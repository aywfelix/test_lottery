DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin
SRC = $(wildcard ${DIR_SRC}/*.c)  
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

CC = gcc
CXX = g++
#CFLAGS = -g -lstdc++ -Wall -o2
CFLAGS = -g 
BIN_DIR = ./bin/
LDFLAGS = -lpthread -levent

all: $(DIR_BIN)/test_client $(DIR_BIN)/test_server $(DIR_BIN)/test
#all: $(TARGET)

# test_client: lib_net.o lib_public.o test_client.o
# 		$(CC) -o $@ $^ 

# test_server2: lib_net.o lib_thread.o lib_public.o lib_file.o test_server2.o
# 		$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)
# $(DIR_BIN)/test_server: util.o server.o test_server.o
# 		$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)
# $(DIR_OBJ)/test_server.o:
# 		$(CXX) $(CFLAGS) -c test_server.cpp $(LDFLAGS)

# $(DIR_BIN)/test_client: util.o client.o test_client.o
# 		$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)
# $(DIR_OBJ)/test_client.o:
# 		$(CXX) $(CFLAGS) -c test_client.cpp

# $(DIR_BIN)/test: util.o test.o
# 		$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# .c.o:
# 		$(CXX) $(CFLAGS) -c $<

$(DIR_BIN)/test_server: util.cpp server.cpp test_server.cpp util.h server.h 
		$(CXX) $(CFLAGS) -o $(DIR_BIN)/test_server $^ $(LDFLAGS)

$(DIR_BIN)/test_client: util.cpp client.cpp test_client.cpp util.h client.h
		$(CXX) $(CFLAGS) -o $(DIR_BIN)/test_client $^ $(LDFLAGS)

$(DIR_BIN)/test: util.cpp test.cpp util.h
		$(CXX) $(CFLAGS) -o $(DIR_BIN)/test $^ $(LDFLAGS)


.PHONY : clean

clean:
		rm -rf $(DIR_BIN)/test_client $(DIR_BIN)/test_server $(DIR_BIN)/test
		find ${DIR_OBJ} -name "*.o" -exec rm -rf {} \;


