#Makefile

#Erick de Oliveira Silva

#Compiler
CXX = gcc

#Flags
COMPILE_FLAG = -std=c11

#Path
<<<<<<< HEAD
SRC_ENCIPHER_PATH = src/encipher.c
SRC_UNCIPHER_PATH = src/uncipher.c

#Executable
BIN_ENCIPHER_NAME = ./bin/encipher
BIN_UNCIPHER_NAME = ./bin/uncipher

init:
	$(CXX) -Wall $(COMPILE_FLAG) $(SRC_ENCIPHER_PATH) -o $(BIN_ENCIPHER_NAME)
=======
SRC_ENCIPHER_PATH = ./src/encipher.c
SRC_UNCIPHER_PATH = ./src/uncipher.c

#Executable
BIN_ENCIPHER_NAME = ./bin/cipher
BIN_UNCIPHER_NAME = ./bin/uncipher

make:
	"> Generating a bin file to encipher in (src/encipher.c)..."
	$(CXX) -Wall $(COMPILE_FLAG) $(SRC_ENCIPHER_PATH) -o $(BIN_ENCIPHER_NAME)
	"> Generating a bin file to uncipher in (src/uasncipher.c)..."
>>>>>>> dadc8950bd247defb6e3d37f4d24dca396db8281
	$(CXX) -Wall $(COMPILE_FLAG) $(SRC_UNCIPHER_PATH) -o $(BIN_UNCIPHER_NAME)

clean:
	-rm -f $(BIN_ENCIPHER_NAME)
	-rm -f $(BIN_UNCIPHER_NAME)
