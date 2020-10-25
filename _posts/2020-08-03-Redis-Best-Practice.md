---
title: Redis Best Practice
published: true
---

> Redis is an open-source, in-memory key-value data store known for its flexibility, performance, and broad language support. A NoSQL database. Redis doesn't use structured query language (otherwise known as SQL) to store, manipulate, and retrieve data.

技术人常见的误区，只关注零散的技术点，不能建立起一套完整框架，缺乏系统观

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

操作接口模型:
  
内存: ns
外存: ms

缓存场景: 数据需要能够快速访问 允许丢失 

一个键值数据库包含:访问框架、索引模块、操作模块、存储模块 
  访问模式:
    1. 通过函数库调用的方式供外部应用使用 
    2. 通过网络架构以Socket通信的形式对外提供键值对操作 
      网络连接的处理、网络请求的解析、以及数据存取的处理是用一个线程、多个线程或者多个进程交互处理 
      不同的I/O模型对键值数据库的性能和扩展性会有不同的影响 
      如果一个线程要处理网络连接，解析请求,数据存取，一旦某一步操作发生阻塞，整个线程就会阻塞，就会降低系统响应速度 
      采用不同线程处理，某个线程的阻塞，其他线程还能正常运行，但是不同线程间如果需要访问共享资源，就会产生线程竞争，会影响效率
  
  索引模块: 
    索引的作用是让键值数据库根据Key找到响应value的存储位置，进而执行操作 
      哈希表: Memcached, Redis 采用哈希表表示key-value索引
        内存键值数据库Redis采用哈希表作为索引，原因在于，其键值数据基本都是保存在内存中，而内存的高性能随机访问特性可以很好地与哈希表O(1)操作复杂度相匹配 
      B+树 
      字典树 
  
  存储模块:
    内存分配器: glibc中的malloc和free 
    持久化功能

高效的数据结构室Redis快速处理数据的基础 

Redis使用哈希表保存所有的键值对，哈希表就是一个数组，数组的每个元素称为哈希桶，
全局哈希表:可以使用O(1)的时间复杂度来快速查找键值对,只需要计算键的哈希值，就可以知道所对应的哈希桶位置，然后可以访问相应的entry 元素 

哈希表冲突问题: Redis解决哈希冲突的方式就是链式哈希
Redis Rehash带来的操作阻塞- 增加现有的哈希桶数量，让逐渐增多的entry元素能在更多桶之间分散保存，减少单桶中的元素数量，

为了rehash操作更高效，Redis默认使用两个全局哈希表：
  1. 哈希表1和哈希表2，一开始，当你刚插入数据时，默认使用哈希表1，此时的哈希表2并没有被分配空间,随着数量逐步增多，Redis开始执行rehash 
  2. 给哈希表2分配更大的空间，例如当前哈希表1大小的两倍 
  3. 给哈希表1中的数据重新映射并拷贝到哈希表2中 (涉及到大量数据拷贝，会造成Redis线程阻塞)
  4. 释放哈希表1的空间 
  
渐进式rehash: 在拷贝数据时，Redis仍然正常处理客户端请求，每处理一个请求时，从哈希表1中第一个索引位置开始，顺带将索引位置上的所有entries拷贝到哈希表2中，等处理下一个请求时，再顺带哈希表1中下一个索引位置的entries. 这样将一次性大量拷贝的开销，分摊到多次处理请求，避免耗时操作，保证数据快速访问 

数据结构的时间复杂度:
  1. 哈希表 O(1)
  2. 跳表 O(logN)
  3. 双向链表 O(N)
  4. 压缩列表 O(N)
  5. 整数数组 O(N)

List类型：POP/PUSH效率高，主要用于FIFO队列场景，而作为可以随机读写集合不适合

Redis单线程主要指Redis网络IO和键值读写是一个线程来完成，其他功能 持久化、异步删除、集群数据同步是由额外的线程执行。

多线程开销:
  使用多线程，增加系统吞吐率 增加系统扩展性 
  多线程编程模式面对的共享资源的并发控制问题 

