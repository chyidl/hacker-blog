---
title: Golang Crash Course
published: true
---

> Go is an open source programming language designed at Google that makes it easy to build simple, reliable, and efficient software.

* Introduction to Go 

```
Creators: 
  Robert Griesemar, Rob Pike, Ken Thompson 

Why a New Language?
  Python: Easy to use, but slow
  Java: Increasingly complex type system 
  C/C++: Complex type system Slow compile times

  focus: Concurrency patched in (at best) 

Go (golang)
  Strong and statically typed
  Excellent community 
  Key features:
    Simplicity 
    Fast compile times 
    Garbage collected
    Built-in concurrency
    Compile to standalone binaries 
```

* Setting Up a Development Environment 

```
$ vim .zshrc 
  export GOROOT=/snap/go/current 
  export PATH=$PATH:$GOROOT/bin
  export GOPATH=/root/golib
  export PATH=$PATH:$GOPATH/bin
  export GOPATH=$GOPATH:/root/goprj 
  # 开启Go module 功能
  export GO111MODULE=on  
  # GOPROXY.IO 配置Goproxy环境变量
  export GOPROXY=https://goproxy.io,direct

$ source .zshrc 

$ go get github.com/nsf/gocode 
$ mkdir ~/goprj/{bin,pkg,src}

fatih/vim-go : Go development plugin for Vim 
  vim-plug: 
    Plug 'fatih/vim-go', {'do': ':GoUpdateBinaries'}
    Install all the nexessary binaries. 
    :GoInstallBinaries # which will go get all the required binaries

gofmt: Gofmt reformats Go source code.
golint: Golint is a linter for Go source code [golint prints out style mistakes]
  The suggestions made by golint are exactly that: suggestions. Golint is not perfect, and has both false positives and false negatives. Do not treat its output as a gold standard.
  $ go get -u golang.org/x/lint/golint  
```

* VARIABLES 

``` 
1. Variable declaration 
  var i int = 42 
  i := 42 
  

2. Redeclaration and shadowing 

3. Visibility

4. Naming conventions 

5. Type conversions 
```
