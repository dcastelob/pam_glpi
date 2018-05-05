#!/bin/bash

## Dependencias
# sudo apt-get install libmysqlclient-dev
# apt-get install libmysqlcppconn-dev  ### Tentativa 1
# sudo apt-get install libmysqlclient libmysqlclient-dev
# $yum install mysql-devel

# Libconfig - yum install libconfig-devel

#gcc mysql-connection.c -o mysql-connection.bin  `mysql_config --cflags --libs` 
#gcc mysql-connection.c -o mysql-connection.bin  `mysql_config --cflags --libs` -L/usr/lib/mysql -lmysqlclient
gcc mysql-connection.c -o mysql-connection.bin  \
	`mysql_config --cflags --libs` -L/usr/lib/mysql -lmysqlclient \
	`pkg-config --cflags libconfig` `pkg-config --libs libconfig`
