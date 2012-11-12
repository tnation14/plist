TARGET = testlist

CC = gcc

#CFLAGS = -m32 -g -Wall
CFLAGS =  -g -Wall

all: $(TARGET)

$(TARGET): $(TARGET).c plist.o 

	$(CC) $(CFLAGS) -o $(TARGET)  $(TARGET).c plist.o

plist.o: plist.c plist.h
	$(CC) $(CFLAGS) -c plist.c

clean:
	$(RM) $(TARGET) *.o
