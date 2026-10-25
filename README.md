# Snake · Cocos2d-x 贪吃蛇

一个使用 C++ 和 Cocos2d-x 编写的早期贪吃蛇小游戏，包含格子移动、食物生成、碰撞判定、触摸操作、分数记录和失败后重试。项目保留了 2014 年的代码及各平台工程，适合阅读简单游戏循环和 Cocos2d-x 2.x 风格的场景组织方式。

后续版本另见 [Snake_for_v3.2](https://github.com/chen3286822/Snake_for_v3.2)，两个仓库的功能和构建环境不要混用。

## 玩法与功能

- 蛇按固定节奏在格子地图上移动，吃到食物后增长并增加分数。
- 碰到地图边缘或自身会进入失败场景，点击 `Retry` 重新开始。
- 点击游戏区域的上、下、左、右方向区域控制转向，不允许直接反向移动。操作按点击位置判断，并不是滑动手势。
- 底部显示分数；`UserData` 使用 `CCUserDefault` 读写分数数据。

## 代码结构

```text
Classes/
├── AppDelegate.cpp       # 应用入口与初始场景
├── Snake.cpp             # 蛇身、移动、吃食物和碰撞判定
├── SnakeMapScene.cpp     # 地图、食物与移动调度
├── TouchLayer.cpp        # 触摸区域与方向控制
├── DataLayer.cpp         # 分数和退出按钮
├── LoseScene.cpp         # 失败界面与重试
└── UserData.cpp          # 分数数据读写
Resources/               # 图片和字体
proj.win32/              # Windows 工程
proj.android/            # Android 工程与旧版构建说明
proj.ios/、proj.mac/ 等   # 其他平台的历史工程文件
```

## 构建环境

仓库包含游戏代码和平台工程，但没有完整的 Cocos2d-x 引擎源码。工程引用了仓库外部的 `cocos2dx`、`CocosDenshion`、`extensions` 和 `external` 目录，直接下载本仓库并不能独立构建。

### Windows

- 入口：`proj.win32/Snake.sln`，Visual Studio 2010 格式，提供 Win32 Debug / Release 配置。
- 源码采用 `CCScene`、`CCLayer`、`CCDirector::sharedDirector()` 等 Cocos2d-x 2.x 风格 API；仓库没有明确锁定引擎的精确版本。
- 需要先准备匹配的旧版 Cocos2d-x 引擎，并恢复工程预期的目录关系，或调整引擎项目和头文件的引用路径。

例如，原相对路径可对应以下布局：

```text
cocos2d-x-root/
├── cocos2dx/
├── CocosDenshion/
├── extensions/
├── external/
└── projects/
    └── Snake/            # 本仓库
        └── proj.win32/
```

### Android

保留了 NDK + Ant / Eclipse ADT 时代的工程，没有 Gradle 配置。`project.properties` 的目标为 `android-16`，`build_native.sh` 依赖 `NDK_ROOT`，并按固定相对路径寻找引擎。

原始操作说明见 [proj.android/README.md](proj.android/README.md)。其中包含当年的工具与示例路径，应结合本项目配置使用，而不是视为现代 Android Studio 的直接构建步骤。构建脚本会重新生成 `proj.android/assets`，资源修改应放在 `Resources`，不要只改生成目录。

## 项目状态

这是保留历史实现的学习项目。各平台工程文件的存在不代表它们目前都能正常构建或运行，旧 SDK、引擎和工具链需要自行核对。本次说明依据源码和工程文件整理，未重新执行构建或设备测试。
