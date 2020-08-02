---
title: Kubernetes Docker
published: true
---

> Cgroups:

用来制造约束的主要手段 

> Namespace:

用来修改进程试图的主要手段

* experiment

```
BusyBox combines tiny versions of many common UNIX utilities into a single small executable. It provides replacements for most of the utilties you usually find in GNU fileutils, shellutils, etc.
  -i: Keep STDIN open even if not attached 
  -t: Allocate a pseudo-tty
$ docker run -it busybox /bin/sh 
Unable to find image 'busybox:latest' locally
latest: Pulling from library/busybox
61c5ed1cbdf8: Pull complete 
Digest: sha256:4f47c01fa91355af2865ac10fef5bf6ec9c7f42ad2321377c21e844427972977
Status: Downloaded newer image for busybox:latest
/ # ps
PID   USER     TIME  COMMAND
  1   root     0:00  /bin/sh
  6   root     0:00  ps

Docker uses a technology called namespace to provide the isolated workspace called the container. When you run a container, Docker creates a set of namespaces for that container. These namespace provide a layer of isolation.

-- CLONE_NEWPID
int pid = clone(main_function, stack_size, CLONE_NEWPID | SIGCHLD, NULL); 

-- isolation containers with a user namespace 
  Linux namespace provide isolation for running processes, limiting their access to system resouces without the running process being aware of the limitations. 
  PID Namespace: 
  Mount Namespace: 用于被隔离进程只看到当前Namespace挂载点信息
  UTS Namespace: 
  IPC Namesapce: 
  Network Namesapce: 用于被隔离进程看到当前Namespace 网络设备和配置
  User Namesapce: 

容器，其实是一种特殊的进程而已 
在使用Docker的时候，并没有一个真正的"Docker容器"运行在宿主机里面，Docker项目帮助用户启动的，还是原来的应用程序，只不过在创建这些进程时，Docker为他们加上各种各样的Namespace参数. 

Linux CGroups 就是Linux内核中用来为进程设置资源
Linux CGroups - Linux Control Group 限制一个进程组能够使用的资源上限
  /sys/fs/cgroup/ 
➜ mount -t cgroup
cgroup on /sys/fs/cgroup/systemd type cgroup (rw,nosuid,nodev,noexec,relatime,xattr,name=systemd)
cgroup on /sys/fs/cgroup/net_cls,net_prio type cgroup (rw,nosuid,nodev,noexec,relatime,net_cls,net_prio)
cgroup on /sys/fs/cgroup/devices type cgroup (rw,nosuid,nodev,noexec,relatime,devices)
cgroup on /sys/fs/cgroup/cpu,cpuacct type cgroup (rw,nosuid,nodev,noexec,relatime,cpu,cpuacct)
cgroup on /sys/fs/cgroup/memory type cgroup (rw,nosuid,nodev,noexec,relatime,memory)
cgroup on /sys/fs/cgroup/pids type cgroup (rw,nosuid,nodev,noexec,relatime,pids)
cgroup on /sys/fs/cgroup/cpuset type cgroup (rw,nosuid,nodev,noexec,relatime,cpuset)
cgroup on /sys/fs/cgroup/perf_event type cgroup (rw,nosuid,nodev,noexec,relatime,perf_event)
cgroup on /sys/fs/cgroup/freezer type cgroup (rw,nosuid,nodev,noexec,relatime,freezer)
cgroup on /sys/fs/cgroup/rdma type cgroup (rw,nosuid,nodev,noexec,relatime,rdma)
cgroup on /sys/fs/cgroup/blkio type cgroup (rw,nosuid,nodev,noexec,relatime,blkio)
cgroup on /sys/fs/cgroup/hugetlb type cgroup (rw,nosuid,nodev,noexec,relatime,hugetlb)

➜ ls /sys/fs/cgroup/cpu
cgroup.clone_children  cpuacct.usage             cpuacct.usage_percpu_user  cpu.cfs_quota_us  notify_on_release
cgroup.procs           cpuacct.usage_all         cpuacct.usage_sys          cpu.shares        release_agent
cgroup.sane_behavior   cpuacct.usage_percpu      cpuacct.usage_user         cpu.stat          systemd
cpuacct.stat           cpuacct.usage_percpu_sys  cpu.cfs_period_us          kubepods          tasks 

chyi in fs/cgroup/cpu  at chyi-aapc 
➜ sudo mkdir container/

chyi in cgroup/cpu/container  at chyi-aapc 
➜ pwd                 
/sys/fs/cgroup/cpu/container

chyi in cgroup/cpu/container  at chyi-aapc 
➜ ls
cgroup.clone_children  cpuacct.usage         cpuacct.usage_percpu_sys   cpuacct.usage_user  cpu.shares      cpu.uclamp.min
cgroup.procs           cpuacct.usage_all     cpuacct.usage_percpu_user  cpu.cfs_period_us   cpu.stat        notify_on_release
cpuacct.stat           cpuacct.usage_percpu  cpuacct.usage_sys          cpu.cfs_quota_us    cpu.uclamp.max  tasks

chyi in ~ at chyi-aapc  
➜ while : ; do : ; done &  # exec loop cpu 
[1] 72408

chyi in cgroup/cpu/container  at chyi-aapc 
✦ ➜ cat cpu.cfs_quota_us 
-1 # 无限制
chyi in cgroup/cpu/container  at chyi-aapc 
✦ ➜ cat cpu.cfs_period_us 
100000 # 100ms

chyi in cgroup/cpu/container  at chyi-aapc 
✦ ➜ sudo sh -c "echo 20000 > /sys/fs/cgroup/cpu/container/cpu.cfs_quota_us"

chyi in cgroup/cpu/container  at chyi-aapc 
✦ ➜ sudo sh -c "echo 75319 > /sys/fs/cgroup/cpu/container/tasks"

blkio: 为快设备设定I/O 限制,一般用于磁盘 
cpuset: 为进程分配单独的CPU核和对应的内存节点 
memory: 为进程设定内存使用的限制 

容器的本质是一种特殊的进程 
```

