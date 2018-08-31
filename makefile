#Makefile

#Erick de Oliveira Silva

#Compiler
CXX = gcc

#Flags
COMPILE_FLAG = -std=c11

#Path
SRC_CIPHER_PATH = src/encoder.c
SRC_UNCIPHER_PATH = src/decoder.c

#Executable
BIN_CIPHER_NAME = ./bin/encoder
BIN_UNCIPHER_NAME = ./bin/decoder

make:
	if [ ! -d bin/ ]; then mkdir bin/; fi
	if [ ! -d build/ ]; then mkdir build/; fi
	$(CXX) -Wall $(COMPILE_FLAG) $(SRC_CIPHER_PATH) -o $(BIN_CIPHER_NAME)
	$(CXX) -Wall $(COMPILE_FLAG) $(SRC_UNCIPHER_PATH) -o $(BIN_UNCIPHER_NAME)

clean:
	-rm -rf bin/
	-rm -rf build/
