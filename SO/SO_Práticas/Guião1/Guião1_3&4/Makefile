CC = gcc
CFLAGS = -Wall

# Comando para compilar o programa
# (basta executar "make")
pessoas:
	$(CC) $(CFLAGS) -o pessoas pessoas.c pessoa.c

# Comando genérico para adicionar um utilizador
run_pessoas_i:
	./pessoas -i "Gabriel Antunes" 20

# Comando genérico para listar os primeiros 5 elementos
run_pessoas_l:
	./pessoas -l 5

# Comando genérico para atualizar a idade de um utilizador
run_pessoas_u:
	./pessoas -u "Gabriel Antunes" 21

# Comando genérico para adicionar um utilizador devolvendo a posição em que foi adicionado
run_pessoas_i2:
	./pessoas -i2 "Gabriel Antunes" 20

# Comando genérico que atualiza a idade de um utilizador através da sua posição na lista
run_pessoas_o:
	./pessoas -o 4 21

# Comando para limpar qualquer ficheiro que seja criado durante a execução do programa
# Não seria necessário apagar a lista_pessoas.txt, foi minha opção
clean: 
	rm -f *.o pessoas file_pessoas lista_pessoas.txt

