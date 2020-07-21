---
title: Using Nginx+Hack theme Build Blog on Ubuntu
published: true
---

Using Cerbot to obtain a free SSL certificate for Nginx on Ubuntu 20.04 and set up certificate to renew automatically.

* Prerequistes
  - Ubuntu 20.04 server set up
  - A registered domain name
  - The DNS records set up for your server.
    * An A record with exmaple.com pointing to your server's public IP address.
  - Nginx installed 
    * $ sudo apt update && sudo apt install nginx  # install Nginx and any required dependencies to your server
    * $ sudo ufw app list # List the application configuration the ufw knows how to work
      Available applications:
        Nginx Full # This profile opens both port 80(normal, unencrypted web traffic) and port 443 (TLS/SSL encrypted traffic)
        Nginx HTTP # This profile opens only port 80 (normal, unencrypted web traffic)
        Nginx HTTPS # This profile opens only port 443 (TLS/SSL encrypted traffic)
        OpenSSH
    * $ sudo ufw allow 'Nginx HTTP' 
      Rules updated
      Rules updated (v6)
    * $ sudo ufw status # verify the change 
    * sudo systemctl status nginx # Checking Web Server  
      ● nginx.service - A high performance web server and a reverse proxy server
       Loaded: loaded (/lib/systemd/system/nginx.service; enabled; vendor preset: enabled)
       Active: active (running) since Sun 2020-07-19 15:03:48 CST; 2h 7min ago
         Docs: man:nginx(8)
       Main PID: 9111 (nginx)
          Tasks: 2 (limit: 2319)
         Memory: 6.3M
         CGroup: /system.slice/nginx.service
                 ├─9111 nginx: master process /usr/sbin/nginx -g daemon on; master_process on;
                 └─9112 nginx: worker process

        Jul 19 15:03:48 chyidl.com systemd[1]: Starting A high performance web server and a reverse proxy server...
        Jul 19 15:03:48 chyidl.com systemd[1]: Started A high performance web server and a reverse proxy server.
    * curl -4 icanhazip.com # get public IP address 
    * $ sudo systemctl stop nginx # stop web server 
    * $ sudo systemctl start nginx # start web server 
    * $ sudo systemctl restart nginx # stop and start service 
    * $ sudo systemctl reload nginx # make configuration changes 
    * $ sudo systemctl disable nginx # By default, Nginx is configured to start automatically when the server boots 
    * $ sudo systemctl enable nginx # re-enable the service to start up at boot 
    * $ sudo mkdir -p /var/www/your_domain/html  # create the directory
    * $ sudo chown -R $USER:$USER /var/www/your_domain/html # assign ownership of the directory with the $USER environment variables
    * $ sudo chmod -R 755 /var/www/your_domain # To ensure that your permissions are correct and allow the owner to read, write, and execute the files while granting only read and execute permissions to groups and others, you can input the following command:
    
