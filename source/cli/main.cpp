#include "MaaAPI.h"

#include "Utils/Locale.hpp" // 不应该 include 这鬼玩意，图方便，先凑合用吧
#include <meojson/json.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

struct Task
{
    std::string name;
    std::string type;
    json::value param = json::object();
};

using TaskList = std::vector<Task>;

void print_help();
bool proc_argv(int argc, char** argv, std::string& adb, std::string& adb_address, TaskList& tasks,
               MaaAdbControllerType& ctrl_type);
void save_config(const std::string& adb, const std::string& adb_address, const TaskList& tasks,
                 MaaAdbControllerType ctrl_type);
std::string read_adb_config(const std::filesystem::path& cur_dir);
void pause();

int main(int argc, char** argv)
{
    print_help();

    std::string adb = "adb";
    std::string adb_address = "127.0.0.1:5555";
    TaskList tasks;
    MaaAdbControllerType control_type = 0;

    bool proced = proc_argv(argc, argv, adb, adb_address, tasks, control_type);
    if (!proced) {
        std::cout << "Failed to parse argv" << std::endl;
        pause();
        return -1;
    }
    if (tasks.empty()) {
        std::cout << "Task empty" << std::endl;
        pause();
        return -1;
    }

    const auto cur_dir = std::filesystem::path(argv[0]).parent_path();
    std::string debug_dir = (cur_dir / "debug").string();
    std::string resource_dir = (cur_dir / "resource").string();
    std::string adb_config = read_adb_config(cur_dir);

    MaaSetGlobalOption(MaaGlobalOption_Logging, (void*)debug_dir.c_str(), debug_dir.size());

    auto maa_handle = MaaCreate(nullptr, nullptr);
    auto resource_handle = MaaResourceCreate(nullptr, nullptr);
    auto controller_handle =
        MaaAdbControllerCreate(adb.c_str(), adb_address.c_str(), control_type, adb_config.c_str(), nullptr, nullptr);

    auto res_result = MaaBindResource(maa_handle, resource_handle);
    auto control_result = MaaBindController(maa_handle, controller_handle);

    _CRT_UNUSED(res_result);
    _CRT_UNUSED(control_result);
    if (!res_result) {
        std::cout << "Failed to init Maa res"
                  << std::endl;
    }
    if (!control_result) {
        std::cout << "Failed to init Maa ctrl" << std::endl;
    }

    int height = 720;
    MaaControllerSetOption(controller_handle, MaaCtrlOption_ScreenshotTargetHeight, reinterpret_cast<void*>(&height),
                           sizeof(int));

    auto resource_id = MaaResourcePostResource(resource_handle, resource_dir.c_str());
    auto connection_id = MaaControllerPostConnection(controller_handle);

    MaaResourceWait(resource_handle, resource_id);
    MaaControllerWait(controller_handle, connection_id);

    auto destroy = [&]() {
        MaaDestroy(maa_handle);
        MaaResourceDestroy(resource_handle);
        MaaControllerDestroy(controller_handle);
    };

    if (!MaaInited(maa_handle)) {
        destroy();
        std::cout << "Failed to init Maa instance, a connection error or resource file corruption occurred, please "
                     "refer to the log."
                  << std::endl;
        pause();
        return -1;
    }

    MaaTaskId task_id = 0;
    
    for (const auto& task : tasks) {
        task_id = MaaPostTask(maa_handle, task.type.c_str(), task.param.to_string().c_str());
    }
    MaaTaskWait(maa_handle, task_id);

    destroy();

    return 0;
}

void print_help()
{
    std::cout << MAA_NS::utf8_to_stdout(
                     R"(欢迎使用 MAA 1999 CLI, 源码地址：https://github.com/MaaAssistantArknights/MAA1999

用法: MAA1999.exe [adb路径] [adb地址] [任务名（有序）]...

可以修改 config.json 来配置任务

请注意命令行参数中的任务名请输入 name，而非 type。name 是可以自己随意修改的，但 type 是固定的。
若无命令行参数，则按顺序执行 config.json 中的全部任务。

欢迎大佬来给我们搓个 GUI _(:з」∠)_

v0.2.0
新增了全关卡导航支持，但还不会吃糖。引导只加了几个常用的关卡，有其他需求可以改改 config，复现次数也在 config 里改

)") << std::endl;
}

