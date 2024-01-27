package main

import (
	"log"
	"os"
	"subscriberapi/src/server"

	"github.com/joho/godotenv"
)

func main() {
	if err := godotenv.Load(); err != nil {
		log.Fatal("Error loading .env file")
	}

	broker := os.Getenv("QUEUE_URL")
	clientID := os.Getenv("CLIENT_ID")
	srv, err := server.NewServer(broker, clientID)
	if err != nil {
		panic(err)
	}

	if err := srv.Run(4000); err != nil {
		panic(err)
	}
}
