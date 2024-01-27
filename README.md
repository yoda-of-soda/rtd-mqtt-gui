# PubSub C++ and Go through MQTT

This consists of 3 applications:
* **Publisher** that pushes random data on different topics to a MQTT instance
* **Subscriber API** that makes web socket connection to the MQTT and immediately subscribes to the data from the MQTT instance.
* **GUI** that shows the data it gets from the `Subscriber API`

More will come eventually