CC = gcc
CXX = g++
CFLAGS = -Wall -g -o2
LDFLAGS = -lpthread 
TARGET: test_client test_server
all: $(TARGET)

# test_client: lib_net.o lib_public.o test_client.o
# 		$(CC) -o $@ $^ 

# test_server2: lib_net.o lib_thread.o lib_public.o lib_file.o test_server2.o
# 		$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)
test_server: util.o server.o test_server.o
		$(CXX) $(CFLAGS) -o $@ $^
test_server.o:
		$(CXX) -c test_server.cpp
test_client: util.o client.o test_client.o
		$(CXX) $(CFLAGS) -o $@ $^
test_client.o:
		$(CXX) -c test_client.cpp

.c.o:
		$(CXX) -c $< 
clean:
		rm *.o $(TARGET)
