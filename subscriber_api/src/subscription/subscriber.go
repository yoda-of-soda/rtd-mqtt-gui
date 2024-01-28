package subscription

import (
	"fmt"
	"os"
	"strconv"

	mqtt "github.com/eclipse/paho.mqtt.golang"
)

// var SocketChannel chan *MessageWithTopic = make(chan *MessageWithTopic)
var SocketChannels = map[string]chan *MessageWithTopic{}

type MQTTSubscriber struct {
	Client           mqtt.Client
	topicsSubscribed map[string]struct{}
}

const defaultQoS = 1

func NewMQTTSubscriber(url string, clientID string) (*MQTTSubscriber, error) {
	subscriber := &MQTTSubscriber{
		topicsSubscribed: map[string]struct{}{},
	}
	opts := mqtt.NewClientOptions().AddBroker(url).SetClientID(clientID)

	subscriber.Client = mqtt.NewClient(opts)
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
	SocketChannels[topic] = make(chan *MessageWithTopic)
	token.Wait()
	subscriber.topicsSubscribed[topic] = struct{}{}
}

func onMessageReceived(client mqtt.Client, message mqtt.Message) {
	fmt.Printf("Received message on topic: %s\n", message.Topic())
	fmt.Printf("Message: %s\n", message.Payload())
	// SocketChannel <- &MessageWithTopic{Topic: message.Topic(), Message: string(message.Payload())}
	SocketChannels[message.Topic()] <- &MessageWithTopic{Topic: message.Topic(), Message: string(message.Payload())}
}

func (subscriber *MQTTSubscriber) IsSubscribedTo(topic string) bool {
	_, isSubscribed := subscriber.topicsSubscribed[topic]
	return isSubscribed
}
