# OBJS specifies which files to compile as part of the project
OBJS = main.cpp Game.cpp Player.cpp Bat.cpp Ball.cpp utils.cpp LTexture.cpp

# CC specifies which compiler we're using
CC = g++

# COMPILER_FLAGS specifies the additional compilation options we're usingo
# -w supresses all warnings
COMPILER_FLAGS = -w

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# OBJ_NAME specifies the name of the executable produced
OBJ_NAME = main.exe
# Target that complies the executable
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) && ./${OBJ_NAME}

