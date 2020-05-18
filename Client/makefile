CC = g++
WFLAG = -Wall		#Warning Flag
DFLAG = -ggdb		#Debugging Flag
CFLAG = -c			#Compiling Flag
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
BINS = ftp_client
OBJ_DIR = build
OBJS = ftp_client.o ftp_client_ui.o ftp_client_control.o ftp_client_connection.o \
ftp_client_command.o

all: $(OBJS) $(BINS)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(BINS): | $(BIN_DIR)

$(BIN_DIR):
	mkdir $(BIN_DIR)

ftp_client: $(OBJS)
	${CC} ${WFLAG} ${DFLAG} -o ${BIN_DIR}/myftp ${OBJ_DIR}/ftp_client.o \
	${OBJ_DIR}/ftp_client_ui.o ${OBJ_DIR}/ftp_client_control.o \
	${OBJ_DIR}/ftp_client_connection.o ${OBJ_DIR}/ftp_client_command.o

ftp_client.o: ${SRC_DIR}/ftp_client.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_client.o \
	${SRC_DIR}/ftp_client.cpp

ftp_client_ui.o: ${SRC_DIR}/ftp_client_ui.cpp ${INCLUDE_DIR}/ftp_client_ui.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_client_ui.o \
	${SRC_DIR}/ftp_client_ui.cpp

ftp_client_control.o: ${SRC_DIR}/ftp_client_control.cpp ${INCLUDE_DIR}/ftp_client_control.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_client_control.o \
	${SRC_DIR}/ftp_client_control.cpp

ftp_client_connection.o: ${SRC_DIR}/ftp_client_connection.cpp \
${INCLUDE_DIR}/ftp_client_connection.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_client_connection.o \
	${SRC_DIR}/ftp_client_connection.cpp

ftp_client_command.o: ${SRC_DIR}/ftp_client_command.cpp ${INCLUDE_DIR}/ftp_client_command.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_client_command.o \
	${SRC_DIR}/ftp_client_command.cpp


.PHONY: clean

clean:
	rm -rf ${BIN_DIR}/*
	rm -rf ${OBJ_DIR}/*