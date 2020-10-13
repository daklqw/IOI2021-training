## Fygon

$\texttt{Frederick}$ 是一个年轻的程序员。他参加了所有他能找到的程序比赛，而且总是用他最喜欢的语言 $\textrm{Fygon}$。不幸的是，他经常 TLE（运行超时），甚至在他的算法是渐进最优的时候他也会 TLE。这都是因为 $\textrm{Fygon}$ 的解释器太慢了。然而 $\texttt{Frederick}$ 非常喜欢 $\textrm{Fygon}$ 以至于他会用非渐进优化把解法卡进时限。为了更方便，他让你写一个能够计算出他的 $\textrm{Fygon}$ 程序准确的操作次数的程序。

方便起见，我们假设 $\textrm{Fygon}$ 只有两种句型。第一种是 $\textrm{lag}$，它代替了几乎其他所有句型。第二种是 $\textrm{for}$ 循环：

$$
\begin{align*}
&\textrm{for &lt;variable&gt; in range(&lt;limit&gt;):} \\
&~~~~\textrm{&lt;body&gt;}
\end{align*}
$$

意思是说，$\textrm{&lt;variable&gt;}$ 会从 $0$ 迭代到 $\textrm{&lt;limit&gt;} - 1$。在 $\textrm{Fygon}$ 中，$\textrm{&lt;variable&gt;}$ 是一个小写拉丁字母（$\textrm{a}$ 到 $\textrm{z}$ 其中一个），$\textrm{&lt;limit&gt;}$ 是一个已经定义过的 $\textrm{&lt;variable&gt;}$ 或者是一个正整常数。$\textrm{&lt;body&gt;}$ 是循环体，有四个空格的缩进，而且至少包含一个语句。

程序会直接在读入里得到一个变量 $n$，这个变量有特殊含义，不能在循环里被定义为 $\textrm{&lt;variable&gt;}$。

你的任务是找到一个公式，能够计算出 $\textrm{lag}$ 被执行的次数，以 $n$ 为变量表示出来。

### 输入格式
输入包含一个 $\textrm{Fygon}$ 程序。不存在两个循环使用了相同的 $\textrm{&lt;variable&gt;}$ 作为迭代器。每个变量以及在外层定义好的 $n$ 会在 $\textrm{&lt;limit&gt;}$ 被使用。

保证输入的程序最多有 $20$ 条语句，最多有 $6$ 个循环，所有的整数常数取值都在 $[1, 9]$ 上。。

### 输出格式
输出一个关于变量 $n$ 的公式。去掉空白字符后长度不能超过 $100$。

（因为原题目没写加上空白字符的限制，我们这里限制输出最多 $1024$ 个字符）

这个公式需要遵循一下语法：

$$
\begin{align*}
\text{&lt;Expression&gt;} & ::= \text{&lt;Product&gt;} ((\text{'+'} | \text{'-'}) \text{&lt;Product&gt;})^* \\
\text{&lt;Product&gt;} & ::= \text{&lt;Value&gt;} (* \text{&lt;Value&gt;})^* \\
\text{&lt;Value&gt;} & ::= \text{'n'} | \text{&lt;Number&gt;} | \text{'-'} \text{&lt;Value&gt;} | \text{'('} \text{&lt;Expression&gt;} \text{')'} \\
\text{&lt;Number&gt;} & ::= [\text{'0'}..\text{'9'}]^ + (\text{'/'} [\text{'0'}..\text{'9'}]^+)^?\\
\end{align*}
$$

### 样例一
#### input
<pre>
for i in range(n):
    for j in range(i):
        lag
for x in range(5):
    for y in range(n):
        for z in range(n):
            lag
    lag

</pre>

#### output
<pre>
1/2 * n * (n - 1) + 5 * (n * n + 1)

</pre>

### 限制与约定

**时间限制**：$1 \texttt{s}$

**空间限制**：$512 \texttt{MB}$
