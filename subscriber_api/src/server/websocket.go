package server

import (
	"log"
	"net/http"
	"subscriberapi/src/subscription"
	"time"

	"github.com/gorilla/websocket"
)

type subscriptionHandler struct {
	websocketUpgrader websocket.Upgrader
	clientMQTT        *subscription.MQTTSubscriber
}

func newSubscriptionHandler(mqttUrl, clientId string) (*subscriptionHandler, error) {
	mqttClient, err := subscription.NewMQTTSubscriber(mqttUrl, clientId)
	if err != nil {
		return nil, err
	}

	return &subscriptionHandler{
		clientMQTT: mqttClient,
		websocketUpgrader: websocket.Upgrader{
			ReadBufferSize:  1024,
			WriteBufferSize: 1024,
		},
	}, nil
}

func (handler *subscriptionHandler) handleSubscription(w http.ResponseWriter, r *http.Request) {
	conn, err := handler.websocketUpgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Println("Error upgrading to WebSocket:", err)
		return
	}
	defer conn.Close()

	request, err := handler.waitForRequestedTopic(conn)
	if err != nil {
		log.Println("Error reading message:", err)
		return
	}

	for {
		err = conn.WriteJSON(request)
		if err != nil {
			log.Println("Error writing message:", err)
			return
		}
		time.Sleep(time.Second)
	}
}

func (handler *subscriptionHandler) waitForRequestedTopic(conn *websocket.Conn) (*TopicRequest, error) {
	request := TopicRequest{}
	err := conn.ReadJSON(&request)
	if err != nil {
		log.Println("Error reading message:", err)
		return nil, err
	}

	if !handler.clientMQTT.IsSubscribedTo(request.Topic) {
		handler.clientMQTT.Subscribe(request.Topic)
	}

	return &request, nil
}
