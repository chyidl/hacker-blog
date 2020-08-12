---
title: SSH login alert with sendmail and PAM
published: true
---

> When you setup a Virtual Private Server (VPS) is security and enabling ssh exposes you to some hack activity! An email alert, when someone logs in to your server via ssh, can be pretty useful to track who is actually using your server!

** Layered security is the Key!** 

  - Disable SSH login for root user 

  - Change your default ssh port (22) 

  - Use fail2ban to prevent brute-force attacks on your new ssh port 
  
  - If you want to increase your security with password access over ssh use port knocking or 2FA otherwise switch to SSH key.


1. Setup and get sendmail ready:

```
Sendmail is an MTA (mail transfer agent) that supports many kinds of mail-transfer and delivery methods, including the Simple Mail Transfer Protocol (SMTP) used for email transport over the Internet. 

**Installation**:
  // installed sendmail 
  $ sudo apt-get install sendmail 
  
  // changed the host name 
  $ sudo hostnamectl set-hostname chyidl.com
  $ sudo vim /etc/hostname 

  // amended the hosts file 
  $ sudo vim /etc/hosts 

  // amended the local host names file
  $ sudo vim /etc/mail/local-host-names

  // created a generics table
  $ sudo vim /etc/mail/genericstable 
    www-data    webmaster@chyidl.com 
    root        server@chyidl.com 

  // created a generics domains file:
  $ sudo vim /etc/mail/generics-domains 
    chyidl.com 

  // added the following to sendmail.mc 
  $ sudo vim /etc/mail/sendmail.mc 

  // check installation folder 
  $ which sendmail 
  /usr/sbin/sendmail
  
  // check if sendmail is running 
  $ ps -xa | grep sendmail | grep -v grep
  290010 ?        Ss     0:00 sendmail: MTA: accepting connections
  
  // Test sendmail using this command: 
  $ echo "Subject: test" | sudo sendmail -v chyiyaqing@gmail.com
  
```
