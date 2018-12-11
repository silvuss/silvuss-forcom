CC = gcc
CFLAGS = -Wall -Wextra

SRC = ./src
BIN = ./bin
DEBUG_BIN = ./bin_debug
NAME = forcom
DEBUG_NAME = forcom_debug

# do not miss the dot below
OBJ = .
RM = rm
MKDIR = mkdir
RMDIR = rmdir

.PHONY: default
default: ${OBJ}/misc.o ${OBJ}/output.o ${OBJ}/readline.o ${OBJ}/main.o
	-${RM} ${BIN}/${NAME}
	-${MKDIR} ${BIN}
	${CC} $^ -o ${BIN}/${NAME}
	-${RM} $^

.PHONY: debug
debug: ${OBJ}/misc.o ${OBJ}/output.o ${OBJ}/readline.o ${OBJ}/main.o
	-${RM} ${DEBUG_BIN}/${DEBUG_NAME}
	-${MKDIR} ${DEBUG_BIN}
	${CC} $^ -o ${DEBUG_BIN}/${DEBUG_NAME}

.PHONY: clean
clean:
	-${RM} ${OBJ}/misc.o ${OBJ}/output.o ${OBJ}/readline.o ${OBJ}/main.o
	-${RM} ${BIN}/${NAME}
	-${RMDIR} ${BIN}
	-${RM} ${DEBUG_BIN}/${DEBUG_NAME}
	-${RMDIR} ${DEBUG_BIN}

${OBJ}/misc.o: ${SRC}/misc.c ${SRC}/misc.h
	${CC} -c ${SRC}/misc.c

${OBJ}/output.o: ${SRC}/output.c ${SRC}/output.h
	${CC} -c ${SRC}/output.c

${OBJ}/readline.o: ${SRC}/readline.c ${SRC}/readline.h
	${CC} -c ${SRC}/readline.c

${OBJ}/main.o: ${SRC}/main.c
	${CC} -c ${SRC}/main.c