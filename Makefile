CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lcurses
TARGET = mainGame
OBJS = outputView.o gameOver.o stairs.o mainGame.o help.o InfStair.o ranking.o textmanager.o

# Targets and rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

outputView.o: outputView.c outputView.h gameOver.h
	$(CC) $(CFLAGS) -c outputView.c

gameOver.o: gameOver.c gameOver.h
	$(CC) $(CFLAGS) -c gameOver.c

stairs.o: stairs.c stairs.h
	$(CC) $(CFLAGS) -c stairs.c

mainGame.o: mainGame.c outputView.h stairs.h gameOver.h
	$(CC) $(CFLAGS) -c mainGame.c
	

help.o: help.c 
	$(CC) $(CFLAGS) -c help.c


InfStair.o: InfStair.c 
	$(CC) $(CFLAGS) -c InfStair.c
	
ranking.o: InfStair.c 
	$(CC) $(CFLAGS) -c ranking.c
		
textmanager.o: textmanager.c 
	$(CC) $(CFLAGS) -c textmanager.c
	
clean:
	rm -f $(OBJS) $(TARGET)


.PHONY: all clean

