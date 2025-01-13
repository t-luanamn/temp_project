# Variables
DOCKER_COMPOSE = docker compose
DOCKER_COMPOSE_FILE = ./srcs/docker-compose.yml
ENV_FILE = ./srcs/.env
SET_ENV_SCRIPT = ./srcs/requirements/tools/set_env.sh
CREATE_VOLUMES_SCRIPT = ./srcs/requirements/tools/create_volumes.sh
CHECK_SCRIPT = ./srcs/requirements/tools/check.sh

# Default target
all: set_env create_volumes build up

# Run the set_env.sh script to set environment variables
set_env:
	bash $(SET_ENV_SCRIPT)

# Create directories for volumes and set permissions
create_volumes:
	bash $(CREATE_VOLUMES_SCRIPT)

# Build Docker images
build: set_env
	$(DOCKER_COMPOSE) --env-file $(ENV_FILE) -f $(DOCKER_COMPOSE_FILE) build

# Start containers
up:
	$(DOCKER_COMPOSE) --env-file $(ENV_FILE) -f $(DOCKER_COMPOSE_FILE) up -d

# Stop containers
down:
	$(DOCKER_COMPOSE) --env-file $(ENV_FILE) -f $(DOCKER_COMPOSE_FILE) down

# Clean up containers, images, volumes, and networks
clean:
	$(DOCKER_COMPOSE) --env-file $(ENV_FILE) -f $(DOCKER_COMPOSE_FILE) down --volumes --remove-orphans
	docker system prune -af --volumes
	sudo rm -rf /home/tanapoom/data

# Restart services
restart: down up

re: clean all

# View logs
logs:
	$(DOCKER_COMPOSE) --env-file $(ENV_FILE) -f $(DOCKER_COMPOSE_FILE) logs -f

# Run checks and troubleshooting
check:
	bash $(CHECK_SCRIPT)

.PHONY: all set_env build up down clean restart re logs check
