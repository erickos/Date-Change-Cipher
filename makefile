#Makefile

#Erick de Oliveira Silva

#Compiler
CXX = gcc

#Flags
COMPILE_FLAG = -std=c11

#Path
SRC_CIPHER_PATH = src/cipher.c
SRC_UNCIPHER_PATH = src/uncipher.c

#Executable
BIN_CIPHER_NAME = ./bin/cipher
BIN_UNCIPHER_NAME = ./bin/uncipher

#Executable
BIN_CIPHER_NAME = ./bin/cipher
BIN_UNCIPHER_NAME = ./bin/uncipher

make:
	$(CXX) -Wall $(COMPILE_FLAG) $(SRC_CIPHER_PATH) -o $(BIN_CIPHER_NAME)
	$(CXX) -Wall $(COMPILE_FLAG) $(SRC_UNCIPHER_PATH) -o $(BIN_UNCIPHER_NAME)

clean:
	-rm -f $(BIN_CIPHER_NAME)
	-rm -f $(BIN_UNCIPHER_NAME)
