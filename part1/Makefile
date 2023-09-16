CC = g++
CFLAGS = -std=c++11
DEST = /usr/local/bin
OBJS = main.o block.o blockchain.o sha256.o
PROGRAM = myprogram

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJS)

#main.o: main.cc
#	$(CC) $(CFLAGS) -c main.cc

sha256.o: ../hash-library/sha256.cpp
	$(CC) $(CFLAGS) -c ../hash-library/sha256.cpp

clean:
	rm -f *.o *~ a.out $(PROGRAM)

#install: $(PROGRAM)
#	install -s $(PROGRAM) $(DEST)

test: $(PROGRAM)
	./$(PROGRAM)
