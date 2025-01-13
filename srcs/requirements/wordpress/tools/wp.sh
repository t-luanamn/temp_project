#!/bin/bash

set -e

# Source environment variables from Docker secrets
export MYSQL_DATABASE=$MYSQL_DATABASE
export MYSQL_USER=$(cat /run/secrets/db_user)
export MYSQL_PASSWORD=$(cat /run/secrets/db_password)
export WORDPRESS_ADMIN=$(cat /run/secrets/wp_admin)
export WORDPRESS_ADMIN_PASSWORD=$(cat /run/secrets/wp_admin_pw)
export WP_USER=$(cat /run/secrets/wp_user)
export WP_USER_PASSWORD=$(cat /run/secrets/wp_password)

# Validate required environment variables
required_vars=(MYSQL_DATABASE MYSQL_USER MYSQL_PASSWORD WORDPRESS_DB_HOST DOMAIN_NAME BRAND WORDPRESS_ADMIN WORDPRESS_ADMIN_PASSWORD WORDPRESS_ADMIN_EMAIL WP_USER WP_USER_EMAIL WP_USER_PASSWORD)
for var in "${required_vars[@]}"; do
    if [ -z "${!var}" ]; then
        echo "Error: Environment variable $var is not set."
        exit 1
    fi
done

cd /var/www/html
rm -rf *

echo "Downloading wp-cli..."
curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
chmod +x wp-cli.phar
mv wp-cli.phar /usr/local/bin/wp

echo "Validating wp-cli installation..."
if ! php /usr/local/bin/wp --info; then
    echo "Error: wp-cli not installed correctly."
    exit 1
fi

echo "Downloading and setting up WordPress..."

# Download WordPress
wp core download --path=/var/www/html --allow-root

# Try to create wp-config.php
if ! wp config create --path=/var/www/html --dbname="$MYSQL_DATABASE" --dbuser="$MYSQL_USER" \
    --dbpass="$MYSQL_PASSWORD" --dbhost="$WORDPRESS_DB_HOST" --allow-root --skip-check; then
    echo "wp-cli failed to create wp-config.php."
fi

# Install WordPress
wp core install --path=/var/www/html --url="$DOMAIN_NAME" --title="$BRAND" \
    --admin_user="$WORDPRESS_ADMIN" --admin_password="$WORDPRESS_ADMIN_PASSWORD" \
    --admin_email="$WORDPRESS_ADMIN_EMAIL" --allow-root || echo "WordPress already installed."

# Create an author user
wp user create "$WP_USER" "$WP_USER_EMAIL" --role=author --user_pass="$WP_USER_PASSWORD" \
    --path=/var/www/html --allow-root || echo "User already exists."

# Install and update the theme
wp theme install onepress --activate --path=/var/www/html --allow-root \
&& wp theme update onepress --path=/var/www/html --allow-root

echo "WordPress setup completed!"
/usr/sbin/php-fpm7.4 -F