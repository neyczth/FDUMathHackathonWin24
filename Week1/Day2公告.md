## 多组输出题目的输出要求
今天的题目对输入输出有较高的要求, 如果格式不对会被判为 `Presentation Error` 或 `Wrong Answer`. 我们对此做如下提醒:
- 对于在一行内输出以空格间隔的多个整数, 行末不应有多余空格.
- 对于输出多组以空行间隔的答案, 文末不应有**多余**空行 (即答案末尾的 endl 被允许, 但是额外的间隔行不应存在).

> **注:** 事实上, 绝大多数 OJ 的比较方式是 "过滤行末空格和文末换行的全文比较", 这是为了节省选手编写输出模块的时间. 但很可惜我们今天使用的 OJ 对输出格式要求比较高, 所以请大家严格按照上述说明输出答案.

以下对于个别题目做特殊提醒.

#### Problem G: Puzzle
- 输入:
    - 地图的每一行保证有 5 个字符, 即使最后一个是空格.
    - 动作序列可能包含多行.
    - 动作序列的终止是数字 `0`, 不是字母 `O`.

格式标准的样例输入数据如下 (点击下方代码框右上角 "Copy" 按钮可复制):
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

#### Problem I: Spatial Structures
- 输出:
	- 在输出以一列十进制整数表示的四分树结构时, 如果黑节点数超过 12 个, 每输出 12 个换一次行. 这在原题中是有说明的.