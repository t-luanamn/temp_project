#!/bin/bash

# Create directories for volumes
sudo mkdir -p /home/tanapoom/data/database
sudo mkdir -p /home/tanapoom/data/website

# Set permissions for the directories
sudo chmod 600 ./secrets/db_root_password.txt ./secrets/db_user.txt ./secrets/db_password.txt \
	./secrets/wp_password.txt ./secrets/wp_admin.txt ./secrets/wp_admin_pw.txt
sudo chown -R 1001:1001 /home/tanapoom/data
sudo chown -R 1001:1001 /home/tanapoom/data/database
sudo chown -R 1001:1001 /home/tanapoom/data/website

echo "Directories for volumes created and permissions set."
