NAME = philo_one
INC_DIR = includes/
INCLUDES = -I$(INC_DIR)
SRCS_DIR = srcs/
OBJ_DIR = obj/
FLAGS = #-Wall -Wextra -Werror
LINUX_LIB_FLAG = #-pthread

FILES =	philo_one\
		philo_one_init\
		philo_one_utils\
		philo_one_greece

SRCS_FILES = $(addsuffix .c, $(addprefix $(SRCS_DIR), $(FILES)))

OBJ_FILES = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(FILES)))


all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(LINUX_LIB_FLAG) -o $(NAME) $(INCLUDES) $(OBJ_FILES) -fsanitize=address

$(OBJ_FILES): $(OBJ_DIR)%.o : $(SRCS_DIR)%.c
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
		@rm -rf $(OBJ_FILES)

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re