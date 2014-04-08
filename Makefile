# Required packages: libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev

CC=g++
CFLAGS=-Iinclude -Wall -O2
LDFLAGS=-s -lSDL -lSDL_image -lSDL_mixer -lX11

# Uncomment for MinGW on Windows
#LDFLAGS=-s -lSDL -lSDL_image -lSDL_mixer -lSDLmain -static-libgcc -static-libstdc++

SOURCES=src/ObjBotones.cpp src/ObjRuleta.cpp src/ObjContador.cpp src/ObjPanel.cpp src/ScrJugar.cpp src/ScrInicio.cpp src/ScrIdioma.cpp src/ScrRecuento.cpp src/Fuente.cpp src/Lenguaje.cpp src/Main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
BIN=ruletacc

# Targets

all: $(SOURCES) $(BIN)

$(BIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJECTS)
	rm $(BIN)
