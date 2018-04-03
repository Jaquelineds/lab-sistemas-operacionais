#***********JAQUELINE DAHMER STEFFENON*************
#!/bin/bash

comando=10

while [ "$comando" -ne 3 ]; do

echo "****** SISTEMA INTEGRADO ******"
echo "1 - Contabilidade"
echo "2 - Vendas"
echo "3 - Sair"
echo "*******************************"
read comando

case "$comando" in 
   1)
      ./contabilidade
      ;;
   2)
      ./vendas
      ;;
   3) 
      echo $status
      echo "Obrigado por utilizar o Sistema Integrado!"	
      ;;
   *) 
      echo "Opção inválida. Escolha uma opção válida."
      ;;
esac

done
