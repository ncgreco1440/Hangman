#COMPILER IN USE
COMPILER=g++
#DIRECTORIES
BUILD=builds
SRC=src
#EXECUTABLE
EXE=Hangman

all: dir $(BUILD)/$(EXE)

dir:
	mkdir -p $(BUILD)

$(BUILD)/$(EXE): $(SRC)/main.o
	$(COMPILER) $(SRC)/main.o -o $(BUILD)/$(EXE)

main.o: $(SRC)/main.cpp
	$(COMPILER)	-c main.cpp

clean:
	rm $(SRC)/*o $(BUILD)/$(EXE)
	rm -rf $(BUILD)