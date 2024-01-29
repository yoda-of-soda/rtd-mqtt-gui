package server

import (
	"log"
	"net/http"
	"subscriberapi/src/subscription"

	"github.com/gorilla/websocket"
)

type subscriptionHandler struct {
	websocketUpgrader websocket.Upgrader
	clientMQTT        *subscription.MQTTSubscriber
}

type TopicRequest struct {
	Topics []string `json:"topics"`
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

	if err = handler.waitForRequestedTopic(conn); err != nil {
		log.Println("Error reading message:", err)
		return
	}

	for {
		response := <-subscription.SocketChannel
		if handler.clientMQTT.IsSubscribedTo(response.Topic) {
			err = conn.WriteJSON(response)
			if err != nil {
				log.Println("Error writing message:", err)
				return
			}
		}
	}
}

func (handler *subscriptionHandler) waitForRequestedTopic(conn *websocket.Conn) error {
	request := TopicRequest{}
	err := conn.ReadJSON(&request)
	if err != nil {
		log.Println("Error reading message:", err)
		return err
	}

	for _, topic := range request.Topics {
		if !handler.clientMQTT.IsSubscribedTo(topic) {
			handler.clientMQTT.Subscribe(topic)
		}
	}

	return nil
}
