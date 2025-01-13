#!/bin/bash
set -e

# Source environment variables from Docker secrets
export MYSQL_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
export MYSQL_USER=$(cat /run/secrets/db_user)
export MYSQL_PASSWORD=$(cat /run/secrets/db_password)

# Start MariaDB server
mysqld_safe &

# Wait for MariaDB to be ready
until mysqladmin ping -h localhost --silent; do
  sleep 1
done

# Initialize the database
mysql -u root -p"${MYSQL_ROOT_PASSWORD}" <<-EOSQL
    CREATE DATABASE IF NOT EXISTS wordpress;
    CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
    GRANT ALL PRIVILEGES ON wordpress.* TO '${MYSQL_USER}'@'%';
    FLUSH PRIVILEGES;
EOSQL

# Keep the container running
wait
