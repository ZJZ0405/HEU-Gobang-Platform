# CSMind
计算思维
# 项目名
HEU Gobang Platform
# 技术特性
## ConsoleGUI
### 8-bit色彩 Windows Command Line Host
采用wprintf的特殊输出前缀实现Foreground全彩输出
通过更改CONSOLE_SCREEN_BUFFER_INFO_EX中的ColorTable实现Background全彩输出
### 棋盘无极DPI
通过测量传入的屏幕大小参数自动更改棋盘渲染大小
### 基于输入-输出循环的交互系统

# 提交规范

本规范基于[Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)制定

## Commit Message 格式

`[type]([scope]): [subject]`

## Type 格式(必填)

- docs: 文档(documentation)

- feat: 新功能(feature)

- fix/to 修复bug

  - fix: 产生diff并自动修复此问题。适用于一次提交修复问题

  - to: 只产生diff不自动修复问题。适用于多次提交。最终修复问题使用fix

- style: 格式(不影响代码运行的变动)

- refactor: 重构(不改变代码本身逻辑)

- perf: (优化相关)

- test: (增加测试)

- chore: (构建过程或辅助工具的变动)

- revert: (回滚到上一个版本)

- merge: (代码合并)

- sync: (同步主线或分支的bug)

## Scope 范围(可选)

用于说明commit影响的范围，比如数据层，控制层，逻辑层等等，视项目不同而不同。

## Subject 主体(必填)

用于简短描述commit目的，不超过50个字符。以动词开头，使用第一人称现在时。
