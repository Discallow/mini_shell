NAME = minishell
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDE_DIR)
INCLUDE_DIR = include
RM = rm -f
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft

PURPLE = \033[1;35m
CYAN = \033[1;36m
UNDERLINED_PURPLE = \033[4;35m
RESET = \033[0m

SRC_FILES = $(SRC_DIR)/main.c \
		$(SRC_DIR)/utils/utils.c \
		$(SRC_DIR)/utils/utils2.c \
		$(SRC_DIR)/tokenization/tokenizer.c \
		$(SRC_DIR)/tokenization/tokenizer2.c \
		$(SRC_DIR)/tokenization/token_stack.c \
		$(SRC_DIR)/tokenization/token_quotes_check.c \
		$(SRC_DIR)/handle_signals.c \
		$(SRC_DIR)/handle_signals2.c \
		$(SRC_DIR)/parsing/parsing.c \
		$(SRC_DIR)/parsing/parsing2.c \
		$(SRC_DIR)/parsing/parsing_here_doc.c \
		$(SRC_DIR)/parsing/parsing_here_doc2.c \
		$(SRC_DIR)/parsing/parsing_syntax.c \
		$(SRC_DIR)/parsing/parsing_pipes.c \
		$(SRC_DIR)/parsing/parsing_redirect.c \
		$(SRC_DIR)/parsing/parsing_open_files.c \
		$(SRC_DIR)/parsing/parsing_list_create.c \
		$(SRC_DIR)/utils/free_functions.c \
		$(SRC_DIR)/utils/free_functions2.c \
		$(SRC_DIR)/execution/execution.c \
		$(SRC_DIR)/execution/execution2.c \
		$(SRC_DIR)/built_ins/built_ins.c \
		$(SRC_DIR)/built_ins/built_ins_exit_pwd.c \
		$(SRC_DIR)/built_ins/built_ins_unset_echo.c \
		$(SRC_DIR)/built_ins/built_ins_env.c \
		$(SRC_DIR)/built_ins/built_ins_env2.c \
		$(SRC_DIR)/built_ins/built_ins_env3.c \
		$(SRC_DIR)/built_ins/built_ins_export.c \
		$(SRC_DIR)/built_ins/built_ins_cd.c
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: libft $(NAME)

libft:
	@echo "$(PURPLE)Making libft...$(RESET)"
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ_FILES)
	@echo "$(PURPLE)Building...$(RESET)"
	$(CC) $^ -o $@ -L$(LIBFT_DIR) -lft -lreadline
	@echo "$(PURPLE)$(NAME) compiled successfully.$(RESET)"

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(PURPLE)Compiling $(UNDERLINED_PURPLE)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

v:
	clear && make && valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./minishell

clean:
	@echo "$(PURPLE)Cleaning up...$(RESET)"
	@make -C $(LIBFT_DIR) clean
	rm -f $(OBJ_FILES)
	@if [ -d "$(OBJ_DIR)" ]; then rm -rf $(OBJ_DIR); fi
	@echo "$(PURPLE)Clean complete!$(RESET)"

fclean: clean
	@echo "$(PURPLE)Removing  \033[9m$(NAME)$(RESET)"
	rm -f $(NAME)
	@echo "$(CYAN)Removing  \033[9m$(LIBFT_DIR)/libft.a$(RESET)"
	rm -f $(LIBFT_DIR)/libft.a
	@echo "$(PURPLE)Removing complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re libft
