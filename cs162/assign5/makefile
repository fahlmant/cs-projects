CC = g++

TARGET = main
FLAG = -I.
RFLAG = -rf

$(TARGET): $(TARGET).cpp
	$(CC) $(FLAG) Creature.h
	$(CC) $(FLAG) Human.h
	$(CC) $(FLAG) Elf.h
	$(CC) $(FLAG) Demon.h
	$(CC) $(FLAG) Balrog.h
	$(CC) $(FLAG) Cyber.h
	$(CC) $(FLAG) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(RFLAG) $(TARGET)
	
