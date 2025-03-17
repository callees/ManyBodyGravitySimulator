package main

import (
	"fmt"
	"net/http"

	"github.com/go-playground/validator/v10"
)

type TwoDVector struct {
	X float64 `json:"x1" validate:"required"`
	Y float64 `json:"x2" validate:"required"`
}

type Body struct {
	Position TwoDVector `json:"position" validate:"required"`
	Velocity TwoDVector `json:"velocity" validate:"required"`
	Mass     float64    `json:"mass" validate:"required"`
}

type BodiesSchema struct {
	Bodies []Body `json:"bodies" validate:"required,dive,required"`
}

func ValidateSimulationRequest(simulationRequest BodiesSchema, w http.ResponseWriter) {
	valErr := validate.Struct(simulationRequest)

	if valErr != nil {
		validationErrors := valErr.(validator.ValidationErrors)
		if len(validationErrors) > 0 {
			fmt.Println(validationErrors)
			w.WriteHeader(400)
		} else {
			w.WriteHeader(500)
		}
	}
}
