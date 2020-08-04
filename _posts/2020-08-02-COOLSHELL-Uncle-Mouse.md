---
title: CoolShell - Uncle Mouse
published: true
---

* 别让自己“墙”了自己[https://coolshell.cn/articles/20276.html]
```
小型项目用什么语言都行，真正的企业级架构就不一样，不仅仅只是RESTful API 或 RPC,还有各种配套设施和控制系统，比如:(应用网关，服务发现，配置中心，健康检查，服务监控，服务治理(熔断、限流、幂等、重试、隔离、事务补偿)、Tracing监控、SOA/ESB、CQRS、EDA) Java强大的生态环境，就是让你把注意力放到更高层次的架构和业务上来(千万不要觉得，整几个服务RPC一下，加个缓存，加个队列，就能叫架构，那只是系统集成罢了)
``` 

* 你可能不知道的SHELL 
```
Shell - 操作系统提供访问内核服务的程序 
!$: 上一命令最后一个字符串
  ➜ echo "Say Hello"
  Say Hello
  chyi in ~ at chyi-aapc 
  ➜ !$
  chyi in ~ at chyi-aapc 
  ➜ "Say Hello"

sudo !!: 以root身份执行上一条命令
chyi in ~ at chyi-aapc 
➜ apt update
Reading package lists... Done
E: Could not open lock file /var/lib/apt/lists/lock - open (13: Permission denied)
E: Unable to lock directory /var/lib/apt/lists/
W: Problem unlinking the file /var/cache/apt/pkgcache.bin - RemoveCaches (13: Permission denied)
W: Problem unlinking the file /var/cache/apt/srcpkgcache.bin - RemoveCaches (13: Permission denied)

chyi in ~ at chyi-aapc 
➜ sudo !!

chyi in ~ at chyi-aapc 
➜ sudo apt update 

cd -: 回到上一次目录
cd ~: 回到自己Home目录 
cd ~user: 进入某个用户的Home目录

mtr:(my traceroute) is a command line network diagnostic tool that provides the functionality of both the ping and traceroute commands.
  $ mtr [domainName/IP]


```

* 打造高效的工作环境 - SHELL 
```

```

