package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"

	"github.com/go-playground/validator/v10"
)

var validate *validator.Validate

func InitValidator() {
	validate = validator.New()
}

func CreateSimulation(w http.ResponseWriter, r *http.Request) {
	if r.Method != "POST" {
		w.WriteHeader(405)
	}

	body, err := io.ReadAll(r.Body)
	if err != nil {
		w.WriteHeader(500)
	}

	defer r.Body.Close()
	bodyStruct := BodiesSchema{}
	json.Unmarshal(body, &bodyStruct)

	ValidateSimulationRequest(bodyStruct, w)
}

func mainPage(w http.ResponseWriter, r *http.Request) {
	io.WriteString(w, "Cals api")
}

func main() {
	InitValidator()
	fmt.Println("Server started")
	http.HandleFunc("/", mainPage)
	http.HandleFunc("/simulate", CreateSimulation)
	err := http.ListenAndServe(":6969", nil)
	if err != nil {
		fmt.Println(err)
	}
}
