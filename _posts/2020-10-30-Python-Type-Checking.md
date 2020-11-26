---
title: Python Type Checking
published: true
---

> Traditionally, types have been handled by the Python interpreter in a flexible but implicit way. Recent versions of Python allow you to specify explicit type hints that can be used by different tools to help you develop your code more efficiently

* Dynamic Typing 
> Python is a dynamically typed language. This means that the Python interpreter does type checking only as code runs, and that the type of variable is allowed to change over its lifetime
> type() returns the type of an object.
```
In [5]: if False:
   ...:     1 + "two"
   ...: else:
   ...:     1 + 2
   ...:

In [6]: thing = "Hello"

In [7]: type(thing)
Out[7]: str

In [8]: thing = 28.1

In [9]: type(thing)
Out[9]: float
```

* Static Typing
> static typing, variables generally are not allowed to change types, although mechanisms for casting a variable to a different type may exist


* Duck Typing 
> If it walks like a duck and it quacks like a duck, then it must be a duck
> Using duck typing you do not check types at all, Instead you check the presence of a given method or attribute
```
In [10]: class TheHobbit:
    ...:     def __len__(self):
    ...:         return 9527
    ...:

In [11]: the_hobbit = TheHobbit()

In [12]: len(the_hobbit)
Out[12]: 9527
```

* Hello Types 
> Adding type hints like this has no runtime effect, they are only hints and are not enforced on their own.
```
>>> def headline(text, align=True):
...     if align:
...             return f"{text.title()}\n{'-' * len(text)}"
...     else:
...             return f" {text.title()} ".center(50, "o")
...
>>> print(headline("python type checking"))
Python Type Checking
--------------------
>>> print(headline("python type checking", align=False))
oooooooooooooo Python Type Checking oooooooooooooo
>>> def headline(text: str, align: bool =True) -> str:
...     if align:
...             return f"{text.title()}\n{'-' * len(text)}"
...     else:
...             return f" {text.title()} ".center(50, "o")
...
>>> print(headline("python type checking"))
Python Type Checking
--------------------
>>> print(headline("python type checking", align=False))
oooooooooooooo Python Type Checking oooooooooooooo
>>>
```

* Pros and Cons
> Type hints help catch certain errors 
> Type hints help document code. 
> Type hints improve IDEs and linters
> Type hints help you bind and maintain a cleaner architecture
>
> Type hints take developer time and effort to add.
> Type hints work best in modern Pythons
> Type hints introduce a slight penalty in start-up time

> types will have no effect on your running program or the users of your program. Type checking is meant to make your life as a developer better and more convenient.
```
# Measuring Import Time

create two files: empty_file.py should be an empty file, while import_typing.py should contain the following line:
  import typing

On Linux it's quite easy to check how much time the typing import takes using the perf utility
$ perf stat -r 1000 python3 import_typing.py
➜ sudo perf stat -r 1000 python3 import_typing.py

 Performance counter stats for 'python3 import_typing.py' (1000 runs):

             57.77 msec task-clock                #    0.988 CPUs utilized            ( +-  0.05% )
                 1      context-switches          #    0.009 K/sec                    ( +-  6.10% )
                 0      cpu-migrations            #    0.000 K/sec
             1,094      page-faults               #    0.019 M/sec                    ( +-  0.00% )
       122,045,074      cycles                    #    2.113 GHz                      ( +-  0.03% )
        66,823,764      instructions              #    0.55  insn per cycle           ( +-  0.00% )
        14,941,257      branches                  #  258.631 M/sec                    ( +-  0.00% )
           821,228      branch-misses             #    5.50% of all branches          ( +-  0.01% )

         0.0584711 +- 0.0000276 seconds time elapsed  ( +-  0.05% )

$ perf stat -r 1000 python3 empty_file.py
➜ sudo perf stat -r 1000 python3 empty_file.py

 Performance counter stats for 'python3 empty_file.py' (1000 runs):

             31.79 msec task-clock                #    0.979 CPUs utilized            ( +-  0.08% )
                 0      context-switches          #    0.010 K/sec                    ( +-  7.91% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +-100.00% )
               808      page-faults               #    0.025 M/sec                    ( +-  0.00% )
        65,140,292      cycles                    #    2.049 GHz                      ( +-  0.04% )
        37,919,688      instructions              #    0.58  insn per cycle           ( +-  0.00% )
         8,396,603      branches                  #  264.154 M/sec                    ( +-  0.00% )
           441,610      branch-misses             #    5.26% of all branches          ( +-  0.01% )

         0.0324760 +- 0.0000249 seconds time elapsed  ( +-  0.08% )

Using timeit 
timeit truggles to time imports reliably because Python is clever about importing modules only once.
$ python3 -m timeit "import typing"
1000000 loops, best of 5: 247 nsec per loop

What timeit has actually done is to run the import typing statement 30 million times, with Python actually only importing typing once.

The New importtime Option:
➜ python3 -X importtime import_typing.py
import time: self [us] | cumulative | imported package
import time:      1708 |       1708 | _frozen_importlib_external
import time:       372 |        372 |   time
import time:      1043 |       1414 | zipimport
import time:       155 |        155 |     _codecs
import time:      1072 |       1226 |   codecs
import time:       992 |        992 |   encodings.aliases
import time:      1677 |       3893 | encodings
import time:       658 |        658 | encodings.utf_8
import time:       545 |        545 | _signal
import time:       754 |        754 | encodings.latin_1
import time:       107 |        107 |     _abc
import time:       655 |        762 |   abc
import time:       838 |       1600 | io
import time:       155 |        155 |       _stat
import time:       747 |        901 |     stat
import time:      2630 |       2630 |     _collections_abc
import time:       390 |        390 |       genericpath
import time:       735 |       1124 |     posixpath
import time:      1655 |       6309 |   os
import time:       600 |        600 |   _sitebuiltins
import time:      1213 |       1213 |     apport_python_hook
import time:       497 |       1710 |   sitecustomize
import time:       272 |        272 |   usercustomize
import time:      1676 |      10564 | site
import time:       193 |        193 |       _operator
import time:       837 |       1029 |     operator
import time:       474 |        474 |     keyword
import time:       312 |        312 |       _heapq
import time:       555 |        867 |     heapq
import time:       288 |        288 |     itertools
import time:       708 |        708 |     reprlib
import time:       209 |        209 |     _collections
import time:      2073 |       5643 |   collections
import time:       617 |        617 |   collections.abc
import time:       161 |        161 |       _functools
import time:      1579 |       1740 |     functools
import time:       817 |        817 |     types
import time:      3445 |       6001 |   contextlib
import time:      1876 |       1876 |     enum
import time:       187 |        187 |       _sre
import time:      1046 |       1046 |         sre_constants
import time:      1107 |       2153 |       sre_parse
import time:       885 |       3224 |     sre_compile
import time:       257 |        257 |     _locale
import time:       621 |        621 |     copyreg
import time:      1839 |       7814 |   re
import time:      4854 |      24927 | typing
```

* Annotations 
> 
