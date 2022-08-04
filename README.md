# estudo_de_caso_01860_2022

O projeto foi baseado no exemplo do FreeRTOS para Linux.
As tarefas estão no arquivo main_test.c

Os arquivos adc(.c/.h) tem as funções relacionadas ao adc.  
Os arquivos fifo(.c/.h) tem as funções relacionadas ao buffer do adc  
Os arquivos task_process(.c/.h) tem as funções relacionadas ao processamento dos dados do adc (tarefa2)  
Os arquivos fifo_proc(.c/.h) tem as funções relacionadas ao buffer dos arquivos processados.  

A tarefa 4 chama a função mas retorna vazia.
Os demais arquivos já existiam no projeto de exemplo.

A tarefa 3 apenas printa o buffer na tela.

A tarefa 4 chama a função mas não está retornando valor.

Para compilar:
$ make

Executar:
$ ./build/estudo_de_caso