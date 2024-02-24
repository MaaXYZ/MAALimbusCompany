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

## TL;DR
带参数启动可执行文件启动相关任务，如：
```
MAALimbus_CLI.exe "H:\Program Files\Netease\MuMuPlayer-12.0\shell\.\adb.exe" "127.0.0.1:16640" ThreadLuxcavationBattle ExpLuxcavation CraftModule
```
## 下载说明

下载地址：<https://github.com/hxdnshx/MAALimbusCompany/releases>

### Windows

- 对于绝大部分用户，请下载 `MAALimbusCompany-win-x86_64-vXXX.zip`
- 若确定自己的电脑是 arm 架构，请下载 `MAALimbusCompany-win-aarch64-vXXX.zip`
- 解压后运行 `MAALimbus_CLI.exe` 即可

### Linux

~~用 Linux 的大佬应该不需要我教~~

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
