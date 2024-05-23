# Projeto 2: Transferências de Contas

# Como compilar e executar

1. Deve-se utilizar uma máquina Linux
2. Utilize o comando com o nome do arquivo utilizado (processo.c ou thread.c)

 ```
   gcc main.c -o nome
```

3. Depois use o comando para executar o arquivo compilado
   
```
   ./nome
```

# Observações
1. Foi utilizada alocação dinâmica de memória para transações, pois em cada thread agora recebe sua própria instância da transação, evitando conflitos de dados.
2. Na execução calcula de forma aleatória o remetente e destinatário
3. A cada iteração de até 100 processos é printado uma mensagem para validação da execução


# Comprovação de Execução na AWS

![Captura de tela 2024-05-23 204652](https://github.com/PedroPessuto/SistemaOperacional/assets/116746646/a7c8694f-5b7e-453f-88a6-00337c7a2ef9)
