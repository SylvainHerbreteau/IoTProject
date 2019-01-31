The Authors : ENSEIRB-MATMECA's Embedded Systems class of 2018/2019 
--------------------------------------------------------------------


This is the source code for LoraWAN transmissions of Temperature, Humidity & Pressure une Cayenne LPP mode with ChisteraPi from the node.




Babysteps :
------------------
Plug the ChisteraPi & the SenseHAT on your RaspberryPi.

Power on and connect into your RaspberryPi.

Activation of the SPI :

```bash
    sudo raspi-config
```

Then select "9 - Advanced Options" then "A5 - SPI" and <Yes>.

The lmic_chisterapi library need the external library : wiringpi.
If you don't have the library do :
```bash
    sudo apt-get update
    sudo apt-get install wiringpi
```


Execution
------------------
Get into the repository :

```bash
	cd IoT_Project_Node
```

Make sure that DEVKEY, ARTKEY and DEVADDR are the same on the TTN console:

```bash
    gedit The_weather_station/abp/abp.c
    make all	
```

Execute the example :

```bash
	sudo ./abp
```
Go to TTN console and verify that you receive data



