## CK
说起来挺简单的，但是题目读错了 N 遍，所以不断 WA。

注意，N 层只能套 N - 1 层，而且不能出现并列。

也就是不能像括号序列那样（开始理解成括号序列深度了），例如：`()(())`就是错的。

那一切都简单了。枚举答案，显然级别是 $O(\sqrt{nv})$。

然后发现如果一层里多个并列 $\{K, K-1, K, K, K-1, K\}$，则我们归纳，中间的几个都可以变成 $K = 1$，也就是两个引号并列。

例如 `''','',',',',',',','','''`。

然后直接枚举前缀，奇偶性判判就好了。

## OG
显然回文树 DP，然后枚举一个回文串剩下的全部是单加。

有两种转移：往两边加，往中间加。

往两边加直接枚举转移边。

往中间加，枚举 fail，于是在加入点的同时维护一半长度的点的标号。

注意无论是否新建点都要更新这个标号。

然后直接 DP 就好了。

## DB
怎么说呢……我脑子被啥踢了去写爆搜……

实际上直接状压随便搞搞就过的东西。
