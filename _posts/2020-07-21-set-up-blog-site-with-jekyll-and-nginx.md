---
title: Set up blog site with Jekyll and Nginx
published: true
---

**JekyII** is a simple static site generator based on Ruby. It takes pages input in Markdown, Texttile, Liquid, HTML, and CSS, and outputs complete static HTML pages. Most of the personal blogs are maintained as static sites with simple posts. 

```
# To install Ruby 
$ sudo apt update  # update the packages index
$ sudo apt install ruby-full # install Ruby by typing 
$ ruby --version
ruby 2.7.0p0 (2019-12-25 revision 647ee6f091) [x86_64-linux-gnu]

```

> Simple:

No more databases, comment moderation, or pesky updates to install--just your content.

> Static 

**Markdown**,**Liquid**,HTML&CSS go in. Static sites come out ready for deployment. 

> Blog-aware

Permalinks, categories, pages, posts, and custom layouts are all first-class citizens here.

```
JekyII for write content 
nginx to serve our content 
Capistrano to deploy : A remote server automation and deployment tool written in Ruby
```

Installing Requirements:

```
Install Ruby and RubyGems Ruby Version Manager(RVM)
$ curl -L https://get.rvm.io | bash -s stable --ruby=2.0.0

$ gem install jekyll capistrano
```

Creating a Blog With Jekyll 

```
# see site running 
$ jekyll serve --watch --host 0.0.0.0 --port 80
Configuration file: /var/www/chyidl/_config.yml
            Source: /var/www/chyidl
       Destination: /var/www/chyidl/_site
 Incremental build: disabled. Enable with --incremental
```

Setting Up the Blog for Deployment With Capistrano 

```
# This creates the necessary files for a Capistrano deployment.
$ cap install 
```
