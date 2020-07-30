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


```
