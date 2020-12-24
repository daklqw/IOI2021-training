你在 $\texttt{Metagonia}$ 证券交易所工作。最近 $\texttt{Metagonia}$ 的商人们听说了 $\texttt{London}$ 证券交易所交易的 $\texttt{Iceberg}$ 订单，他们想让你的老板也加一个这样的功能。证券交易引擎是一个能接受订单并产生交易的引擎。

$\texttt{Iceberg}$ 订单是一个整数五元组 $(ID, T, P, V, TV)$。每一个订单有一个标识符 $ID$（在所有订单中独一无二），类型 $T$（要么为 $BUY = 1$ 要么为 $SELL = 2$)，单价 $P$，总共余量 $V$ 和限量 $TV$。对于每一个订单，交易引擎额外地保持追踪着它的当前量 $CV$ 和优先级 $PR$。还存在一个全局交易优先级计数器 $GP$。交易引擎的订单表是由订单组成的集合。

交易引擎生成的交易是一个整数四元组 $(BUY\_ID, SELL\_ID, P, V)$。每个交易有 $BUY\_ID$ 和 $SELL\_ID$ —— 分别对应着 $BUY$ 和 $SELL$ 订单的标识符，交易单价 $P$，交易量 $V$。

交易引擎收到一个订单后，会将它和订单表中其他订单进行匹配。操作如下。假设收到一个 $T_a = SELL$ 的订单 $a$。在目前订单表中的订单里我们找到一个 $T_b = BUY$ 且 $P_b \geq P_a$ 的 $b$。我们选择有最大单价的 $b$，如果存在多个 —— 选择优先级最小的。如果存在这样一个 $b$，那么一个 $BUY\_ID_t = ID_b$， $SELL\_ID_t = ID_a$，交易单价 $P_t = P_b$ 且交易量 $V_t = \min(V_a, CV_b)$ 的交易 $t$ 会被生成。$V_a$，$V_b$ 和 $CV_b$ 都会减少交易量的值。之后如果 $V_b = 0$，那么订单 $b$ 就会从订单表中被删除。如果 $CV_b = 0$（但是 $V_b > 0$）那么我们设置交易 $b$ 的当前量 $CV_b = \min(V_b, TV_b)$，设置 $PR_b = GP$，并且增加 $GP$。我们继续这些选择 $b$ 并且生成交易的操作直到要么 $V_a = 0$ 要么不再存在一个满足条件的订单表中的订单 $b$。在后面这种情况，我们把 $CV_a=\min(V_a,TV_a)$ 且 $PR_a = GP$ 的订单 $a$ 加入订单表，然后增加 $GP$。当匹配订单 $a$ 的过程结束后产生了很多有着相同订单二元组 $a$ 和 $b$ 的交易（而且可能会有一堆！），它们都会被合并为交易量为这些单独交易量的和的单个交易。

如果 $T_a = BUY$，我们会找一个 $T_b = SELL$ 且 $P_b \leq P_a$ 的订单而且会从中选其中单价最小和优先级最小的。剩下的匹配过程类似上面讲述的，除了交易的 $BUY\_ID_t = ID_a$，$SELL\_ID_t = ID_b$，$P_t = P_b$ 并且 $V_t = \min(V_a, CV_b)$。

一开始订单表是空的。你会按顺序收到交易所得到的数个订单。你需要在所有订单完成后输出生成的交易以及剩下的订单表。

**提示：** 题面里的介绍的优先级以及优先级计数器 $GP$ 只是用来正式地描述交易引擎的算法的。实际上你的实现没有完全必要去保持追踪优先级。通常交易引擎只会简单地为在它订单表中的各种价格各种类型的订单维护一个按照优先级排序的数组。

### 输入格式
输入第一行包含订单个数 $n (1 \leq n \leq 50~000)$。下面 $n$ 行中的每一行代表一个订单。每一个订单由一个空格分隔的五元组 $ID$ $T$ $P$ $V$ $TV$ 给出，保证 $1 \leq ID \leq 1~000~000$，$BUY$ 时 $T = 1$，$SELL$ 时 $T = 2$，$1 \leq P \leq 100~000$，并且 $1 \leq TV \leq V \leq 1~000~000~000$。

### 输出格式
对于每个订单输出所有由处理它产生的交易，按照二元组 $(BUY\_ID, SELL\_ID)$ 升序，每个交易单独一行。每个交易按空格分隔的整数四元组 $BUY\_ID$ $SELL\_ID$ $P$ $V$ 输出。保证交易总数不会超过 $100~000$。在所有交易后输出一个空行，下面紧跟着订单表。每一个仍在交易表中的订单按空格分隔的六元组 $ID$ $T$ $P$ $V$ $TV$ $CV$ 输出，按照 $P$ 为第一关键字，$PR$ 为第二关键字排序。

