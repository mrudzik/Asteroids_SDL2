NAME = asteroids

SRC_DIR :=	./sources/
OBJ_DIR :=	./objects/
INC_DIR :=	./includes/
# LIB_DIR :=	./Library/

SRC = 	main.cpp \
		parser/ParserControl.cpp	parser/ParserFlags.cpp	\
		parser/ParserMessages.cpp	parser/ParserTools.cpp	\
		GameManager.cpp				\
		GameSDL_Window.cpp 			\
		\
		SpawnControl.cpp			\
		\
		GameObjectFactory.cpp		\
		GameObjectIntersections.cpp \
		GameObjectRender.cpp		\
		\
		input/InputControl.cpp		\
		input/KeyBehaviour.cpp		\
		input/MouseBehaviour.cpp 	\
		\
		texture/PicTexture.cpp			\
		texture/BackGroundControl.cpp 	\
		\
		game_objects/AbstractGameObject.cpp \
		game_objects/BigAsteroid.cpp		\
		game_objects/SmallAsteroid.cpp		\
		game_objects/Bullet.cpp				\
		game_objects/Player.cpp				\
		\
		ui/Reticle.cpp
		

#	project object files
OBJ =		$(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

INCLUDES	=	-I $(INC_DIR) \
				-I $(INC_DIR)/game_objects	\
				-I $(INC_DIR)/ui

FRAMEWORKS	=	-w -lSDL2 -w -lSDL2_image -w -lSDL2_ttf



CC_FLAGS := -Wall -Wextra -Werror -O3
CC = clang++
all:
	make $(NAME)

# compiles .c files
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(INCLUDES) $(FRAMEWORKS) #-g -fsanitize=address
	@ echo "\n===> $(NAME) compiled\n"

#compiles .o files
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) -c $< -o $@ $(CC_FLAGS) $(HEADER_FLAGS) $(INCLUDES)

clean:
	# make clean -C $(LIBFT_DIR)
	/bin/rm -f $(OBJ)

fclean: clean
	# make fclean -C $(LIBFT_DIR)
	/bin/rm -f $(NAME)

re: fclean all

vpath %.cpp $(SRC_DIR)