多路复用机制:
  
  Get请求:
    监听请求bind/listen 
      -> 客户端建立连接 accept 
        -> socket中读取请求 recv 
          -> 解析客户端发送请求 parse  
            -> 根据请求类型读取键值数据 get 
    socket 写回数据 <-

  socket() 方法返回主动套接字 
  listen()方法将主动套接字转化为监听套接字 
  accept方法接收到达客户端连接 -> 返回已连接套接字 

  Linux中的IO 多路复用机制是指一个线程处理多个IO流 select/epoll 机制，该机制允许内核中，同时存在多个监听套接字和已连接套接字，内核会一致监听这些套接字上的连接请求或数据请求。
  FreeBSD kqueue 
  Solaris: evport 

AOF(Appended Only File) 日志 
  Redis 实现数据的持久化，避免从后端数据库中进行恢复，是至关重要的 
  Redis 持久化机制:
    AOF 日志
    RDB 快照

  传统数据库的写前日志 Write Ahead log, WAL: 实际写数据前，先把修改的数据记录到日志文件中，以便故障时进行恢复 
    - redo log 重做日志，记录的是修改后的数据
  AOF日志：Redis先执行命令，把数据写入内存，然后才记录日志 
    - aof记录的是Redis收到的每一条命令，这些命令是以文本形式保存 
  
  写后日志这种方式，先让系统执行命令，只有命令执行成功，才会被记录入职，否则，系统就会直接向客户端报错，Redis使用写后日志这种方式，可以避免出现记录错误命令的情况 

  AOF 在命令执行后才记录日志，所以不会阻塞当前写操作 

  AOF 潜在风险:
    1. 执行完命令，但是没有及时记录日志 宕机 因此命令没有记录日志，所以无法使用日志进行恢复
    2. AOF避免对当前命令的阻塞，但是会对写一个操作带来阻塞风险 AOF日志也是在主线程中执行，如果磁盘写压力大，就会导致写磁盘很慢，进而导致后续操作无法执行 

  AOF 写盘时机:
    appendfsync Always: 同步写回，每个写命令执行完，立马同步将日志写会磁盘 -- 影响主线程性能
    appendfsync Everysec: 每秒写回，每个写命令执行完，只是先把日志写入AOF文件的内存缓冲区，每隔一秒把缓冲区中的内容写入磁盘 
    appendfsync No: 操作系统控制写回，每个写命令执行完，只是先把日志写到AOF文件的内存缓冲区，由操作系统决定将缓冲区内容写会磁盘 

  AOF 文件过大性能问题:
    1. 文件系统本身对文件大小限制，无法保存过大文件 
    2. 文件过大，里面追加命令记录 效率会变低，
    3. 如果发生宕机，AOF中记录的命令要一个个被重新执行，用于故障恢复 

  AOF 重写机制:
    AOF重写机制就是在重写时，Redis根据数据库现状创建一个新的AOF文件，重写机制具有“多变一”旧日志文件中的多条命令在重写的新日志中变成一条命令 
    重写AOF 文件需要把整个数据库的最新数据的操作日志都写回磁盘，重写过程是由后台线程bgrewriteaof完成 避免阻塞主线程
    Redis每次执行重写时，主线程fork出后台的bgrewriteaof子进程，fork会把主线程的内存拷贝一份给bgrewriteaof子进程，然后bgwriteaof子进程就可以在不影响主线程的情况下，逐一拷贝数据写成操作，记入重写日志 
    AOF日志缓冲区 
    AOF重写日志缓冲区 
    使用新的AOF文件替换旧文件 

  Trade Off: 取舍 
    
