---
title: Coll New Features in Python 
published: true
---

## Python 3.8

* The Walrus assignment expressions (:=)
> Assignment expressions allow you to assign and return a value in the same expression

```
Python 3.8.5 (default, Jul 28 2020, 12:59:40)
Type 'copyright', 'credits' or 'license' for more information
IPython 7.18.1 -- An enhanced Interactive Python. Type '?' for help.

In [1]: print(walrus := True)
True

In [2]: walrus = False

In [3]: print(walrus)
False

In [4]:
```

* Positional-Only Arguments
>  use / to denote that all arguments before it must be specified by positon
>  can specify keyword-only arguments using the star(*). Any argument after * must be specified using a keyword
```
In [1]: def incr(x, /):
   ...:     return x + 1
   ...:

In [2]: incr(3.8)
Out[2]: 4.8

In [3]: incr(x=3.8)
---------------------------------------------------------------------------
TypeError                                 Traceback (most recent call last)
<ipython-input-3-982270385843> in <module>
----> 1 incr(x=3.8)

TypeError: incr() got some positional-only arguments passed as keyword arguments: 'x'

In [4]:
```

* More Precise Types 
> Literal types 
> Typed dictionaries
> Final objects 
> Protocols 
> type hints allow static type checkers to do type checking of your Python code, without actually running your scripts. Additionally, type hints act as documentation of your code, making it easier to read, as well as improving auto-complete in your IDE
```
In [4]: def double(number: float) -> float:
   ...:     return 2 * number
   ...:
# Python treats these annotations as hints. They are not enforced at runtime
```
