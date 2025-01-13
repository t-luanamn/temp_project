FROM debian:bullseye

LABEL "author"="tluanamn"

# Install MariaDB
RUN apt-get update && apt-get install -y \
    mariadb-server \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Copy MariaDB custom configuration
COPY ./conf/mariadb.cnf /etc/mysql/mariadb.conf.d/mariadb.cnf
COPY ./tools/init-mariadb.sh .

RUN chmod +x init-mariadb.sh

# Expose default MariaDB port
EXPOSE 3306

# HEALTHCHECK --interval=30s --timeout=10s \
#   CMD mysqladmin ping -h localhost -u root -p"${MYSQL_ROOT_PASSWORD}" || exit 1

ENTRYPOINT ["bash", "init-mariadb.sh"]

# Start MariaDB
CMD ["mysqld"]
