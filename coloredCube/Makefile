CC 			= g++
CFLAGS 		=
LDFLAGS 	= -lGL -lGLU -lglut -lm
TARGET 		= cube
SOURCE		= cube.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~