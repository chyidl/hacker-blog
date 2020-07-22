---
title: The Rust Programming Language 
published: true
---

> Change crates.io repository
```
$ vim ~/.cargo/config 
[source.crates-io]
registry = "https://github.com/rust-lang/crates.io-index"
replace-with = 'ustc'
[source.ustc]
registry = "git://mirrors.ustc.edu.cn/crates.io-index"
```
