---
title: Redis Best Practice
published: true
---

技术人常见的误区，只关注零散的技术点，不能建立起一套完整的只是框架，缺乏系统观

![Redis Problem self portait](images/redis-problem-self-portrait.jpeg?raw=true)

* 基础篇

```
基本的数据模型 
  key-value模型: 
    value类型：
      Memcached: 支持的value类型String类型 
      Redis:支持的value包括String,Hash,List,Set 

  SET 写入或更新 key-value 对 
  GET: 根据一key读取相应的value值 
  DELETE: 根据一个key删除整个key-value对 
  SCAN: 

内存


  
```

* 实践篇 

```

```

* FAQ

```
1. Redis的Key和数据结构应该怎么设计？
2. Redis集群如何均衡数据？如何横向扩展？
3. 怎么保证数据的一致性？热点数据的问题怎么解决?
4. RDB 持久化生成的数据快照，每次更新是全量更新还是增量更新?
5. 缓存雪崩、缓存穿透、缓存预热、缓存更新、缓存降级等问题怎么解决?
6. 如何高效阅读Redis源代码?

单线程的Redis而言，任何阻塞性操作都会导致长尾延迟的产生，
Redis网络IO使用的IO复用机制，不会阻塞在单个客户端上 

Redis 知识全景图
  1.应用维度 : 缓存应用、集群应用、数据结构应用
  2.系统维度 : 
    2.1: 处理层: 线程模型 - 
    2.2: 内存层: 数据结构 哨兵机制
    2.3: 存储层: AOF RDB
    2.4: 网络层: epoll网络架构

1. CPU 
2. MEM 
3. Store 
4. Network 

高性能主线：线程模型、数据结构、持久化、网络框架 
高可用主线：主从复制、哨兵机制 
高可用主线：数据分片、负载均衡 
```
