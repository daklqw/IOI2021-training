## TF
应该不难，然后我做了这么久……

难道我最近太划了？

~~显然分类讨论就做完了~~

考虑 $A$，$B$ 中间没有其他数，那么我们把这种连边记为 $A$。

显然对于每种 $A$ 只能选一个位置。

我们记每个位置 $i$ 如果 $v_i$ 只出现一遍，那么它是 $1$，否则是 $0$。

对于 $0$ 周围最多只能建一条边。

那么问题变成了一张奇怪的图的最大独立集。

看起来有很多团，但是因为值的连续性，直接 $f[i][j]$ 记为目前是第 $i$ 种边，上一个选的边位置在 $j$ 即可。

## DD
	dd if=/dev/null of=/dev/sda1

很好的一道题，然后式子看错好久导致写不出来……

首先看到这个式子，发现很好搞成三维凸包。

但是不好做。然后想到了单调栈，发现两个数组都有 $t_i < t_j$ 则 $p_i > p_j$ 的单调栈。

然后没有什么可二分性。但是看到式子想把三维向量的那个常数项搞掉，这使我们想到了四边形不等式：

对于 $i < j, x < y$ （我现在还背不对不等式方向/kk）：

$$
\begin{align*}
& (w_{i,y} + w_{j,x}) - (w_{i,x} + w_{j,y}) \\
= & (p_x - p_y) (t_i - t_j) + (p_i - p_j) (t_x - t_y)
\end{align*}
$$

发现，在我们单调栈基础上，这四项符号都是固定的，那么式子符号也是固定的。

这样有了四边形不等式，直接决策点单调性即可。

复杂度 $O(n)$，当然我是偷懒写分治的那种人。

## FF
考虑覆盖有拓扑序，然后就是区间前缀min区间后缀min，区间加，区间赋值。

复杂度证明用连续段。还算好写。
