---
title: Launching Linux threads and processes with clone
published: true
---

In fact, for the Linux kernel itself there's absolutely no difference between what userspace sees as processes (the result of **fork**) and as threads (the result of **pthread_create**). Both are represented by the same data structures and scheduled similarly. In kernel nomenclature this is called tasks (the main structure representing a task in the kernel is task_struct), and I'll be using this term from now on.

In Linux, threads are just tasks that share some resources, most notably their memory space; processes, on the other hand, are tasks that don't share resources. For application programmers, processes and threads are created and managed in very different ways. For processes there's a slew of process-management APIs like **fork**, **wait** and so on. For threads there's the **pthread** library. However, deep in the guts of these APIs and libraries, both processes and threads come into existence through a single Linux system call - **clone**.

> The clone system call 

We can think of **clone** as the unifying implementation shared between processes and threads. Whatever perceived difference there is between processes and threads on Linux is achieved through passing different flags to **clone**. Thereforce, it's most useful to think of processes and threads not as two completely different concepts, but rather as two variants of the same concept - staring a concurrent task. The differences are mostly about what is shared between this new task and the task that started it.

```
// We have to define the _GNU_SOURCE to get access to clone(2) and the CLONE_* 
// flags from sched.h 
// 
#define _GNU_SOURCE 
#include <sched.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int child_func(void* arg) {
    char* buf = (char*)arg;
    printf("Child sees buf = \"%s\"\n", buf);
    strcpy(buf, "hello from child.");
    return 0;
}

int main(int argc, char** argv) {
    // Alocate stack for child task.
    const int STACK_SIZE = 65536;
    char* stack = malloc(STACK_SIZE);
    if (!stack) {
        perror("malloc");
        exit(1);
    }

    // When called with the command-line argument "vm", set the CLONE_VM flag on.
    unsigned long flags = 0; 
    if (argc > 1 && !strcmp(argv[1], "vm")) {
        // CLONE_VM flag tells clone to share the virtual memory between the calling task and the new task clone is about to create
        flags |= CLONE_VM;
    }

    char buf[100];
    strcpy(buf, "hello from parent");
    /*
    1. It takes a function pointer to the code the new task will run, similarly to threading APIs, and unlike the fork API.
    This is the glibc wrapper for clone. There's also a raw system call which is discussed below.

    2. The stack for the new task has to be allocated by the parent and passed into clone.

    3. The SIGCHLD flag tells the kernel to send the SIGCHLD to the parent when the child terminates, which lets the parent use the plain wait call to wait for the child to exit.
    */
    if (clone(child_func, stack + STACK_SIZE, flags | SIGCHLD, buf) == -1) {
        perror("clone");
        exit(1);
    }

    int status; 
    if (wait(&status) == -1) {
        perror("wait");
        exit(1);
    }

    printf("Child exited with status %d. buf = \"%s\"\n", status, buf);
    return 0;
}
```

* Calling clone in process and thread creation 

```
glibc: The GNU C Libraru project provides the core libraries for the GNU system and GNU/Linux systems, as well as other systems that use Linux as the kernel. 

Let's dig through in glibc to see how clone is invoked, starting with **fork**, whichi is routed to __libc_fork in sysdeps/nptl/fork.c. 

The actual cloning happens with:
  pid = arch_fork(&THREAD_SELF->tid);

Where arch_fork is a macro defined per architecture (exact syscall ABIs are architecture-specific.) glibc/sysdeps/unix/sysv/linux/arch-fork.h 

Let's turn to pthread_create. Through a dizzying chain of macros it reaches a function named create_thread (defined in sysdeps/unix/sysv/linux/createthread.c) that calls clone with:
```

* Benchmarking process vs. thread creation 

```
Since fork and pthread_create route to the same system call in Linux, the difference would come from the different flags they pass in. When pthread_create passes all these CLONE_* flags, it tells the kernel there;s no need to copy the virtual memory image, the open files, the signal handlers, and so on. Obviously, this saves time.

For processes, there's a bit of copying to be done when fork is invoked, which costs time. The biggest chunk of time probably goes to copying the memory image due to the lack of CLONE_VM. Note, however, that it's not just copying the whole memory; Linux has an important optimization by using COW(Copy On Write) pages. The child's memory pages are initially mapped to the same pages shared by the parent. and only when we modified them the copy happens. This is very important because processes will often use a lot of shared read-only memory (think of the global structures used by the standard library)

Creation time is not the only performance benchmark of importance. It's also interesting to measure how long it takes to switch context between tasks when using threads of processes.
```
