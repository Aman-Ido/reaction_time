COMPILER = g++

LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image
TARGET = reaction_timer

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(COMPILER) $(TARGET).cpp -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
