#!/bin/bash
if [ ! -d  $MON_DIR ]; then
	echo "Não é um diretório válido!" 2> /dev/stderr
elif [ -z $MON_DIR ]; then
	echo "Diretório nulo. Não informado!" 2> /dev/stderr
else
	echo "Diretório válido: $MON_DIR" 
	while [ 1 ]; do
		echo -e "\nArquivos contidos no diretório:"
		ls $MON_DIR
		sleep 2
	done
fi

