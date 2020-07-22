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
> Return True if all elements of the iterable are true (or if the iterable is empty)
```
»> all([1,2,True])
True
»> all([1,2,0])
False
»>
»> all([])
True
»>

# Equivalent to 
def all(iterable):
  for element in iterable:
    if not element:
      return False 
  return True
```

* any(iterable)
> Return True if any element of the iterable is true. If the iterable is empty return False.
```
»> any([])
False
»> any([True, False, False])
True

# Equivalent to 
def any(iterable):
  for element in iterable:
    if element:
      return True 
  return False 
```

* ascii(object)
> As repr(), return a string containing a printable representating of an object, but escape the non-ASCII characters in the string returned by repr() using \x,\u or \U escapes.
```
```

* bin(x) 
> Convert an interger number to a binary string prefixed with "0b".
```
»> bin(1)
'0b1'
»> bin(2)
'0b10'
```

* bool()
> Return a Boolean value, i.e. one of True or False.
```
```

* breakpoint(*args, **kws)

