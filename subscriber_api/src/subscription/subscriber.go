package subscription

import (
	"fmt"
	"os"
	"strconv"

	MQTT "github.com/eclipse/paho.mqtt.golang"
)

type MQTTSubscriber struct {
	Client           MQTT.Client
	topicsSubscribed map[string]struct{}
}

const defaultQoS = 1

func NewMQTTSubscriber(url string, clientID string) (*MQTTSubscriber, error) {
	subscriber := &MQTTSubscriber{
		topicsSubscribed: map[string]struct{}{},
	}
	opts := MQTT.NewClientOptions().AddBroker(url).SetClientID(clientID)

	subscriber.Client = MQTT.NewClient(opts)
	if token := subscriber.Client.Connect(); token.Wait() && token.Error() != nil {
		return nil, token.Error()
	}
	return subscriber, nil
}

func (subscriber *MQTTSubscriber) Subscribe(topic string) {
	qos := defaultQoS
	if parsedQoS, err := strconv.Atoi(os.Getenv("QOS")); err == nil {
		qos = parsedQoS
	}
	token := subscriber.Client.Subscribe(topic, byte(qos), onMessageReceived)
	token.Wait()
	subscriber.topicsSubscribed[topic] = struct{}{}
}

func onMessageReceived(client MQTT.Client, message MQTT.Message) {
	fmt.Printf("Received message on topic: %s\n", message.Topic())
	fmt.Printf("Message: %s\n", message.Payload())
}

func (subscriber *MQTTSubscriber) IsSubscribedTo(topic string) bool {
	_, isSubscribed := subscriber.topicsSubscribed[topic]
	return isSubscribed
}
