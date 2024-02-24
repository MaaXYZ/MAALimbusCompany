# MAALimbusCompany

基于全新架构的 亿韭韭韭（LimbusCompany） 小助手。图像技术 + 模拟控制，解放双手！  
由 [MaaFramework](https://github.com/MaaAssistantArknights/MaaFramework) / [MaaCommon](https://github.com/MaaAssistantArknights/MaaCommon) 强力驱动！

在使用 MAALimbusCompany 时，建议将模拟器分辨率配置为 `1280x720`，且 LimbusCompany 游戏本体的 `Render Scaling` 选项配置到 `Medium` 以上，语言配置为 `English`

## 与其他项目的区别

由于采用 MAA 框架进行开发，这个自动化工具主要支持的目标为 Android 设备/模拟器，并不支持PC端（Steam）游戏的自动化，如果您需要相关的工具，可以前往下面的项目：

 - https://github.com/HSLix/LixAssistantLimbusCompany
 - https://github.com/Xie-Tiao/Limbus-Scripts
 - https://github.com/Janrilw/limbus-company-auto


## 画大饼

- [x] 自动收菜  
  最基本的了，没啥好说的。目前已支持 自动经验/线本。
  对应的任务是： `ExpLuxcavation` 和 `ThreadLuxcavationSkip` `ThreadLuxcavationBattle`。日常合成模块的任务是 `CraftModule`。 `SubmitMission` 可以收取当前通行证下已完成的每日任务。
  对应最新活动的 11 12 关的任务是：`Mission_4_5_11` `Mission_4_5_12` （活动已结束，不建议再使用）
- 对应 Miracle District 活动的任务是： `Mission_5_5_13`
- [ ] 自动选人
  。。。
- [ ] 自动镜牢  
  镜牢的关卡选择看起来好麻烦，不过战斗的话相信Auto都能解决吧（悲

## 下载说明

下载地址：<https://github.com/hxdnshx/MAALimbusCompany/releases>

### Windows

- 对于绝大部分用户，请下载 `MAALimbusCompany-win-x86_64-vXXX.zip`
- 若确定自己的电脑是 arm 架构，请下载 `MAALimbusCompany-win-aarch64-vXXX.zip`
- 解压后运行 `MaaPiCli.exe` 即可

### macOS

- 若使用 Intel 处理器，请下载 `MAALimbusCompany-macos-x86_64-vXXX.zip`
- 若使用 M1, M2 等 arm 处理器，请下载 `MAALimbusCompany-macos-aarch64-vXXX.zip`
- 使用方式：
  ```bash
  chmod a+x MaaPiCli
  ./MaaPiCli
  ```

### Linux

~~用 Linux 的大佬应该不需要我教~~

## 使用说明
### ①
启动后会出现:
```
Welcome to use Maa Project Interface CLI!

Version: v0.0.1

### Select ADB ###

        1. Auto detect
        2. Manual input

Please input [1-2]:
```
分别代表：
1. 自动检测，如果在同一台机器上开启着模拟器，可以尝试选择这个。

```
### Select ADB ###

        1. Auto detect
        2. Manual input

Please input [1-2]: 1

Finding device...

## Select Device ##

        1. MuMuPlayer12
                H:/Program Files/Netease/MuMuPlayer-12.0/shell/adb.exe
                127.0.0.1:16672

Please input [1-1]: 1
```
选择 1 后会像上面这样，列出若干个模拟器实例，之后选择你需要进行操控的即可。

2. 手动输入，目前手动输入对于"含空格的路径"有问题，请参考下面的说明手动修改 `config/maa_pi_config.json`，如果没有则新建，修改完成后重启 `MaaPiCli`。

```
{
    "controller": {
        "adb_path": "H:\\Program Files\\Netease\\MuMuPlayer-12.0\\shell\\adb.exe",
        "address": "127.0.0.1:16672",
        "name": "ADB 默认方式"
    },
    "resource": "官服",
    "task": [
        {
            "name": "活动：肉斩骨断-22关",
            "option": [
            ]
        }
    ]
}
```
其中 `"adb_path"` 部分是你的adb的路径，一般你可以在你的MuMu等模拟器的安装路径下，找到 `adb.exe`。注意如果路径里面有`\`，需要替换成 `\\'` ，就像上面那样。

`address` 是模拟器实例的 ADB 端口信息，你可以从你的模拟器上获取，获取方式相关可以参考：[MAA的文档](https://maa.plus/docs/%E7%94%A8%E6%88%B7%E6%89%8B%E5%86%8C/%E5%B8%B8%E8%A7%81%E9%97%AE%E9%A2%98.html#%E7%A1%AE%E8%AE%A4-adb-%E5%8F%8A%E8%BF%9E%E6%8E%A5%E5%9C%B0%E5%9D%80%E6%AD%A3%E7%A1%AE)。

### ②
在初次启动后，会让你输入启动的任务：
```
### Add task ###

        1. 经验本（战斗）
        2. 纺锤本（跳过）
        3. 纺锤本（战斗）
        4. 合成脑啡肽
        5. 领取日常任务（第三赛季）
        6. 活动：鸡-11关（活动已结束）
        7. 活动：鸡-12关（活动已结束）
        8. 活动：MiracleDistrict-13关（活动已结束）
        9. 活动：肉斩骨断-22关
        10. 活动：肉斩骨断-23关

Please input [1-10]:
```
选择你要执行的任务即可。

### ③

之后会反复出现：
```
Tasks:

<这里会列出你已经增加，等待执行的任务>

### Select action ###

        1. Switch controller
        2. Switch resource
        3. Add task
        4. Move task
        5. Delete task
        6. Run tasks
```
其中分别代表：
1. 调整控制器（也就是adb地址等）
2. 调整资源（不用管，目前只有一个）
3. 新增任务，像②中那样
4. 移动任务
5. 删除任务
6. 开始执行任务，在这之后就会自动开始操控。

如果你认为这种方式过于繁琐，也可以直接修改 `config/maa_pi_config.json`。


## 图形化界面

目前暂无正式版 GUI，但有以下由社区大佬们贡献的 GUI 项目，欢迎使用！

- [MAA1999WPF](https://github.com/MLAcookie/MAA1999WPF) 拿WPF框架写的一个MAA199的UI（应该能导入吧）

## How to build

**如果你要编译源码才看这节，否则直接 [下载](https://github.com/hxdnshx/MAALimbusCompany/releases) 即可**

0. 完整克隆本项目及子项目

    ```bash
    git clone --recursive https://github.com/hxdnshx/MAALimbusCompany.git
    ```

1. 下载 MaaFramework 的 [Release 包](https://github.com/MaaAssistantArknights/MaaFramework/releases)，解压到 `deps` 文件夹中
2. 安装

    ```python
    python ./install.py
    ```

生成的二进制及相关资源文件在 `install` 目录下

## 开发相关

- [MaaFramework 快速开始](https://github.com/MaaAssistantArknights/MaaFramework/blob/main/docs/zh_cn/1.1-%E5%BF%AB%E9%80%9F%E5%BC%80%E5%A7%8B.md)

## Join us

- 开发 QQ 群：864474742
- MaaFramework 开发交流 QQ 群: 595990173
