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

```

| readlock     | description                   |
|:-------------|:------------------------------|
| Redlock-py   | Python implementation         |
| Aioredlock   | Asyncio Python implementation |
| Redsync      | Go implementation             |
