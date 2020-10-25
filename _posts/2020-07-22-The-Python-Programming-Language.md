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

* Special method names 

```
__new__: Called to create a new instance of class cls. The return value of __new__() should be the new object instance (usually an instance of cls)
__init__: Called after the instance has been created (by __new__())

  __new__() and __init__() work together in constructing objects (__new__() to create it, and __init__() to customize it)

__del__: Called when the instance is about to be destroyed.
  del x doesn't directly call x.__del__() - the former decrements the reference count for x by one, and the latter is only called when x's reference count reaches zero

__repr__: Called by the repr() built-in function to compute the "official" string representation of an object. 
  This is typically used for debugging, so it is important that the representation is information-rich and unambiguous

__str__: Called by str(object) and the built-in functions format() and print() to compute the "informal" or nicely printable string representation of an object. The return value must be a string object.

__bytes__: Called by bytes to compute a byte-string representation of an object. This should return a bytes object.

__format__: Called by the format() built-in function, and by extension, evaluation of formatted string literals and the str.format() method, to produce a "formatted" string representation of an object.

__bool__: Called to implement truth value testing and the built-in operation bool() When this method is not defined, __len__() is called, if it is defined, and the object is considered true if its result is nonzero. 

__getattr__: Called when the default attribute access fails with an AttributeError

__setattr__: Called when an attribute assignment is attempted. 

__getattribute__: Called unconditionally to implement attribute accesses for instances of the class.

__delattr__: This should only be implemented if del obj.name is meaning for the object. 

__dir__: Called when dir() is called on the object. A sequence must be retruned. dir() converts the re-turned sequence to a list and sorts it.

__get__: Called to get the attribute of the owner class 

__set__: Called to set the attribute on an instance of the owner class to a new value.

__delete__: Called to delete the attribute on an instance instance of the owner class. 
```

```
Concurrency: 
  Concurrency is when code can run independently of other code. 

Parallelism:
  Parallelism is the execition of concurrent code simultaneously

Parallelism is particularly useful when there's a lot of work to be done in userspace, and that's typically CPU-heavy stuff. 

Greenlets really shine in network programming where interactions with one socket can occur independently of interactions with other sockets. This is good because threads are very expensive in terms of virtual memory and kernel overhead. 

a and b returns b if a is True, else returns a 
a or b returns a if a is True, else return b
```
