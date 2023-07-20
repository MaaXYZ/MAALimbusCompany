# MAA1999

基于全新架构的 亿韭韭韭（LimbusCompany） 小助手。图像技术 + 模拟控制，解放双手！  
由 [MaaFramework](https://github.com/MaaAssistantArknights/MaaFramework) / [MaaCommon](https://github.com/MaaAssistantArknights/MaaCommon) 强力驱动！

## 画大饼

- [x] 自动收菜  
  最基本的了，没啥好说的。目前已支持 自动经验/线本。
  对应的任务是： `ExpLuxcavation` 和 `ThreadLuxcavation`。日常合成模块的任务是 `CraftModule`。
- [ ] 自动选人
  。。。
- [ ] 自动镜牢  
  镜牢的关卡选择看起来好麻烦，不过战斗的话相信Auto都能解决吧（悲

## How to build

**如果你要编译源码才看这节，否则直接 [下载](https://github.com/MaaAssistantArknights/MAA1999/releases) 即可**

_只是一个临时的编译方法，因为新架构中的 [MaaCommon](https://github.com/MaaAssistantArknights/MaaCommon) 还没完成，所以先简单糊一下。欢迎大佬们来带带~_

1. 更新子模块 `git submodule update --init --recursive`
2. 下载 MaaFramework 的 [Release 包](https://github.com/MaaAssistantArknights/MaaFramework/releases)，解压到 `source/cli/x64/Release`
3. 使用 Visual Studio 编译 `source/cli/MAA1999_CLI.sln`
4. `tools/CropRoi` 是个小工具，可以用来裁剪图片和获取 ROI

## Join us

开发 QQ 群：649344857