### 样例一
#### input
<pre>
7
42 1 100 200 20
239 1 100 50 50
1111 1 101 30 15
1234 1 100 300 15
4321 2 99 125 25
5678 1 101 30 30
8765 2 101 100 20

</pre>

#### output
<pre>
42 4321 100 30
239 4321 100 50
1111 4321 101 30
1234 4321 100 15
5678 8765 101 30

42 1 100 170 20 10
1234 1 100 285 15 15
8765 2 101 70 20 20

</pre>

#### explanation

在这个样例开始四个订单都有 $T = BUY$。假设交易引擎一开始的 $GP$ 等于 $1$，在收到这些订单后，在按照题面给出来的匹配规则给 $T_b = BUY$ 的订单排序（先按单价最大，再按优先级最小）后，订单表看起来向下面这样子：

<div style="width: 256px">
<table class="table table-bordered table-vertical-middle" >
<thead>
<tr>
<th style="text-align: right; border-right: none"> $ID$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $T$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $P$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $V$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $TV$ </th>
<th style="text-align: right; border-left: none"> $CV$ </th>
<th style="text-align: right"> $PR$ </th>
</tr>
</thead>
<tbody style="text-align: right;">
<tr>
<td style="border-right: none"> $1111$ </td>
<td style="border-left: none; border-right: none"> $1$ </td>
<td style="border-left: none; border-right: none"> $101$ </td>
<td style="border-left: none; border-right: none"> $30$ </td>
<td style="border-left: none; border-right: none"> $15$ </td>
<td style="border-left: none"> $15$ </td>
<td> $3$ </td>
</tr>
<tr>
<td style="border-bottom: none; border-right: none"> $42$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $1$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $100$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $200$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $20$ </td>
<td style="border-bottom: none; border-left: none"> $20$ </td>
<td style="border-bottom: none; "> $1$ </td>
</tr>
<tr>
<td style="border-bottom: none; border-top: none; border-right: none"> $239$ </td>
<td style="border-bottom: none; border-top: none; border-left: none; border-right: none"> $1$ </td>
<td style="border-bottom: none; border-top: none; border-left: none; border-right: none"> $100$ </td>
<td style="border-bottom: none; border-top: none; border-left: none; border-right: none"> $50$ </td>
<td style="border-bottom: none; border-top: none; border-left: none; border-right: none"> $50$ </td>
<td style="border-bottom: none; border-top: none; border-left: none"> $50$ </td>
<td style="border-bottom: none; border-top: none;"> $2$ </td>
</tr>
<tr>
<td style="border-top: none; border-right: none"> $1234$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $1$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $100$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $300$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $15$ </td>
<td style="border-top: none; border-left: none"> $15$ </td>
<td style="border-top: none; "> $4$ </td>
</tr>
</tbody>
</table>
</div>

第五个订单（$ID_a = 4321$) 有 $T_a = SELL$，$P_a = 99$，以及 $V_a = 125$ 并且是可以和上面所有四个给出的订单匹配。一开始，它两次以最高的价格 $101$ 和交易量 $30$ 匹配订单 $1111$，并且把它此从订单表中删除，在此过程中将 $GP$ 增加到 $6$，并且将 $V_a$ 减少到 $95$。接着，有另外三个单价为 $100$ 的订单。通过一次在它们之间的匹配产生三个交易，交易总量为 $85$（订单 $42$ 交易量 $20$，订单 $239$ 交易量 $50$，并将它从表中删除，订单 $1234$ 交易量 $15$），$GP$ 增加到 $8$，$V_a$ 减到 $10$。表中剩下的订单被展示在下面：

<div style="width: 256px">
<table class="table table-bordered table-vertical-middle" >
<thead>
<tr>
<th style="text-align: right; border-right: none"> $ID$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $T$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $P$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $V$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $TV$ </th>
<th style="text-align: right; border-left: none"> $CV$ </th>
<th style="text-align: right"> $PR$ </th>
</tr>
</thead>
<tbody style="text-align: right;">
<tr>
<td style="border-bottom: none; border-right: none"> $42$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $1$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $100$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $180$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $20$ </td>
<td style="border-bottom: none; border-left: none"> $20$ </td>
<td style="border-bottom: none; "> $6$ </td>
</tr>
<tr>
<td style="border-top: none; border-right: none"> $1234$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $1$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $100$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $275$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $15$ </td>
<td style="border-top: none; border-left: none"> $15$ </td>
<td style="border-top: none; "> $7$ </td>
</tr>
</tbody>
</table>
</div>

