# Connects the Raspberry Pi Pico W to Wi‑Fi and sends an email via Gmail using the umail library (requires filling in your Gmail address, app password, and Wi‑Fi credentials).
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-gmail-send-email
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import network
import time
import urequests

import umail

# Internal libs
import constants


# Email details
sender_email = <Your email>
sender_name = <Your name>
sender_app_password = <APP_PASSWORD>
recipient_email = <EMAIL> 
email_subject ='Like, Comment, Subscribe'

def connect_to_internet(ssid, password):
    # Pass in string arguments for ssid and password
    
    # Just making our internet connection
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(ssid, password)
    
    # Wait for connect or fail
    max_wait = 10
    while max_wait > 0:
      if wlan.status() < 0 or wlan.status() >= 3:
        break
      max_wait -= 1
      print('waiting for connection...')
      time.sleep(1)
    # Handle connection error
    if wlan.status() != 3:
       print(wlan.status())
       raise RuntimeError('network connection failed')
    else:
      print('connected')
      print(wlan.status())
      status = wlan.ifconfig()
      
connect_to_internet(<INTERNET_NAME>, <INTERNET_PASSWORD>)

# Send the email
# Connect to the Gmail's SSL port
smtp = umail.SMTP('smtp.gmail.com', 465, ssl=True)
# Login to the email account using the app password
smtp.login(sender_email, sender_app_password)
# Specify the recipient email address
smtp.to(recipient_email)
# Write the email header
smtp.write("From:" + sender_name + "<"+ sender_email+">\n")
smtp.write("Subject:" + email_subject + "\n")
# Write the body of the email
smtp.write("Test Email from Raspberry Pi Pico W")
# Send the email
smtp.send()
# Quit the email session
smtp.quit()

print('Email Sent')
