---
title: Distributed locks with Redis
published: true
---

> DLM (Distributed Lock Manager) 

> Redlock, which implements a DLM 

> Safety and Liveness guarantees
  1. Safety property: Mutal exclusion. At any given moment, only one client can hold a lock. 
  2. Liveness property A: Deadlock free. Eventually it is always possible to acquires a lock, even if the client that locked a resource crashes or gets partitioned.
  3. Liveness property B: Fault tolerance. As long as the majority of Redis nodes are up, clients are able to acquire and release locks.

> The simplest way to use Redis to lock a resource is to create a key in an instance. The key is usually created with a limited time to live, using the Redis expires feature, so that evetually it will get released (property 2 in our list). When the client need to release the resource, it deletes the key. 

> Superficially this works well, but there is a problem: this is **a single point of failure** in our architecture. What happens if the Redis master goes down? Well, let's add a slave! And use it if the master is unavailable. This is unfortuately now viable. By doing so we can't implement our safety property of mutual exclusion, because Redis replication is asynchronous.

> This is an abvious race condition with this model:
  1. Client A acquires the lock in the master 
  2. The master crashes before the write to the key is transmitted to the slave 
  3. The slave gets promoted to master 
  4. Client B acquires the lock to the same resource A already holds a lock for. **SAFETY VIOLATION**!

> Correct implementation with a single instance 

```
# To acquire the lock, the way to go is the following: 
> SET resource_name my_random_value NX PX 30000

# Remove the key only if it exists and the value stored at the key is exactly the one I expect to be.
# This si accomplished by the following **Lua** scripts:
if redis.call("get", KEYS[1]) == ARGV[1] then 
  return redis.call("del", KEYS[1])
else
  return 0 
end 
```

> The system,reasoning about a non-distrubuted system composed of a single, always available, instance, is safe. Let's extend the concept to a distributed system where we don't have such guranttes.

> The Redlock algorithm 

```
Assume have 5 Redis Masters In order to acquire the lock, the client performs the following operations:
  1. It gets the current time in miliseconds 
  2. It tries to acquire the lock in all the N instances sequentially, using the same key name and random value in all the insatnces. During step 2, when setting the lock in each instance, the client uses a timeout which is small compared to the total lock auto-release time in order to acquire it. For example if the auto-release time is 10 seconds, the timeout could be in the ~ 5-20 miliseconds range. This prevents the client from remaining blocked for a long time trying to talk with a Redis node which is down. If an instance is not available, we should try to talk with the next instance ASAP(As soon as possible).
  3. The client computes how much time elapsed in order to acquire the lock. by subtracting from the current time the timestamp obtained in step 1. If and only if the client was able to acquire the lock in the majority of the instance(at least 3), and the total time elapsed to acquire the lock is less than lock validity time, the lock is considiered to be acquired. 
  4. If the lock was acquired, its validity time is considered to be the initial validity time minus the time elapsed, as computed in step 3. 
  5. If the client failed to acquire the lock for some reason (either it was not able to lock N/2 + 1 instances or the validity time is negative), it will try to unlock all the instance (even the instance it believed it was not able to lock)
```

| readlock     | description                   |
|:-------------|:------------------------------|
| Redlock-py   | Python implementation         |
| Aioredlock   | Asyncio Python implementation |
| Redsync      | Go implementation             |


```
75252:C 21 Jul 2020 14:57:58.091 # oO0OoO0OoO0Oo Redis is starting oO0OoO0OoO0Oo
75252:C 21 Jul 2020 14:57:58.092 # Redis version=6.0.6, bits=64, commit=00000000, modified=0, pid=75252, just started
75252:C 21 Jul 2020 14:57:58.092 # Configuration loaded
75252:C 21 Jul 2020 14:57:58.092 # WARNING supervised by systemd - you MUST set appropriate values for TimeoutStartSec and TimeoutStopSec in your service unit.
75252:C 21 Jul 2020 14:57:58.092 # systemd supervision requested, but NOTIFY_SOCKET not found
75252:M 21 Jul 2020 14:57:58.093 * Increased maximum number of open files to 10032 (it was originally set to 1024).
                _._                                                  
           _.-``__ ''-._                                             
      _.-``    `.  `_.  ''-._           Redis 6.0.6 (00000000/0) 64 bit
  .-`` .-```.  ```\/    _.,_ ''-._                                   
 (    '      ,       .-`  | `,    )     Running in standalone mode
 |`-._`-...-` __...-.``-._|'` _.-'|     Port: 6379
 |    `-._   `._    /     _.-'    |     PID: 75252
  `-._    `-._  `-./  _.-'    _.-'                                   
 |`-._`-._    `-.__.-'    _.-'_.-'|                                  
 |    `-._`-._        _.-'_.-'    |           http://redis.io        
  `-._    `-._`-.__.-'_.-'    _.-'                                   
 |`-._`-._    `-.__.-'    _.-'_.-'|                                  
 |    `-._`-._        _.-'_.-'    |                                  
  `-._    `-._`-.__.-'_.-'    _.-'                                   
      `-._    `-.__.-'    _.-'                                       
          `-._        _.-'                                           
              `-.__.-'                                               

75252:M 21 Jul 2020 14:57:58.095 # Server initialized
75252:M 21 Jul 2020 14:57:58.095 # WARNING overcommit_memory is set to 0! Background save may fail under low memory condition. To fix this issue add 'vm.overcommit_memory = 1' to /etc/sysctl.conf and then reboot or run the command 'sysctl vm.overcommit_memory=1' for this to take effect.
75252:M 21 Jul 2020 14:57:58.095 # WARNING you have Transparent Huge Pages (THP) support enabled in your kernel. This will create latency and memory usage issues with Redis. To fix this issue run the command 'echo never > /sys/kernel/mm/transparent_hugepage/enabled' as root, and add it to your /etc/rc.local in order to retain the setting after a reboot. Redis must be restarted after THP is disabled.
75252:M 21 Jul 2020 14:57:58.096 * Ready to accept connections
75252:M 21 Jul 2020 14:57:58.096 # systemd supervision requested, but NOTIFY_SOCKET not found
75252:M 21 Jul 2020 14:57:58.096 # systemd supervision requested, but NOTIFY_SOCKET not found
```
