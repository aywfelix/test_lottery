CC = gcc
CXX = g++
#CFLAGS = -g -lstdc++ -Wall -o2
CFLAGS = -g
LDFLAGS = -lpthread -levent 
TARGET: test_client test_server test
all: $(TARGET)

# test_client: lib_net.o lib_public.o test_client.o
# 		$(CC) -o $@ $^ 

# test_server2: lib_net.o lib_thread.o lib_public.o lib_file.o test_server2.o
# 		$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)
test_server: util.o server.o test_server.o
		$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)
test_server.o:
		$(CXX) $(CFLAGS) -c test_server.cpp $(LDFLAGS)

test_client: util.o client.o test_client.o
		$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)
test_client.o:
		$(CXX) $(CFLAGS) -c test_client.cpp

test: util.o test.o
		$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.c.o:
		$(CXX) $(CFLAGS) -c $< 
clean:
		rm *.o $(TARGET)
