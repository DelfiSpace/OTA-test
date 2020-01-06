CFLAGS = -Wall

TARGET = ./tests/$(test)
BIN = $(test)

ifeq ($(OS),Windows_NT)
	BIN = $(test).exe
endif


$(TARGET): $(TARGET).c def.h
	gcc -o ./bin/$(BIN) $(TARGET).c OTA.c slot_handler.c md5.c $(CFLAGS) 

clean:
	$(RM) ./bin/$(test)