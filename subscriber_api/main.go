package main

import (
	"fmt"
	"log"
	"os"
	"os/signal"
	"strings"
	"syscall"

	"github.com/joho/godotenv"
)

func main() {
	if err := godotenv.Load(); err != nil {
		log.Fatal("Error loading .env file")
	}

	// broker := "tcp://127.0.0.1:1883"
	// clientID := "subscriber"
	// topic := "FUN"
	broker := os.Getenv("QUEUE_URL")
	clientID := os.Getenv("CLIENT_ID")
	topics := strings.Split(os.Getenv("TOPICS"), ",")
	subscriber, err := NewMQTTSubscriber(broker, clientID)
	if err != nil {
		panic(err)
	}

	for _, topic := range topics {
		fmt.Printf("Subscribing to topic \"%s\"\n", topic)
		subscriber.Subscribe(topic)
	}

	// Wait for a signal to exit
	c := make(chan os.Signal, 1)
	signal.Notify(c, os.Interrupt, syscall.SIGTERM)
	<-c

	// Disconnect from the broker
	for _, topic := range topics {
		if token := subscriber.Client.Unsubscribe(topic); token.Wait() && token.Error() != nil {
			fmt.Println(token.Error())
		}
	}

	subscriber.Client.Disconnect(250)
}
