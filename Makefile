# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafioron <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 15:31:44 by mafioron          #+#    #+#              #
#    Updated: 2024/11/14 20:05:25 by mafioron         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# names
NAME = philosopher
#BONUS_NAME = checker
LIBFT = full_libft/libftfull.a

# Compilation
CC = gcc
#MAKEFLAGS += --silent
#WFLAGS = -Wall -Werror -Wextra
CFLAGS += -I$(INCS_DIR) $(WFLAGS) -g3
DEPFLAGS= -MMD -MP


#printing
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m
CLEAR = \033[2K\r

# directories
SRCS_DIR = src/
#SRCS_BONUS_DIR = src/checker_bonus/
INCS_DIR = include/
#LIBFT_INC = full_libft/include/
OBJ_DIR = obj

#sources
COMMON_SRC = parsing.c philo.c utils.c
#SRC_BONUS = 
COMMON_SRCS = $(addprefix $(SRCS_DIR), $(COMMON_SRC))
#SRCS_BONUS = $(addprefix $(SRCS_BONUS_DIR), $(SRC_BONUS))
COMMON_OBJ = $(COMMON_SRCS:.c=.o)
#OBJ_BONUS = $(SRCS_BONUS:.c=.o)
OBJ_FILES = $(patsubst $(SRCS_DIR)/%.c,$(OBJ_DIR)/%.o,$(COMMON_SRCS))
DEP_FILES = $(OBJ_FILES:.o=.d)

all: $(NAME)

#$(LIBFT):
#	$(MAKE) -C full_libft re

# Création du dossier obj
$(OBJ_DIR):
	@printf "$(CYAN)Création dossier obj$(RESET)"
	@for i in 1 2 3; do printf "."; sleep 0.2; done
	@mkdir -p $(OBJ_DIR)
	@printf " $(GREEN)OK$(RESET)\n"

# Modification de la règle de compilation des .c -> .o
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@printf "$(CYAN)Compilation $<$(RESET)"
	@for i in 1 2 3; do printf "."; done
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
	@printf " $(GREEN)OK$(RESET)\n"

# Linking et message d'animation
$(NAME): $(OBJ_FILES)
	@printf "$(YELLOW)Linking$(RESET)"
	@for i in 1 2 3; do printf "."; sleep 0.3; done
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)
	@printf " $(GREEN)OK$(RESET)\n"

#bonus: $(LIBFT) $(COMMON_OBJ) $(OBJ_BONUS)
#	$(CC) -o $(BONUS_NAME) $(COMMON_OBJ) $(OBJ_BONUS) $(LIBFT)

clean:
	@printf "$(CLEAR)$(YELLOW)Cleaning object files..."
#	@$(MAKE) -C full_libft clean
	@rm -rf $(OBJ_DIR)
	@printf "$(CLEAR)$(GREEN)✓ Object files cleaned!\n"

fclean: clean
	@printf "$(CLEAR)$(YELLOW)Removing executables..."
#	@$(MAKE) -C full_libft fclean
	@rm -f $(NAME)
	@printf "$(CLEAR)$(GREEN)✓ Executables removed!\n"

re: fclean all

.PHONY: all clean fclean re bonus
