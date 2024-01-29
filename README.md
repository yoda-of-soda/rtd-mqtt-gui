# PubSub C++ and Go through MQTT

This consists of 3 applications:
* **Publisher** that pushes random data on different topics to a MQTT instance
* **Subscriber API** that makes web socket connection to the MQTT and immediately subscribes to the data from the MQTT instance.
* **GUI** that shows the data it gets from the `Subscriber API`

## What you should expect to see
This is a screenshot of the `GUI` application when data has been fed to it by the 2 other applications:
![image](https://github.com/yoda-of-soda/rtd-mqtt-gui/assets/40967532/152fcd4c-accc-42ed-b64f-d401819768cf)
The `Add record` button just adds a record that says "Clickbait" to the container to the left.

## Setup and installation
This project has certain dependencies:
* **Mosquitto**: This serves the `MQTT` instance which the `Publisher` and `Subscriber API` communicates with to feed the `GUI` with data. It can be downloaded [here](https://mosquitto.org/download/).
* **paho.mqtt.cpp**: This is the library that `Publisher` uses to communicate with the `Mosquitto` instance mentioned before. You can install it using [this guide](https://github.com/eclipse/paho.mqtt.cpp).
* **Qt for C++**: The `GUI` is built using `Qt` (version `6.6.1`) with `C++`. To build this from source, you need to install the `Qt` library ([guide](https://doc.qt.io/qt-6/get-and-install-qt.html)).
    * **Important:** When you install `Qt`, remember to include the `QWebSocket` library.

## Running the damn thing
To run the application, I recommend using the following steps:
1. Clone the project (e.g. using `git clone`)
2. Go to the `subscriber_api` folder and run the program using `go run .`
3. In another terminal, go to the `publisher` folder and call `make` inside the folder to compile the `Publisher` app.
4. Run the `Publisher` application with the preset environment using the command `make start`.
5. Open Qt Creator and open all the files inside the `gui` folder and run the project using `Ctrl` + `R`.

## Known bugs
* When the websocket connection is disconnected using the button for the first time, then you can't reconnect using the `Connect` button.

If you experience any other bug, please create an `issue` and I will try to resolve it.