json::value combat_param(int index)
{
    json::value param;
    auto& diff = param["diff_task"];

    auto& chapter = diff["EnterTheShow"]["next"];
    auto& stage = diff["TargetStageName"]["text"];
    auto& difficulty = diff["StageDifficulty"]["next"];
    auto& times = diff["SetReplaysTimes"]["text"];

    switch (index) {
    case 4:
        // "4. 3-9 厄险（百灵百验鸟）\n"
        chapter = "MainChapter_3";
        stage = "09";
        difficulty = "StageDifficulty_Hard";
        times = "1";
        break;
    case 5:
        // "5. 4-20 厄险（双头形骨架）\n"
        chapter = "MainChapter_4";
        stage = "20";
        difficulty = "StageDifficulty_Hard";
        times = "1";
        break;
    case 6:
        // "6. 2-3 厄险（祝圣秘银）\n"
        chapter = "MainChapter_2";
        stage = "03";
        difficulty = "StageDifficulty_Hard";
        times = "1";
        break;
    case 7:
        // "7. 3-13 厄险（盐封曼德拉）\n"
        chapter = "MainChapter_3";
        stage = "13";
        difficulty = "StageDifficulty_Hard";
        times = "1";
        break;
    case 8:
        // "8. 4-10 厄险（啮咬盒）\n"
        chapter = "MainChapter_4";
        stage = "10";
        difficulty = "StageDifficulty_Hard";
        times = "1";
        break;
    case 9:
        // "9. 3-11 厄险（金爪灵摆）\n"
        chapter = "MainChapter_3";
        stage = "11";
        difficulty = "StageDifficulty_Hard";
        times = "1";
        break;

    case 10:
        // "10. 尘埃运动 06\n"
        chapter = "ResourceChapter_LP";
        stage = "06";
        difficulty = "StageDifficulty_None";
        times = "1";
        break;
    case 11:
        // "11. 猪鼻美学 06\n"
        chapter = "ResourceChapter_MA";
        stage = "06";
        difficulty = "StageDifficulty_None";
        times = "1";
        break;
    case 12:
        // "12. 丰收时令 04\n"
        chapter = "ResourceChapter_MA";
        stage = "04";
        difficulty = "StageDifficulty_None";
        times = "1";
        break;

    case 13:
        //"13. 群山之声 06（洞悉 岩）\n"
        chapter = "PromotionChapter_ME";
        stage = "06";
        difficulty = "StageDifficulty_None";
        times = "1";
        break;
    case 14:
        //"14. 星陨之所 06（洞悉 星）\n"
        chapter = "PromotionChapter_SL";
        stage = "06";
        difficulty = "StageDifficulty_None";
        times = "1";
        break;
    case 15:
        //"15. 深林之形 06（洞悉 林）\n"
        chapter = "PromotionChapter_SS";
        stage = "06";
        difficulty = "StageDifficulty_None";
        times = "1";
        break;
    case 16:
        //"16. 荒兽之野 06（洞悉 兽）\n"
        chapter = "PromotionChapter_BW";
        stage = "06";
        difficulty = "StageDifficulty_None";
        times = "1";
        break;
    }

    return param;
}

