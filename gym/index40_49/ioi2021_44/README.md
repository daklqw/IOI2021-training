## GJ
见过这道题……实际上做法也十分厉害。

首先考虑不满 $K$ 次的，显然就是直接最短路就对了。

超过 $K$ 次的看起来可以二分，但是经过思考，发现带权二分什么是假的。

那么，我们只能枚举第 $K$ 大边权是 $V$。接着只能做最短路。

那么，长度小于 $V$ 的怎么办？总不能负边权吧？看起来 $\max(a - V, 0)$ 挺不错的。

对于最短路方案中，如果第 $K$ 大长度小于 $V$，显然算成 $V$ 时不会统计到最优解里。因为它会在 $V'$ 是第 $K$ 大时得到更小的答案。

长度大于 $V$ 的显然也会增加更多贡献。那么正确性就显然了。

## KE
一堆三分套上去。然而自己想了一个很难做的写法……

然后好做的写法，就是考虑宽度固定，则面积随左下角横坐标凸。

左下角横坐标任意面积随宽度凸。

然后一个位置的上下交点都好求。

然后直接三分就能过了。

还是很好的一道题，像我如果场上碰到估计要开始枚举一条边开始三分了。
