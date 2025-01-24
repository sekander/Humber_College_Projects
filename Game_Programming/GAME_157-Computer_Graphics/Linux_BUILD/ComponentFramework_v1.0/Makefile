#OBJS specifies which files to compile as part of the project
OBJS = Main.cpp Window.cpp Shader.cpp VMath.cpp Timer.cpp MMath.cpp Mesh.cpp Actor.cpp Noise.cpp SceneManager.cpp Scene0.cpp Scene1.cpp Scene2.cpp Scene3.cpp  Scene4.cpp Scene6.cpp Scene5.cpp Scene7.cpp Skybox.cpp Texture.cpp Trackball.cpp Camera.cpp Debug.cpp 

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lGL -lGLEW

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = graphics_engine 

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

