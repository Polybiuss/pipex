NAME = pipex
LIB = libft.a
LIB_DIR = libft
OBJ_DIR = obj

SRC = pipex.c \

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
GREEN = \033[0;32m
CYAN = \033[0;36m
RESET = \033[0m
GRAY = \033[90m

SUCCESS = $(GREEN)[SUCCESS]$(RESET)
INFO = $(CYAN)[INFO]$(RESET)

all: $(NAME)

$(OBJ_DIR):
	@if [ ! -d $(OBJ_DIR) ]; then \
		echo "$(INFO) create directory $(OBJ_DIR)...$(GRAY)"; \
		mkdir -p $(OBJ_DIR); \
		echo "$(SUCCESS) $(OBJ_DIR) done !"; \
	fi

$(LIB):
	@if [ ! -d ./$(LIB_DIR) ]; then \
		echo "$(INFO) git clone Polybft in directory $(LIB_DIR)"; \
		git clone https://github.com/Polybiuss/libft.git $(LIB_DIR); \
		echo "$(INFO) Make $(LIB)..$(GRAY)"; \
		make -sC $(LIB_DIR); \
		echo "$(SUCCESS) Make dome !"; \
	fi

$(OBJ_DIR)/%.o: %.c | $(LIB)
	@echo "$(INFO) Make directory in $(OBJ_DIR).. $(GRAY)"
	mkdir -p $(dir $@)
	@echo "$(SUCCESS) Directory $(dir $@) created !"
	@echo "$(INFO) Compiling all files.c to files.o..$(GRAY)"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(SUCCESS) Compilation succeed !"

$(NAME): $(OBJ)
	@echo "$(INFO) Creating program $(NAME)..$(GRAY)"
	$(CC) $(CFLAGS) $(OBJ) $(LIB_DIR)/$(LIB) -o $(NAME)
	@echo "$(SUCCESS) Program $(NAME) created !"

clean:
	@echo "$(INFO) Removing $(OBJ_DIR) directory & $(LIB_DIR) directory...$(GRAY)"
	rm -rf $(OBJ_DIR)
	rm -rf $(LIB_DIR)
	@echo "$(SUCCESS) $(OBJ_DIR) & $(LIB_DIR) removed !"

fclean: clean
	@echo "$(INFO) Removing program $(NAME)...$(GRAY)"
	rm -rf $(NAME)
	@echo "$(SUCCESS) $(NAME) program removed !"

re: fclean all

.PHONY: all clean fclean re