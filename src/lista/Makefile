#Inicia valores iniciais
EXE				:= main #Nome do executável
CC				:= g++ #Compilador
MAIN_SRC	:= main.cpp

#Adicionar arquivos .h aqui:
H_SRC			:=  vertice.h vizinho.h lista.h saida.h

CFLAGS			:= -Wall -g -std=c++11
LDFLAGS			:= 

#Define variável com arquivos .o
MAIN_OBJ	:= $(MAIN_SRC:.cpp=.o)
OBJS		:= $(H_SRC:.h=.o)

#Junta tudo em um executável
all: output

output:$(MAIN_OBJ) $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $(EXE)
#$@ pega o nome do target(output)
#$^ para listar todos os pré-requisitos do target

#Cria main.o
$(MAIN_OBJ): $(MAIN_SRC) $(H_SRC)
	$(CC) $< $(CFLAGS) -c 
#$< pega o nome do primeiro pré-requisito

#Cria demais arquivos .o
#% pega o tronco do nome
%.o: %.$(EXT) %.h
	$(CC) $< $(CFLAGS) -c

#Apaga arquivos .o e executavel
clean:
	rm -f *.o $(EXE)