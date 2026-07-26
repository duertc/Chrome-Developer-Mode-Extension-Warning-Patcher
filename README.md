# Chrome & Chromium Developer Mode Extension Warning Patcher

A lightweight tool to remove Chromium's Developer Mode Extension Warning popup, extension debugging warning, URL elisions, and enable webRequestBlocking for Manifest V3 extensions.

## Tested Versions
- **Google Chrome**: `131.0.6778.265`
- **Microsoft Edge**: `135.0.3179.85`
- **Helium Browser**: `148.0.7778.215`

## Features
- Remove Developer Mode Extension Warning popup on browser startup
- Remove debugging warning bar when using `chrome.debugger` API
- Disable URL elision (Force showing full HTTPS and WWW in omnibox)
- Enable `webRequestBlocking` extension API for Manifest V3 extensions
- Autodetect browser installations on `C:\` and `D:\` drives (Chrome, Edge, Helium) with custom path option
- Patcher injector using Event Traces for Windows (ETW) with zero overhead

## Requirement & Usage
1. **Prerequisite**: [.NET 6.0 Desktop Runtime](https://dotnet.microsoft.com/download/dotnet/6.0/runtime).
2. **Usage**:
   - Run `ChromeDevExtWarningPatcher.exe`
   - Select detected browsers or click **"Add a custom path"** (e.g. `D:\Program Files\Chrome\App`)
   - Click **Install Patches**

## Commandline Options
```bash
ChromeDevExtWarningPatcher.exe --customPath "D:\Program Files\Chrome\App"
```
- `--customPath`: Define a custom Application directory path
- `--groups`: Specify comma-separated patch group IDs (e.g. 0,1,6)
- `--noWait`: Disable waiting prompt after completion

---

# Chromium 开发者模式扩展警告修补工具 (中文说明)

本工具用于自动移除 Chromium 内核浏览器（如 Chrome / Edge / Helium / Brave）的“请禁用开发者模式扩展”弹窗提示、调试警告条、网址省略隐藏等。

## 实测验证版本
- **Google Chrome**: `131.0.6778.265`
- **Microsoft Edge**: `135.0.3179.85`
- **Helium Browser**: `148.0.7778.215`

## 功能特性
- 自动移除启动时的“请禁用开发者模式扩展”弹窗提示
- 移除使用 `chrome.debugger` API 时的扩展调试警告条
- 禁用 URL 省略（强制在地址栏显示完整的 HTTPS 与 WWW）
- 解禁 Manifest V3 扩展的 `webRequestBlocking` 网络拦截 API
- 自动识别 `C:\` 与 `D:\` 盘中的浏览器安装路径（Chrome, Edge, Helium），支持自定义路径
- 基于 ETW 事件追踪的高效后台注入机制，内存占用极低

## 运行依赖与使用方法
1. **运行依赖**: [.NET 6.0 Desktop Runtime](https://dotnet.microsoft.com/download/dotnet/6.0/runtime)。
2. **使用方法**:
   - 运行 `ChromeDevExtWarningPatcher.exe`
   - 选择检测到的浏览器或点击 **"Add a custom path"**（如 `D:\Program Files\Chrome\App`）
   - 点击 **Install Patches** 执行修补

## 命令行选项
```bash
ChromeDevExtWarningPatcher.exe --customPath "D:\Program Files\Chrome\App"
```
- `--customPath`: 指定自定义浏览器 Application 目录
- `--groups`: 指定补丁组 ID（逗号分隔，如 0,1,6）
- `--noWait`: 补丁完成后不等待按键

---

## License
Public domain under [GPL-3.0 License](LICENSE). Original project by Ceiridge, updated and maintained for modern Chromium builds by duertc.
