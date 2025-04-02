project_dir = $(shell pwd)

source_dir = $(project_dir)/src
build_dir = $(project_dir)/build
binary_name = webservice

binary_path = $(build_dir)/$(binary_name)

# Delete build directory
clean:
	rm -rf $(build_dir)

# Build go source code to binary
build: clean
	go build -C $(source_dir) -o $(binary_path)

# Run web service binary
start:
	$(binary_path)

# Build web service container image
service/build:
	docker compose build

# Create web service container and start it
service/up: 
	docker compose up

# Stop web service container if it's running and remove it
service/down:
	docker compose down

# Start existing web service container
service/start:
	docker compose start

# Stop running web service container
service/stop:
	docker compose stop