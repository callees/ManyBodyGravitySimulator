package main

import (
	"bytes"
	"encoding/json"
	"net/http"
	"net/http/httptest"
	"os"
	"testing"
)

func TestMain(m *testing.M) {
	InitValidator()
	code := m.Run()
	os.Exit(code)
}

func TestValidTwoVectorSchema(t *testing.T) {
	invalidTwoDVector := TwoDVector{X: 1.0, Y: 2.0}
	validationErrors := validate.Struct(invalidTwoDVector)

	if validationErrors != nil {
		t.Errorf("Expected validator to pass, but it failed")
		t.Log(validationErrors)
	}
}

func TestInvalidTwoVectorSchema(t *testing.T) {
	invalidTwoDVector := TwoDVector{X: 1.0}
	validationErrors := validate.Struct(invalidTwoDVector)

	if validationErrors == nil {
		t.Errorf("Expected validator to fail, but it passed")
	}
}

func TestValidBodySchema(t *testing.T) {
	position := TwoDVector{X: 1.0, Y: 5.0}
	velocity := TwoDVector{X: -2, Y: 50}

	validBody := Body{Position: position, Velocity: velocity, Mass: 2.0}

	validationErrors := validate.Struct(validBody)

	if validationErrors != nil {
		t.Errorf("Expected validator to pass, but it failed")
		t.Log(validationErrors)
	}
}

func TestMissingPosition(t *testing.T) {
	velocity := TwoDVector{X: -2, Y: 50}

	bodyWithoutPosition := Body{Velocity: velocity, Mass: 2.0}

	validationErrors := validate.Struct(bodyWithoutPosition)

	if validationErrors == nil {
		t.Errorf("Expected validator to fail, but it passed")
	}
}

func TestMissingVelocity(t *testing.T) {
	position := TwoDVector{X: 100, Y: 5}

	bodyWithoutPosition := Body{Position: position, Mass: 2.0}

	validationErrors := validate.Struct(bodyWithoutPosition)

	if validationErrors == nil {
		t.Errorf("Expected validator to fail, but it passed")
	}
}

func TestMissingMass(t *testing.T) {
	position := TwoDVector{X: 1.0, Y: 5.0}
	velocity := TwoDVector{X: -2, Y: 50}

	validBody := Body{Position: position, Velocity: velocity}

	validationErrors := validate.Struct(validBody)

	if validationErrors == nil {
		t.Errorf("Expected validator to fail, but it passed")
	}
}

func TestInvalidTwoVectorInBody(t *testing.T) {
	position := TwoDVector{X: 20}
	velocity := TwoDVector{X: -100, Y: 200}

	bodyWithInvalidTwoVector := Body{Position: position, Velocity: velocity, Mass: 20}

	validationErrors := validate.Struct(bodyWithInvalidTwoVector)

	if validationErrors == nil {
		t.Errorf("Expected validator to fail, but it passed")
	}
}

func TestValidBodies(t *testing.T) {
	bodiesSlice := make([]Body, 0)

	position1 := TwoDVector{X: 20, Y: -10}
	velocity1 := TwoDVector{X: 200, Y: 99}
	mass1 := 5
	body1 := Body{Position: position1, Velocity: velocity1, Mass: float64(mass1)}

	position2 := TwoDVector{X: -20, Y: -200}
	velocity2 := TwoDVector{X: 1, Y: 20}
	mass2 := 50
	body2 := Body{Position: position2, Velocity: velocity2, Mass: float64(mass2)}

	bodiesSlice = append(bodiesSlice, body1, body2)
	bodies := BodiesSchema{Bodies: bodiesSlice}

	validationErrors := validate.Struct(bodies)

	if validationErrors != nil {
		t.Errorf("Expected validator to pass, but it failed")
		t.Log(validationErrors)
	}
}

func TestInvalidBodies(t *testing.T) {
	bodiesSlice := make([]Body, 0)

	velocity1 := TwoDVector{X: 200, Y: 99}
	mass1 := 5
	body1 := Body{Velocity: velocity1, Mass: float64(mass1)}

	position2 := TwoDVector{X: -20, Y: -200}
	velocity2 := TwoDVector{X: 1, Y: 20}
	mass2 := 50
	body2 := Body{Position: position2, Velocity: velocity2, Mass: float64(mass2)}

	bodiesSlice = append(bodiesSlice, body1, body2)
	bodies := BodiesSchema{Bodies: bodiesSlice}

	validationErrors := validate.Struct(bodies)

	if validationErrors == nil {
		t.Errorf("Expected validator to fail, but it passed")
		t.Log(validationErrors)
	}
}

func TestValidRequest(t *testing.T) {
	var fileData, _ = os.ReadFile("validRequest.json")
	var testRequests interface{}
	json.Unmarshal(fileData, &testRequests)

	json, _ := json.Marshal(testRequests)
	req := httptest.NewRequest("POST", "/simulate", bytes.NewBuffer(json))

	w := httptest.NewRecorder()
	handler := http.HandlerFunc(CreateSimulation)

	handler(w, req)
	r := w.Result()

	if r.StatusCode != 200 {
		t.Errorf("Expected 200 status code but got %d", r.StatusCode)
	}
}

func TestInvalidRequest(t *testing.T) {
	var fileData, _ = os.ReadFile("invalidRequest.json")
	var testRequests interface{}
	json.Unmarshal(fileData, &testRequests)

	json, _ := json.Marshal(testRequests)
	req := httptest.NewRequest("POST", "/simulate", bytes.NewBuffer(json))

	w := httptest.NewRecorder()
	handler := http.HandlerFunc(CreateSimulation)

	handler(w, req)
	r := w.Result()

	if r.StatusCode != 400 {
		t.Errorf("Expected 400 status code but got %d", r.StatusCode)
	}
}
