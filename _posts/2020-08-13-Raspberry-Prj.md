---
title: Raspberry Pi Project
published: true
---


* DIY Build A BICYCLE Computer WITH RASPBERRY PI
```
Kindle Touch: 

rubber bands:

saddlebag: 

Raspberry Pi:

battery pack: 

FONA 808: Adafruit Fona 808 - Mini Cellular GSM + GPS Breakout
  > The Fona is a neat little from Adafruit that allows internet access through a GRPS cellular data connection. It also comes with a built in GPS! 
  Setup a serial connection between the Fona and the Pi 
  use the Fona's cellular connection to give the Pi internet access 
  access the Fona's built-in GPS  
  collect GPS info and then stream it over a cellular connection
    
  > UART configuration 
    Pi 4 - six UARTS (The Raspberry Pi 4 has four additional PL011s, which are disabled by default. The full list of UARTs on the Pi 4 is:)
      UART0     PL011 
      UART1     mini UART 
      UART2     PL011 
      UART3     PL011 
      UART4     PL011 
      UART5     PL011 
  > $ sudo apt-get update 
  > $ sudo apt-get install ppp screen


reed switches: [https://item.taobao.com/item.htm?spm=a230r.1.14.76.66ae498ar3lFqw&id=624708233913&ns=1&abbucket=2#detail]

Monitor: chain ring:
Monitor: back wheel 
  cadence speed 

// Main code for Raspi-base cycling computer 
from flask import Flask, request 
from flask import render_template 
from flask import send_from_directory 
import random 
import time 
import RPi.GPIO as GPIO 
import os 
from gps import * 
import threading 
import math 

// Create some global variables. 
prev_acc_runtime = 0 
prev_acc_distance = 
speed = 0 
this_time_wheel = 0 

SHOW Metrics:
  AVE SPEED: 
  DISTANCE:
  SLAPSED: 
  TIME: 

MORE: 
  RESET RIDE
  LOG THIS RIDE 
  CONFIGURE 
  SHUT DOWN 
CANCEL 

MAPS: 
  CLOSE BUTTEN 



```
