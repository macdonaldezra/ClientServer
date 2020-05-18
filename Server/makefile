CC = g++
WFLAG = -Wall
DFLAG = -ggdb
CFLAG = -c
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
BINS = ftp_server 
OBJ_DIR = build
OBJS = ftp_server.o ftp_server_connection_listener.o ftp_server_net_util.o \
ftp_server_string_util.o ftp_server_connection.o ftp_server_session.o ftp_server_command.o \
ftp_server_passive.o ftp_server_nlist.o ftp_server_retrieve.o

all: $(OBJS) $(BINS)

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(BINS): | $(BIN_DIR)

$(BIN_DIR):
	mkdir $(BIN_DIR)

ftp_server: 
	${CC} ${WFLAG} ${DFLAG} -o ${BIN_DIR}/myftpserver ${OBJ_DIR}/ftp_server.o \
	${OBJ_DIR}/ftp_server_connection_listener.o ${OBJ_DIR}/ftp_server_net_util.o ${OBJ_DIR}/ftp_server_string_util.o \
	${OBJ_DIR}/ftp_server_connection.o ${OBJ_DIR}/ftp_server_session.o ${OBJ_DIR}/ftp_server_command.o \
	${OBJ_DIR}/ftp_server_passive.o ${OBJ_DIR}/ftp_server_nlist.o ${OBJ_DIR}/ftp_server_retrieve.o

ftp_server.o: ${SRC_DIR}/ftp_server.cpp ${INCLUDE_DIR}/ftp_server_connection_listener.hpp \
${INCLUDE_DIR}/ftp_server_session.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_server.o ${SRC_DIR}/ftp_server.cpp

ftp_server_connection_listener.o: ${SRC_DIR}/ftp_server_connection_listener.cpp \
${INCLUDE_DIR}/ftp_server_connection_listener.hpp ${INCLUDE_DIR}/ftp_server_net_util.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_server_connection_listener.o ${SRC_DIR}/ftp_server_connection_listener.cpp

ftp_server_connection.o: ${SRC_DIR}/ftp_server_connection.cpp ${INCLUDE_DIR}/ftp_server_connection.hpp \
${INCLUDE_DIR}/ftp_server_net_util.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_server_connection.o ${SRC_DIR}/ftp_server_connection.cpp

ftp_server_session.o: ${SRC_DIR}/ftp_server_session.cpp ${INCLUDE_DIR}/ftp_server_session.hpp \
${INCLUDE_DIR}/ftp_server_command.hpp ${INCLUDE_DIR}/ftp_server_connection.hpp ${INCLUDE_DIR}/ftp_server_response.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_server_session.o ${SRC_DIR}/ftp_server_session.cpp

ftp_server_net_util.o: ${SRC_DIR}/ftp_server_net_util.cpp ${INCLUDE_DIR}/ftp_server_net_util.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_server_net_util.o ${SRC_DIR}/ftp_server_net_util.cpp

ftp_server_string_util.o: ${SRC_DIR}/ftp_server_string_util.cpp ${INCLUDE_DIR}/ftp_server_string_util.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_server_string_util.o ${SRC_DIR}/ftp_server_string_util.cpp

ftp_server_command.o: ${SRC_DIR}/ftp_server_command.cpp ${INCLUDE_DIR}/ftp_server_command.hpp \
${INCLUDE_DIR}/ftp_server_connection.hpp ${INCLUDE_DIR}/ftp_server_passive.hpp ${INCLUDE_DIR}/ftp_server_nlist.hpp \
${INCLUDE_DIR}/ftp_server_retrieve.hpp ${INCLUDE_DIR}/ftp_server_response.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_server_command.o ${SRC_DIR}/ftp_server_command.cpp

ftp_server_passive.o: ${SRC_DIR}/ftp_server_passive.cpp ${INCLUDE_DIR}/ftp_server_passive.hpp \
${INCLUDE_DIR}/ftp_server_connection_listener.hpp ${INCLUDE_DIR}/ftp_server_connection.hpp \
${INCLUDE_DIR}/ftp_server_net_util.hpp ${INCLUDE_DIR}/ftp_server_command.hpp \
${INCLUDE_DIR}/ftp_server_string_util.hpp ${INCLUDE_DIR}/ftp_server_response.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_server_passive.o ${SRC_DIR}/ftp_server_passive.cpp

ftp_server_nlist.o: ${SRC_DIR}/ftp_server_nlist.cpp ${INCLUDE_DIR}/ftp_server_nlist.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_server_nlist.o ${SRC_DIR}/ftp_server_nlist.cpp

ftp_server_retrieve.o: ${SRC_DIR}/ftp_server_retrieve.cpp ${INCLUDE_DIR}/ftp_server_retrieve.hpp \
${INCLUDE_DIR}/ftp_server_connection.hpp ${INCLUDE_DIR}/ftp_server_response.hpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDE_DIR} -o ${OBJ_DIR}/ftp_server_retrieve.o ${SRC_DIR}/ftp_server_retrieve.cpp

.PHONY: clean

clean:
	rm -rf ${BIN_DIR}/*
	rm -rf ${OBJ_DIR}/*