最后的一个匹配是和订单 $42$ 产生了一个交易量为 $10$ 的交易（和订单 $42$ 的匹配总共产生了 $30$ 的交易量），同时订单 $4321$ 已经完成了 $V_a = 0$。订单 $4321$ 对应的总共四个交易被输出到样例输出里。剩下的订单表是：

<div style="width: 256px">
<table class="table table-bordered table-vertical-middle" >
<thead>
<tr>
<th style="text-align: right; border-right: none"> $ID$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $T$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $P$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $V$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $TV$ </th>
<th style="text-align: right; border-left: none"> $CV$ </th>
<th style="text-align: right"> $PR$ </th>
</tr>
</thead>
<tbody style="text-align: right;">
<tr>
<td style="border-bottom: none; border-right: none"> $42$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $1$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $100$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $180$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $20$ </td>
<td style="border-bottom: none; border-left: none"> $10$ </td>
<td style="border-bottom: none; "> $6$ </td>
</tr>
<tr>
<td style="border-top: none; border-right: none"> $1234$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $1$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $100$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $275$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $15$ </td>
<td style="border-top: none; border-left: none"> $15$ </td>
<td style="border-top: none; "> $7$ </td>
</tr>
</tbody>
</table>
</div>

第六个 $BUY$ 订单（$ID = 5678$）被加入了订单表（$GP$ 变成了 $9$）：

<div style="width: 256px">
<table class="table table-bordered table-vertical-middle" >
<thead>
<tr>
<th style="text-align: right; border-right: none"> $ID$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $T$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $P$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $V$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $TV$ </th>
<th style="text-align: right; border-left: none"> $CV$ </th>
<th style="text-align: right"> $PR$ </th>
</tr>
</thead>
<tbody style="text-align: right;">
<tr>
<td style="border-right: none"> $5678$ </td>
<td style="border-left: none; border-right: none"> $1$ </td>
<td style="border-left: none; border-right: none"> $101$ </td>
<td style="border-left: none; border-right: none"> $30$ </td>
<td style="border-left: none; border-right: none"> $30$ </td>
<td style="border-left: none"> $30$ </td>
<td> $8$ </td>
</tr>
<tr>
<td style="border-bottom: none; border-right: none"> $42$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $1$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $100$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $180$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $20$ </td>
<td style="border-bottom: none; border-left: none"> $10$ </td>
<td style="border-bottom: none; "> $6$ </td>
</tr>
<tr>
<td style="border-top: none; border-right: none"> $1234$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $1$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $100$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $275$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $15$ </td>
<td style="border-top: none; border-left: none"> $15$ </td>
<td style="border-top: none; "> $7$ </td>
</tr>
</tbody>
</table>
</div>

最后，第七个订单（$ID = 8765$），在单价条件的限制上，只能被订单 $5678$ 匹配，生成一个交易量为 $30$ 的交易，交易 $5678$ 被从订单表中删除，同时加入订单 $8765$。现在订单表同时拥有 $BUY$ 和 $SELL$ 的订单：

<div style="width: 256px">
<table class="table table-bordered table-vertical-middle" >
<thead>
<tr>
<th style="text-align: right; border-right: none"> $ID$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $T$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $P$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $V$ </th>
<th style="text-align: right; border-left: none; border-right: none"> $TV$ </th>
<th style="text-align: right; border-left: none"> $CV$ </th>
<th style="text-align: right"> $PR$ </th>
</tr>
</thead>
<tbody style="text-align: right;">
<tr>
<td style="border-bottom: none; border-right: none"> $42$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $1$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $100$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $180$ </td>
<td style="border-bottom: none; border-left: none; border-right: none"> $20$ </td>
<td style="border-bottom: none; border-left: none"> $10$ </td>
<td style="border-bottom: none; "> $6$ </td>
</tr>
<tr>
<td style="border-top: none; border-right: none"> $1234$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $1$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $100$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $275$ </td>
<td style="border-top: none; border-left: none; border-right: none"> $15$ </td>
<td style="border-top: none; border-left: none"> $15$ </td>
<td style="border-top: none; "> $7$ </td>
</tr>
<tr>
<td style="border-right: none"> $8765$ </td>
<td style="border-left: none; border-right: none"> $2$ </td>
<td style="border-left: none; border-right: none"> $101$ </td>
<td style="border-left: none; border-right: none"> $70$ </td>
<td style="border-left: none; border-right: none"> $20$ </td>
<td style="border-left: none"> $20$ </td>
<td> $9$ </td>
</tr>
</tbody>
</table>
</div>

### 限制与约定

**时间限制**：$3 \texttt{s}$

**空间限制**：$512 \texttt{MB}$

