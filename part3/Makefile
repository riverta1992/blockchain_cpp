CC = g++
CFLAGS = -std=c++17
DEST = /usr/local/bin
SRCS = main.cpp block.cpp blockchain.cpp proofofwork.cpp cli.cpp
#OBJS = main.o block.o blockchain.o sha256.o proofofwork.o cli.o
OBJS = $(SRCS:.cpp=.o) sha256.o ~/src/leveldb/build/libleveldb.a
INCDIR = -I  ../hash-library -I ~/src/leveldb/include -I ~/learning/blockchain_cpp/cereal/include
#LIBDIR = -L /usr/local/lib/ -L ~/src/leveldb/build
LIBS = -lboost_serialization
PROGRAM = blockchain

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJS) $(LIBS)

#main.o: main.cc
#	$(CC) $(CFLAGS) -c main.cc
#blockchain.o: main.cc
#	$(CC) $(CFLAGS) -c main.cc $(INCDIR)

#sha256.o: ../hash-library/sha256.cpp
#	$(CC) $(CFLAGS) $(INCDIR) -c 

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(INCDIR) -c $(SRCS) ../hash-library/sha256.cpp
clean:
	rm -f *.o *~ a.out $(PROGRAM)
	rm -rf *.db

#install: $(PROGRAM)
#	install -s $(PROGRAM) $(DEST)

test: $(PROGRAM)
	./$(PROGRAM) --addblock="First Data"
	./$(PROGRAM) --addblock="Second Data"
	./$(PROGRAM) --printchain