bool proc_argv(int argc, char** argv, std::string& adb, std::string& adb_address, TaskList& tasks,
               MaaAdbControllerType& ctrl_type)
{
    int touch = 1;  
    int key = 1;
    int screencap = 3;

    tasks.clear();

    if (auto config_opt = json::open("config.json"); config_opt && argc < 3) {
        auto& confing = *config_opt;

        adb = confing["adb"].as_string();
        adb_address = confing["adb_address"].as_string();

        int index = 1;
        for (auto& task : confing["tasks"].as_array()) {
            Task task_obj;
            if (task.is_string()) {
                task_obj.type = task.as_string();
                task_obj.name = "MyTask" + std::to_string(index++);
            }
            else {
                task_obj.type = task["type"].as_string();
                task_obj.name = task["name"].as_string();
                task_obj.param = task["param"];
            }
            tasks.emplace_back(task_obj);
        }
        touch = confing.get("touch", touch);
        key = confing.get("key", key);
        screencap = confing.get("screencap", screencap);

        ctrl_type = touch << 0 | key << 8 | screencap << 16;
    }
    else {
        if (argc >= 3) {
            adb = argv[1];
            adb_address = argv[2];

            std::vector<std::string> task_names;
            for (int i = 3; i < argc; ++i) {
                task_names.emplace_back(argv[i]);
            }
            auto all_tasks = std::move(tasks);
            tasks.clear();
            for (auto& task_name : task_names) {
                tasks.emplace_back(task_name, task_name);
            }
        }
        if (adb.empty()) 
        {

            std::cout << std::endl
                      << std::endl
                      << MAA_NS::utf8_to_stdout("请输入 adb 路径，例如 C:/adb.exe，不要有中文: ") << std::endl;
            std::getline(std::cin, adb);
        }
        if (adb_address.empty()) {
            std::cout << std::endl
                      << std::endl
                      << MAA_NS::utf8_to_stdout("请输入 adb 地址，例如 127.0.0.1:5555：") << std::endl;
            std::getline(std::cin, adb_address);
        }
        if (tasks.empty()) {
            std::cout << std::endl
                      << std::endl
                      << MAA_NS::utf8_to_stdout("选择任务，会自动登录，但不会启动游戏和模拟器") << std::endl
                      << std::endl
                      << MAA_NS::utf8_to_stdout(
                             "1.收取荒原\n2.每日心相\n3.领取奖励\n4. 搓饼\n5. 经验本战斗\n6. 纺锤本战斗\n7. 纺锤本跳过")
                      << std::endl
                      << std::endl
                      << std::endl
                      << MAA_NS::utf8_to_stdout("请输入要执行的任务序号，可自定义顺序，以空格分隔，例如 1 3 11 2: ")
                      << std::endl;
            std::vector<int> task_ids;
            std::string line;
            std::getline(std::cin, line);
            std::istringstream iss(line);
            int task_id;
            while (iss >> task_id) {
                task_ids.emplace_back(task_id);
            }
            // tasks.emplace_back(Task { .name = "MyTask0", .type = "Start1999" });

            int index = 1;
            for (auto id : task_ids) {
                Task task_obj;
                task_obj.name = "MyTask" + std::to_string(index++);

                switch (id) {
                case 1:
                    task_obj.type = "Wilderness";
                    break;
                case 2:
                    task_obj.type = "Awards";
                    break;

                case 3:
                    task_obj.type = "Psychube";
                    break;
                case 4:
                    tasks.emplace_back("CraftModule");
                    break;
                case 5:
                    tasks.emplace_back("ExpLuxcavation");
                    break;
                case 6:
                    tasks.emplace_back("ThreadLuxcavationBattle");
                    break;
                case 7:
                    tasks.emplace_back("ThreadLuxcavationSkip");
                    break;
                default:
                    std::cout << "Unknown task: " << id << std::endl;
                    return false;
                }
                tasks.emplace_back(std::move(task_obj));
            }
        }

        ctrl_type = touch << 0 | key << 8 | screencap << 16;
        save_config(adb, adb_address, tasks, ctrl_type);
    }



    return true;
}

void save_config(const std::string& adb, const std::string& adb_address, const TaskList& tasks,
                 MaaAdbControllerType ctrl_type)
{
    json::value config;
    config["adb"] = adb;
    config["adb_Doc"] = "adb.exe 所在路径，相对绝对均可";
    config["adb_address"] = adb_address;
    config["adb_address_Doc"] = "adb 连接地址，例如 127.0.0.1:5555";

    json::value tasks_array;
    for (auto& task : tasks) {
        json::value task_obj;
        task_obj["type"] = task.type;
        task_obj["name"] = task.name;
        task_obj["param"] = task.param;
        tasks_array.emplace(std::move(task_obj));
    }
    config["tasks"] = std::move(tasks_array);
    config["tasks_Doc"] = "要执行的任务 Start1999, Wilderness, Psychube, Awards, Combat";

    config["touch"] = (ctrl_type & MaaAdbControllerType_Touch_Mask) >> 0;
    config["touch_Doc"] = "点击方式：1: Adb, 2: MiniTouch, 3: MaaTouch";
    // config["key"] = key;
    // config["key_Doc"] = "按键方式：1: Adb, 2: MaaTouch";
    config["screencap"] = (ctrl_type & MaaAdbControllerType_Screencap_Mask) >> 16;
    config["screencap_Doc"] = "截图方式：1: 自动测速, 2: RawByNetcat, 3: RawWithGzip, 4: Encode, 5: EncodeToFile, 6: "
                              "MinicapDirect, 7: MinicapStream";
    config["version"] = "v0.2.0";

    std::ofstream ofs("config.json", std::ios::out);
    ofs << config;
    ofs.close();
}

std::string read_adb_config(const std::filesystem::path& cur_dir)
{
    std::ifstream ifs(cur_dir / "resource" / "controller_config.json", std::ios::in);
    if (!ifs.is_open()) {
        std::cout << "Can't open controller_config.json" << std::endl;
        exit(1);
    }

    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return buffer.str();
}

void pause()
{
    std::ignore = getchar();
}