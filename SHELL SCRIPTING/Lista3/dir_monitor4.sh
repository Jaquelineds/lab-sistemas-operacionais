#!/bin/bash
CONTADOR=0
if [ ! -d  $MON_DIR ]; then
	echo "Não é um diretório válido!" 2> /dev/stderr
elif [ -z $MON_DIR ]; then
	echo "Diretório nulo. Não informado!" 2> /dev/stderr
else
	ESTADO_INICIAL=$(ls $MON_DIR -l)
	echo "Diretório válido: $MON_DIR" 
	while [ 1 ]; do
		ESTADO_ATUAL=$(ls $MON_DIR -l)
		#houve mudanca no diretorio
		if [ "$ESTADO_INICIAL" != "$ESTADO_ATUAL" ]; then
			bash -c $* &
			ESTADO_INICIAL=$ESTADO_ATUAL
			CONTADOR=$((CONTADOR+1))
		fi
		sleep 2
		#controla o numero de vezes que houve alteracao, se = 5, terminacao com status 5
		if [ "$CONTADOR" -eq $((5))  ]; then
			exit 5
		fi
	done	
fi

