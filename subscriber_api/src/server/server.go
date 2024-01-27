package server

import (
	"fmt"
	"net/http"

	"github.com/gorilla/mux"
)

type Server struct {
	router              *mux.Router
	subscriptionHandler *subscriptionHandler
}

func NewServer(mqttUrl, clientId string) (*Server, error) {
	subHandler, err := newSubscriptionHandler(mqttUrl, clientId)
	if err != nil {
		return nil, err
	}

	srv := Server{
		subscriptionHandler: subHandler,
		router:              mux.NewRouter(),
	}

	srv.router.HandleFunc("/subscribe", srv.subscriptionHandler.handleSubscription)
	return &srv, nil
}

func (srv *Server) Run(port int) error {
	fmt.Printf("Server started on port %d\n", port)
	return http.ListenAndServe(fmt.Sprintf(":%d", port), srv.router)
}
