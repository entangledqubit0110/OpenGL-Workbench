CC 			= g++
CFLAGS 		=
LDFLAGS 	= -lGL -lGLU -lglut -lm
TARGET 		= teapot
SOURCE		= teapot.cpp
LIBRARIES	= lighting.h

all: $(TARGET)

$(TARGET): $(SOURCE) $(LIBRARIES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~