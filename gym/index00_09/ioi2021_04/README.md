## HL
不会数三.jpg

猜测和很小，然后直接 DP，直接暴力找长度和 $\leq K$ 时最后一个串是啥。

甚至不用剪枝。

## MI
首先无解判断很简单。

我们尝试把无解的判断拿过来做。

然后发现直接可以 dp 了！

对于每个方向，存它匹配到了哪一位。

然后写挂了一个细节……
