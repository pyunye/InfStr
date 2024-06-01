CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lcurses
TARGET = mainGame
OBJS = outPutView.o gameOver.o stairs.o mainGame.o help.o InfStair.o ranking.o textmanager.o

# Targets and rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

outPutView.o: outPutView.c outPutView.h stairs.h
	$(CC) $(CFLAGS) -c outPutView.c

gameOver.o: gameOver.c gameOver.h
	$(CC) $(CFLAGS) -c gameOver.c

stairs.o: stairs.c stairs.h
	$(CC) $(CFLAGS) -c stairs.c

mainGame.o: mainGame.c outPutView.h InfStair.h 
	$(CC) $(CFLAGS) -c mainGame.c
	

help.o: help.c outPutView.h
	$(CC) $(CFLAGS) -c help.c


InfStair.o: InfStair.c stairs.h InfStair.h gameOver.h textmanager.h
	$(CC) $(CFLAGS) -c InfStair.c
	
ranking.o: InfStair.c outPutView.h
	$(CC) $(CFLAGS) -c ranking.c
		
textmanager.o: textmanager.c textmanager.h
	$(CC) $(CFLAGS) -c textmanager.c
	
clean:
	rm -f $(OBJS) $(TARGET)


.PHONY: all clean

