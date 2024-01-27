package main

import (
	"fmt"

	MQTT "github.com/eclipse/paho.mqtt.golang"
)

type MQTTSubscriber struct {
	Client MQTT.Client
}

func NewMQTTSubscriber(url string, clientID string) (*MQTTSubscriber, error) {
	subscriber := &MQTTSubscriber{}
	opts := MQTT.NewClientOptions().AddBroker(url).SetClientID(clientID)

	subscriber.Client = MQTT.NewClient(opts)
	if token := subscriber.Client.Connect(); token.Wait() && token.Error() != nil {
		return nil, token.Error()
	}
	return subscriber, nil
}

func (subscriber *MQTTSubscriber) Subscribe(topic string) {
	token := subscriber.Client.Subscribe(topic, 1, onMessageReceived)
	token.Wait()
}

func onMessageReceived(client MQTT.Client, message MQTT.Message) {
	fmt.Printf("Received message on topic: %s\n", message.Topic())
	fmt.Printf("Message: %s\n", message.Payload())
}
