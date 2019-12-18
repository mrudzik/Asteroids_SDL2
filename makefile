NAME = asteroids

SRC_DIR :=	./sources/
OBJ_DIR :=	./objects/
INC_DIR :=	./includes/
# LIB_DIR :=	./Library/

SRC = 	main.cpp \
		parser/ParserControl.cpp	parser/ParserFlags.cpp	\
		parser/ParserMessages.cpp	parser/ParserTools.cpp	\
		GameManager.cpp	\
		GameSDL_Window.cpp \
		input/InputControl.cpp	\
		input/KeyBehaviour.cpp		input/MouseBehaviour.cpp \
		texture/PicTexture.cpp
		

#	project object files
OBJ =		$(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

INCLUDES	=	-I $(INC_DIR) \
				# -I $(INC_DIR)/parser

FRAMEWORKS	=	-w -lSDL2 -w -lSDL2_image



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