# Noms
NAME = philosopher
OBJ_DIR = obj
LIBFT = full_libft/libftfull.a

# Compilation
CC = gcc
#WFLAGS = -Wall -Werror -Wextra
CFLAGS += -I$(INCS_DIR) $(WFLAGS) -g3
DEPFLAGS = -MMD -MP

# Affichage
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m
CLEAR = \033[2K\r

# Dossiers
SRCS_DIR = src/
INCS_DIR = include/

# Sources
COMMON_SRC = parsing.c philo.c utils.c actions.c monitor.c
COMMON_SRCS = $(addprefix $(SRCS_DIR), $(COMMON_SRC))
OBJ_FILES = $(patsubst $(SRCS_DIR)%.c,$(OBJ_DIR)/%.o,$(COMMON_SRCS))
DEP_FILES = $(OBJ_FILES:.o=.d)

all: $(NAME)

# Inclusion des dépendances
-include $(DEP_FILES)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@printf "$(YELLOW)Compilation $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
	@printf "$(CLEAR)$(GREEN)✓ Compiled $<$(RESET)\n"

$(NAME): $(OBJ_FILES)
	@printf "$(YELLOW)Linking...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)
	@printf "$(CLEAR)$(GREEN)✓ $(NAME) created!$(RESET)\n"

clean:
	@printf "$(YELLOW)cleaning up obj...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@printf "$(CLEAR)$(GREEN)✓ Objects cleaned!$(RESET)\n"

fclean: clean
	@printf "$(YELLOW) Deleteing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@printf "$(CLEAR)$(GREEN)✓ $(NAME) delete!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
