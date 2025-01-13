FROM debian:bullseye

LABEL "author"="tluanamn"

# Install necessary packages
RUN apt-get update && apt-get install -y \
    php7.4-phar \
    php7.4-cli \
    php7.4-mbstring \
    php7.4-xml \
    php7.4-fpm \
    php7.4-mysql \
    php7.4-zip \
    php7.4-gd \
    php7.4-gettext \
    curl \
    wget \
    unzip \
    mariadb-client \
    iputils-ping \
    msmtp \
    && mkdir -p /run/php \
    && rm -f /var/www/html/wp-config.php \
    && rm -rf /var/lib/apt/lists/*

# Set up WordPress directory
RUN mkdir -p /var/www/html
RUN chown -R www-data:www-data /var/www/html && chmod -R 755 /var/www/html

# Copy custom PHP-FPM configuration
COPY ./conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf

# Copy the WordPress setup script
COPY ./tools/wp.sh /tmp/wp-setup.sh

RUN chmod +x /tmp/wp-setup.sh

# Expose port 9000 for PHP-FPM
EXPOSE 9000

ENTRYPOINT ["bash", "/tmp/wp-setup.sh"]

# Start PHP-FPM
CMD ["/usr/sbin/php-fpm7.4", "-F"]
