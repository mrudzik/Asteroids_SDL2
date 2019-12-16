NAME = asteroids

SRC_DIR :=	./sources/
OBJ_DIR :=	./objects/
INC_DIR :=	./includes/
# LIB_DIR :=	./Library/

SRC = 	main.cpp
		

#	project object files
OBJ =		$(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

INCLUDES	=	-I $(INC_DIR)\
				-I ./frameworks/SDL2.framework/Versions/A/Headers \
				-I ./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I ./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I ./frameworks/SDL2_mixer.framework/Headers \
				-I ./frameworks/SDL2_net.framework/Headers

FRAMEWORKS	=	-F ./frameworks \
				-rpath ./frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer -framework SDL2_net



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