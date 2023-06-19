# CSMind
计算思维
# 项目名
HEU Gobang Platform
# 技术特性
## ConsoleGUI
### 8-bit Color Windows Command Line Host
| Conventional | Our Solution |
|--|--|
| <img src="https://user-images.githubusercontent.com/36219016/230775519-656c54e3-bac7-4e0c-aa59-d02639820205.png"> | <img src="https://user-images.githubusercontent.com/36219016/230775522-db09bfe2-b7d0-453d-b796-5e11a0ca0c87.png"> |
| 1-Bit RGBW | 8-Bit RGB |
| 2^4 Colors | 2^24 Colors |

#### Foreground Color Implementation:
```c
  struct Color // 颜色结构体
  {
      int r,g,b;
  };
  wchar_t *outputFormatPrefix = L“\x1b[38;2;%d;%d;%dm”; // 更改颜色使用的输出前缀
  void Console_Print(wchar_t *str, struct Color color) // 输出彩色字符串
  {
      wprintf(outputFormatPrefix, color.r, color.g, color.b); // 更改颜色
      DWORD ws;
      WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), str, wcslen(str), &ws, NULL); // 输出字符串
  }
```
Use _wchar_t_ (wide char type) to avoid UTF-8 encoding garbled characters

#### Background Color Implementation:
```c
void MapColorTable()
{
    CONSOLE_SCREEN_BUFFER_INFOEX csbiex;
    csbiex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfoEx(hOut, &csbiex);
    csbiex.ColorTable[0] = RGB(41, 97, 136);   // 替代黑色
    csbiex.ColorTable[1] = RGB(240, 200, 183); // 替代白色，强调色
    SetConsoleScreenBufferInfoEx(hOut, &csbiex);
}
```
#### Why we need this feature?
To colorize chessboard 

To make the chesses easier to see(highlighting)

![image](https://user-images.githubusercontent.com/36219016/230775739-b9264efd-b3c3-47c9-9d9b-16e47329a390.png)

### Blink-proof Render Algorithm
Since __double buffering__ conflicts with colorful output, we designed a new algorithm to ensure that the same pixel is written only once every time a buffer write operation is performed.
| Without Algorithm | With Algoithm |
|--|--|
| <img src="https://github.com/ZJZ0405/CSMind/blob/develop/static/2023-04-08%2022-45-05%2000_00_18-00_00_21~1.gif"> | <img src="https://github.com/ZJZ0405/CSMind/blob/develop/static/2023-04-08%2022-45-05%2000_00_18-00_00_21.gif"> |

### Adaptive DPI Rendering  
| Font Size = 14 | Font Size = 24 | Font Size = 36 |
|--|--|--|
| <img src="https://user-images.githubusercontent.com/36219016/230775867-e1c9663b-6982-46e0-b719-437b8d205475.png"> | <img src="https://user-images.githubusercontent.com/36219016/230775870-5863197c-872c-45b0-9c55-bd50a3a72a81.png"> | <img src="https://user-images.githubusercontent.com/36219016/230775872-d81a71a8-9465-41a3-9775-571252bd6b65.png"> |

Use percentages whenever possible to position controls and scale controls by integer multiples

### Interactive system logic based on message queue
The UI asks the console buffer for input events through a loop, and comprehensively handles them.
We can receive mouse and keyboard events by this function:
```c
BOOL WINAPI ReadConsoleInput(
  _In_  HANDLE        hConsoleInput,
  _Out_ PINPUT_RECORD lpBuffer,
  _In_  DWORD         nLength,
  _Out_ LPDWORD       lpNumberOfEventsRead
);

typedef struct _INPUT_RECORD {
  WORD  EventType;
  union {
    KEY_EVENT_RECORD          KeyEvent;
    MOUSE_EVENT_RECORD        MouseEvent;
    WINDOW_BUFFER_SIZE_RECORD WindowBufferSizeEvent;
    MENU_EVENT_RECORD         MenuEvent;
    FOCUS_EVENT_RECORD        FocusEvent;
  } Event;
} INPUT_RECORD;
```
Example of _waiting for left click_
```c
// 获取鼠标输入
    INPUT_RECORD inRec;
    DWORD res;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE); /* 获取标准输入设备句柄*/
LABEL1:
    do
    {
        ReadConsoleInputW(hInput, &inRec, 1, &res);
    } while (inRec.Event.MouseEvent.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED);
```
## AI
### 背景
**零和博弈**，又称零和游戏或零和赛局，与非零和博弈相对，是博弈论的一个概念，属非合作博弈。

**零和博弈**表示所有博弈方的利益之和为零或一个常数，即一方有收入，其他方必有所失。在零和博弈中，博弈各方是不合作的。

**五子棋是**零和博弈的一种
### 博弈树
五子棋看起来有各种各样的走法，而实际上把每一步的走法展开，就是一颗巨大的博弈树，博弈双方交替落子。通过深度优先搜索算法寻找最优路径。
### 落子策略
棋盘上并不是全部位置都适合落子，取棋盘已有棋子周围两格以内为适合落子区域
### 评估函数
由于零和博弈的定义，我们可以认为博弈双方的任何操作若对自己有利，则一定对对方不利。
通过棋盘上连子的数量，来表示某一方的分数
- 连五 100000
- 活四 10000
- 活三 1000
- 活二 100
- 活一 10
- 死四 1000
- 死三 100
- 死二 10
### 优化算法
由于DFS和评估需要大量算力，需要进行优化
- Alpha-Beta剪枝算法

  **Alpha-Beta剪枝算法**是一种安全的剪枝策略，也就是不会对棋力产生任何负面影响。它的基本依据是：棋手不会做出对自己不利的选择。依据这个前提，如果一个节点明显是不利于自己的节点，那么就可以直接剪掉这个节点。


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
