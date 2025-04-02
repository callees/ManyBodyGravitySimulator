build_dir = build
binary_name = webservice

binary_path = $(build_dir)/$(binary_name)

# Build go source code to binary
build:
	go build -o $(binary_path)

# Run web service binary
start:
	./$(binary_path)

# Build web service container image
build-service:
	docker compose build

# Create web service container and start it
create-service: 
	docker compose up

# Stop web service container if it's running and remove it
destroy-service:
	docker compose down

# Start existing web service container
start-service:
	docker compose start

# Stop running web service container
stop-service:
	docker compose stop