内存快照RDB (Redis Database)
  > snapshot 内存快照是指内存中的数据在某一个时刻的状态记录
  保证可靠性 还能在宕机时实现快速恢复 
  AOF 日志进行故障恢复的时候需要逐一把操作日志执行一遍 
  RDB 记录的是某一时刻的数据，并不是操作，在做数据恢复时，可以直接把RDB文件读入

  Redis提供两个命令生成RDB文
    1. save: 在主线程中执行 会导致阻塞
      
    2. bgsave: 创建一个子进程 专门用于写入RDB文件,避免主线程的阻塞
    COW (Copy-On-Write) 写时复制技术 在执行快照的同时正常处理写操作(操作系统提供)
      1. 频繁将全量数据写入磁盘，会给磁盘带来很大压力，多个快照竞争有限的磁盘带宽
      2. bgsave 子进程需要通过fork操作从主线程创建出来

  Redis 4.0 混合使用AOF日志和内存快照：内存快照以一定的频率执行，在两次快照之间，使用AOF日志记录期间的所有命令操作. 这种方法既能享受RDB文件快速恢复和AOF记录操作命令简单的优势 

数据同步 
  高可靠性:
    1. 数据尽量少丢失 (AOF, RDB)
    2. 服务尽量少中断 (增加副本冗余)
      主从库模式: 保证数据副本一致，主从库之间采用的是读写分离
        读操作：主库、从库都可以
        写操作: 首先到主库，然后主库将写操作同步给从库
  Redis 建立主从模式：
    replicaof:
    slaveof:
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

Redis单线程处理IO请求性能瓶颈:
  1. 任意一个请求在server中一旦发生耗时，都会影响整个server的性能,耗时操作包括以下几种
    1.1: 操作bigkey: 写入一个bigkey在分配内存时需要消耗更多的时间，同样，删除bigkey释放内存同样产生耗时 
    1.2: 使用复杂度过高的命令: SORT,SUNION,ZUNIONSTORE 或者O(n)命令 
    1.3: 大量key几种过期，Redis的过期机制是在主线程中执行的，大量key集中过期会导致处理一个请求时，耗时都在删除过期key耗时变长
    1.4: 淘汰策略:淘汰策略也是在主线程执行，当内存超过Redis内存上限后，每次写入都需要淘汰一些key,也会造成耗时变长。
    1.5: AOF 刷盘开启always机制，每次写入都需要把这个操作刷到磁盘，写磁盘的速度远比内存慢，会拖慢Redis性能 
    1.6: 主从全量同步生成RDB：虽然采用fork子进程生成数据快照，但fork瞬间也是会阻塞整个线程 实例越大，阻塞时间越久 
    - 需要业务人员规避，
    - Redis 4.0推出的lazy-free机制，把bigkey 释放内存的耗时操作放在异步线程中执行，降低主线程的影响
  2. 并发量非常大时，单线程读写客户端IO数据存在性能瓶颈，虽然采用IO多路复用机制，但是读写客户端数据依旧是同步IO，只能单线程一次读区客户端的数据，无法利用到CPU多核
    - Redis 6.0 推出多线程 可以在高并发场景下利用CPU多核多线程读写客户端数据，进一步提升server性能，只是针对客户端的读写是并行的，每个命令的真正操作依旧是单线程的


select, epoll , poll:
  select 和 poll本质上没啥区别，就是文件描述符数量的限制，select根据不同系统，文件描述符限制为1024或者2048，poll没有数量限制，他们都是把文件描述符集合保存在用户态，每次把集合传入内核态，内核态返回ready的文件描述符 

  epoll 是通过epoll_create和epoll_ctl和epoll_await三个系统调用完成，每当接入一个文件描述符，通过ctl添加到内核维护的红黑树中，通过事件机制，当数据ready后，从红黑树移动到链表，通过await获取链表中准备好数据的fd，程序处理 

Redis Persistence: 
  
Redis Transaction:
  > Redis allows plan a sequence of commands and run them one after another, a procedure known as a transation. 
  > Each transaction is treated as an uninterrupted and isolated operation, which ensures data integrity 
  > Client cannot run commands while a transaction block is being executed.
  
  **MULT**, **EXEC**, **DISCARD**, **WATCH** are the foundation of transactions in Redis. They allow the execution of a group of commands in a single step, with two important guarantees. 
    All the commands in a transaction are serialized and executed sequentially. This gurantees that the commands are executed as a single isolated operation. 
    Either all of the commands or none are processed, so a Redis transaction is also atomic. The **EXEC** command triggers the execution of all the commands in the transaction
  **redis-check-aof**: 
    
```
