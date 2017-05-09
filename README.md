# Philips OTT2000 remote control clone
An esp8266 based (wemos d1 mini), api powered clone of the the Philips OTT 2000 
remote control.



# Problem statement
[Philips OTT 2000](http://www.philips.nl/c-p/OTT2000_12/classic-microgeluidssysteem)
is a cute little stereo with LP playing capabilities. The 
remote control that comes with it is IR based which makes it not so useful 
for non line of sight situations.

   
# Solution
The remote control is a standard IR remote control using rc6 encoding. Which 
means that the IR signals can be read and then can be replayed effectively cloning it's usage 
with whatever means work for us. In this case we are going to use a wemos D1 
mini (esp8266 based) micro controller and create an api driven IR blaster 
compatible with philips' OTT 2000 remote control.

On [this file](IR%20codes.txt) you can find a dump of all IR codes of the 
remote.

Load up the [webserver remote sketch](project/webserver_remote.ino) from the project 
directory to your wemos d1 mini making sure you have loaded the required 
libraries [IRremoteESP8266](https://github.com/markszabo/IRremoteESP8266) and 
[aREST](https://github.com/marcoschwartz/aREST)


The hardware part is very very simple and shown below.

![alt text](/images/ir_led_connection.png "ir led connection schematic")


You should set the ip provided by your dhcp to a static assignment as this is
 a service.

# Usage


Send a power button

    http://remote_ip/send?button=power

response:
    
    {"return_value": 0, "id": "te", "name": "Philips_OTT2000_Remote", "hardware": "esp8266", "connected": true}

Send a non existent button

    http://remote_ip/send?button=noexistent_button

response:
 
    {"return_value": 1, "id": "te", "name": "Philips_OTT2000_Remote", "hardware": "esp8266", "connected": true}


List of supported buttons:


    power
    source
    display
    tuning_left
    tuning_right
    play_pause
    alt_preset_down
    alt_preset_up
    stop
    sleep_timer  
    clock_prog  
    play_mode   
    file_cut   
    rec     
    info   
    volume_down   
    volume_up 
    mute 
    
# Client side
Having an api is fine and all but it is not so much fun to have to access it 
to use your stereo. 

A very simple solution for android phones is [HTTP 
Shortcuts](https://github.com/Waboodoo/HTTP-Shortcuts) and a sample 
configuration implementing just power, source, volume_up, volume_down and 
mute can be found at [http_shortcuts_configuration](shortcuts.txt). If you 
want to use this please replace the instances of "IR_REMOTE_SERVER_IP" with 
the ip of your server.

