The given .ino file contains the code for sending DHT sensor data to the web. Specifically, to ThingsSpeak website. \
The DHT sensor will provide temperature and humidity of the surroundings which will act as a trigger event to send the data accross the thingsSpeak channel. The changes in the humidity and temperature are measured automatically and updated to the visualisations present on the channel, although there are multiple options to provide restrainst for the amount of data to be transferred, this code fouces on successfully implementing webhooks.\
According to the given code, following can be inferred:
1. Source: Arduino Nano
2. Destination: ThingsSpeak
3. Trigger Event: DHT22 sensor

Note: The give code is made with the help of MathWorks source code file WriteMultipleFields which is improvised to inculcate the changes in the temperature and humidity of the surroundings and then upload the data the IoT platform service (ThingsSpeak).\
\
Another curcial part of this code is a Secrets.h file that contains the information of the SSID key and password for wifi-connectionn as well as API key for writing values into the fields present on the ThingsSpeak channel. That file is not attached to this code as it contains confidential information.
