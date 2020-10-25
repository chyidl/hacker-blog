---
title: Coding Principle & Rule
published: true
---

* 定律
  1. 90-9-1 法则 (90-9-1 Principle or 1% Rule) 
```
法则表明, 互联网社区中, 90%用户只看内容并不参与互动, 9%用户参与讨论, 1% 用户会创造内容
```
  2. 阿姆达尔定律 (Amdahl's Law)
```
阿姆达尔定律是一个显示计算任务潜在加速能力的公式，这种能力可以通过增加系统资源实现，通常用于并行计算中，可以预测增加处理器数量的实际好处，然而增加处理器数量会受到程序并行性的限制
```
  3. 玻窗效应 (The Broken Windows Theory)
```
破窗理论应用于软件开发中，表明劣质代码(Technical Debt 技术债务)可能会影响后续优化的效率，从而进一步造成代码劣质，随着时间推移，这种效应将会导致代码质量大幅下降
```
  4. 布鲁克斯法则(Brooks's Law)
```
软件开发后期，添加人力只会使的项目开发的更慢.
这个定律表明，在许多情况下，视图通过增加人力来加速已延期项目的交付，将会使项目交付得更晚
```
  5. CAP定理 (CAP Theorem or Brewer's Theorem)
```
指出对于分布式数据存储来说，不可能同时满足一下三点:
  1. 一致性(Consistency): 在读取数据时，每个请求都会接收到最新的数据，或者返回错误 
  2. 可用性(Availability): 在读取数据时，每个请求都会接收到一个非错误的响应，但是不能保证该数据是最新的数据 
  3. 分区容错性 (Partition Tolerance): 当节点之间任意数量的网络请求失败时，系统能按照预期继续运行
```
  6. 康威定律 (Conway's Law)
```
康威定律表明，如果一个组织被分散成许多小而无联系的单元，那么它开发的软件也是小而分散的，如果组织是更多地围绕以功能或服务为导向的垂直结构，那么软件系统也会反应这一点
```
  7. 坎宁汉姆定律(Cunninghanm's Law)
```
在网络上想得到正确答案的最好不是提问题，而是发布一个错误的答案
```
  8. 邓巴数字 (Dunbar's Number)
```
邓巴数字是对一个人能够保持稳定社会关系的人数的认知极限
```
  9. 费茨法则 (Fitts's Law)
```

```
  10. 盖尔定律 (Gall's Law)
```
一个切实可行的复杂系统势必是从一个切实可行的简单系统发展而来的，从头开始设计的复杂系统根本不切实可行，无法修修补补让它切实可行,无法修修补补让它切实可行，你必须由一个切实可行的简单系统重新开始.
```
  11. 古德哈特定律 (GoodHart's Law)
```
  由测量驱动的优化反而可能导致测量结果本身的说服力下降，盲目使用一些过度严格筛选的方式KPIs可能会产生一些不良的影响，人们会倾向于用"钻空子"的行为去做局部优化，从而满足一些特定的度量标准，而不会在意整体的结果
```
  12. 汉隆的剃刀 (Hanlon's Razor)
```
  能解释为愚蠢的，就不要解释为恶意的
```
  13. 席克定律 (Hick's Law or Hick-Hyman Law)
```
决策时间和可供选择的选项数量呈对数增长关系
```
  14. 侯世达定律 (Hofstadter's Law)
```
即使考虑到侯世达定律，他也总是比你预期的要长 
```
  15. 哈伯特定律 (Hutber's Law)
```
改善即恶化;
对一个系统的改进会导致其他部分的恶化，或者它会将其他的恶化隐藏起来，并导致系统整体状态的退化
```
  16. 技术成熟曲线 (The Hype Cycle or Amara's Law)
```
我们倾向于高估技术短期内的影响，并低谷长期效应
```
  17. 隐式接口定律 (Hyrum's Law or The Law of Implicit Interfaces)
```
当API有足够多的用户时，你在合同中的承诺已不重要，你系统的所有可观察行为都将被某些人所依赖
```
  18. 柯林汉定律 (Kernighan's Law)
```
调试在一开始就比编写程序困难一倍，因此，按照定义，如果你的代码写得非常巧妙，那么你就没有足够的能力开调试它
```
  19. 林纳斯定律 (Linus's Law)
```
足够多的眼镜，就可让所以问题浮现
如果有足够大的测试员和联合开发人员基础，那么几乎每个问题都能很快被特征化，从而让以前遇到过类似的人解决
```
  20. 梅特卡夫定律 (Metecalfe's Law)
```
在网络理论中，系统的价值约等于系统用户数的平方
```
  21. 摩尔定律 (Moore's Law)
```
集成电路中的晶体管数量大约每两年翻一番
```
  22. 墨菲定律 (Murphy's Law)
```
凡事可能出错的事就一定会出错
```
  23. 奥卡姆剃刀 (Occam's Razor)
```
如无必要，勿增实体
```
  24. 帕金森定理(Parkinson's Law)
```
在工作能够完成的时限内，工作量一直增加，知道所有可用时间都被填满为止
```
  25. 过早优化效应 (Permature Optimization Effect)
```
过早优化时万恶之源
```
  26. 普特定律 (Putt's Law)
```
技术由两类人主导，一类是纯粹的管理人员，一类是纯粹的技术人员
```
  27. 里德定律 (Reed's Law)
```
大型网络，尤其时社交网络的效用会随着网络的大小呈指数级扩增
```
  