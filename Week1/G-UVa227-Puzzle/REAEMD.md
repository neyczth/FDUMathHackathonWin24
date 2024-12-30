## Problem G: Puzzle 说明
本题在输入输出上细节较多, 为减少不必要的踩坑, 我们做如下提醒:
- 输入:
    - 地图的每一行保证有5个字符, 即使最后一个是空格.
    - 动作序列可能包含多行.
    - 动作序列的终止是数字 `0`, 不是字母 `O`.
- 输出:
    - 输出迷宫地图时, 每行最后不应有多余空格.
    - 输出中每两个Puzzle之间有一个额外空行, 但文件最末不应有**额外**空行.

答案正确但格式不对时OJ会返回 `Presentation Error` 的评测结果.

格式标准的样例输入数据如下:
```text
TRGSJ
XDOKI
M VLN
WPABE
UQHCF
ARRBBL0
ABCDE
FGHIJ
KLMNO
PQRS 
TUVWX
AAA
LLLL0
ABCDE
FGHIJ
KLMNO
PQRS 
TUVWX
AAAAABBRRRLL0
Z
```
对于如上样例数据, 以下输出是 "标准" 的:
```text
Puzzle #1:
T R G S J
X O K L I
M D V B N
W P   A E
U Q H C F

Puzzle #2:
  A B C D
F G H I E
K L M N J
P Q R S O
T U V W X

Puzzle #3:
This puzzle has no final configuration.

```