#!/bin/bash
echo "Bem-vindo" $USER
echo "Escolha uma opção:"
echo "1 - Calculadora"
echo "2 - Texto"
echo "3 - Operações"
echo "4 - Processo"
echo "5 - Sair"
read comando
case "$comando" in 
   1)
      ./calculadora
      ;;
   2)
      ./texto
      ;;
   3)
      
      ;;
   4)
      
      ;;
   5) 
      echo "Encerrando..."
      ;;
   *) 
      echo "Opção inválida. Escolha uma opção válida."
      ;;
esac
