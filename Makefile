EXEC_NAME=LatHex
CC=g++

# CFLAGS= -Wall -Wno-write-strings -O0 -g
CFLAGS= -w -Wno-write-strings -O3 -lsfml-window -lsfml-graphics -lsfml-system

SRC =   	  \
	main.cpp  \
	Board.cpp \
	Object.cpp\
	Player.cpp\
	Bot.cpp

OBJ =  ${SRC:.cpp=.o}

#------------------------------------------------------------

all: ${EXEC_NAME}

${EXEC_NAME}: ${OBJ}
	${CC} -o ${EXEC_NAME} ${OBJ} ${CFLAGS}

%.o: %.cpp
	${CC} -c -o $@ $+ ${CFLAGS}

clean:
	rm ${EXEC_NAME} *.o *~ *# -rf
