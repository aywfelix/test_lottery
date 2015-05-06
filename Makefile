CC = gcc
CXX = g++
CFLAGS = -g -lstdc++ -Wall -o2 -pg
LDFLAGS = -lpthread -levent 

all: test_client test_server test

test_server: util.o CServer.o test_server.o
		$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_client: util.o CClient.o test_client.o
		$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: util.o test.o
		$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.c.o:
		$(CXX) $(CFLAGS) -c $< -pg 


.PHONY : clean

clean:
		rm -rf test_client test_server test
		find ./ -name "*.o" -exec rm -rf {} \;


