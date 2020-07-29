---
title: The Python Programming Language
published: true
---

### Built-in Functions 

* abs(x)

```
»> abs(-1)
1
»> abs(-1.0)
1.0
»> class A:
…     def __abs__(self):
…             return "This is abs function return"
...
»> a = A()
»> abs(a)
'This is abs function return'
```

* all(iterable)

Return True if all elements of the iterable are true (or if the iterable is empty)

```
»> all([1,2,True])
True
»> all([1,2,0])
False
»>
»> all([])
True
»>

Equivalent to 
def all(iterable):
  for element in iterable:
    if not element:
      return False 
  return True
```

* any(iterable)

Return True if any element of the iterable is true. If the iterable is empty return False.

```
»> any([])
False
»> any([True, False, False])
True

// Equivalent to 
def any(iterable):
  for element in iterable:
    if element:
      return True 
  return False 
```

* ascii(object)

As repr(), return a string containing a printable representating of an object, but escape the non-ASCII characters in the string returned by repr() using \x,\u or \U escapes.

```
```

* bin(x) 

Convert an interger number to a binary string prefixed with "0b".

```
»> bin(1)
'0b1'
»> bin(2)
'0b10'
```

* bool()

Return a Boolean value, i.e. one of True or False.

```
```

* breakpoint(*args, **kws)

* getattr(object, name[, default])

Return the value of the named attribute of object. For example, getattr(x, 'foobar') is equivalent to x.foobar. If the named attribute does not exist, de-fault returned if provided, otherwise AttributeError is raised.

```
»> getattr(int, '__doc__')
"int([x]) -> integer\nint(x, base=10) -> integer\n\nConvert a number or string to an integer, or return 0 if no arguments\nare given.  If x is a number, return x.__int__().  For floating point\nnumbers, this truncates towards zero.\n\nIf x is not a number or if base is given, then x must be a string,\nbytes, or bytearray instance representing an integer literal in the\ngiven base.  The literal can be preceded by '+' or '-' and be surrounded\nby whitespace.  The base defaults to 10.  Valid bases are 0 and 2-36.\nBase 0 means to interpret the base from the string as an integer literal.\n>>> int('0b100', base=0)\n4"
```

```
Concurrency: 
  Concurrency is when code can run independently of other code. 

Parallelism:
  Parallelism is the execition of concurrent code simultaneously

Parallelism is particularly useful when there's a lot of work to be done in userspace, and that's typically CPU-heavy stuff. 

Greenlets really shine in network programming where interactions with one socket can occur independently of interactions with other sockets. This is good because threads are very expensive in terms of virtual memory and kernel overhead. 
```
