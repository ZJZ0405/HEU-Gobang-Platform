# CSMind
计算思维
# 五子棋对战平台
## 功能
- 人机交互界面
- 人人对战
- 人机对战
## AI
- 最大值最小值搜索算法
这里的值为全局评估数值，越大对AI越有利，反之越小对玩家越有利
AI处于max层，取最大值
玩家处于min层，取最小值
- 全局评估函数
- 落点生成
并不是所有的地方都适合落子
- 阿尔法-贝塔减枝算法
- 启发式搜索算法
- 迭代加深


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
