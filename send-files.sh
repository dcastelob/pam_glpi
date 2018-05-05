#!/bin/bash

IP=192.168.15.10
#FILES="mysql-connection.c compila.sh"

echo "Enviando arquivos..."
#scp  "$FILES" root@"$IP":~/pam_code/
scp mysql-connection.c compila.sh pam_glpi.conf root@"$IP":~/pam_code/


