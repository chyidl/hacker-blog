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
        flags |= CLONE_VM;
    }

    char buf[100];
    strcpy(buf, "hello from parent");
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

/**
 * This code smaple passes a buffer into the child, and the child writes a string into it. When called without the vm command-line argument, the CLONE_VM flag is off, and the parent's virtual memory is copied into the child. The child sees the message the parent placed in buf, but whatever it writes into buf goes into its own copy and the parent can't see it.
 *
 * gcc -o clone-vm-sample clone-vm-sample.c 
 * ./clone-vm-sample 
 * Child sees buf = "hello from parent"
 * Child exited with status 0. buf = "hello from parent"
 * 
 * But when the vm argument is passed, CLONE_VM is set and the child task shares the parent's memory. Its writing into 
 * buf will now be observable from the parent.
 *
 * ./clone-vm-smaple vm 
 * Child sees buf = "hello from parent"
 * Child exited with status 0. buf = "hello from child."
 * */
