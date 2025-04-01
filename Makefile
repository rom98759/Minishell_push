# =============================================================================
# 🌟 GENERAL CONFIG & FLAGS 🌟
# =============================================================================

CC := cc
CFLAGS := -g -Wall -Wextra -Werror
LDFLAGS := -L/usr/local/lib -lreadline -Llibft
INCLUDES := -Iincludes -Ilibft/includes
NAME := minishell

# =============================================================================
# 📂 SOURCES & OBJECTS 📂
# =============================================================================

# Main sources
SRCS_MAIN := srcs/main.c srcs/main_utils.c

# Builtins sources
SRCS_BUILTINS := \
	srcs/builtins/cd.c \
	srcs/builtins/cd_update.c \
	srcs/builtins/echo.c \
	srcs/builtins/env.c \
	srcs/builtins/execute_builtins.c \
	srcs/builtins/exit.c \
	srcs/builtins/is_builtin.c \
	srcs/builtins/pwd.c \
	srcs/builtins/unset_utils.c \
	srcs/builtins/unset.c \
	srcs/builtins/print_env.c \
	srcs/builtins/export/export.c \
	srcs/builtins/export/export_utils.c \
	srcs/builtins/export/export_add.c \
	srcs/builtins/export/export_concat.c

# Executor sources
SRCS_EXECUTOR := \
	srcs/executor/pipe.c \
	srcs/executor/pipe_utils.c \
	srcs/executor/execute_command.c \
	srcs/executor/execution_utils.c \
	srcs/executor/run_command.c \
	srcs/executor/command_exit.c

# Parsing sources
SRCS_PARSING := \
	srcs/parsing/syntax_error.c

SRCS_SPLIT := \
	srcs/parsing/split_args/split_args.c \
	srcs/parsing/split_args/split_args_utils.c

SRCS_TOKENS := \
	srcs/parsing/tokens/tokens.c \
	srcs/parsing/tokens/detect_type.c \
	srcs/parsing/tokens/tokens_utils.c \
	srcs/parsing/tokens/tokens_utils2.c \
	srcs/parsing/tokens/syntax_error_tokens.c \
	srcs/parsing/tokens/is_valid.c \
	srcs/parsing/tokens/get_command_tokens.c \
	srcs/parsing/tokens/tokens_redir.c

SRCS_REDIRECTIONS := \
	srcs/parsing/redirections/redirections.c \
	srcs/parsing/redirections/create_redirections.c \
	srcs/parsing/redirections/swap_tokens.c \
	srcs/parsing/redirections/swap_tokens_utils.c \
	srcs/parsing/redirections/heredocs_utils.c \
	srcs/parsing/redirections/handle_heredoc.c \
	srcs/parsing/redirections/change_heredoc.c \
	srcs/parsing/redirections/create_heredoc.c \
	srcs/parsing/redirections/apply_heredoc.c

# Expand sources (subset of Parsing)
SRCS_EXPAND := \
	srcs/parsing/expand/expand.c \
	srcs/parsing/expand/expand2.c \
	srcs/parsing/expand/expand_utils.c \
	srcs/parsing/expand/size_expand.c

# Utils sources
SRCS_UTILS := \
	srcs/utils/ft_env.c \
	srcs/utils/ft_exit_error.c \
	srcs/utils/ft_exit.c \
	srcs/utils/ft_free.c \
	srcs/utils/ft_free2.c \
	srcs/utils/history.c \
	srcs/utils/signal.c \
	srcs/utils/utils.c \
	srcs/utils/utils2.c \
	srcs/utils/std.c \
	srcs/utils/ft_safe_atoll.c

# All sources combined
SRCS := $(SRCS_MAIN) $(SRCS_BUILTINS) $(SRCS_EXECUTOR) $(SRCS_PARSING) $(SRCS_EXPAND) $(SRCS_SPLIT) $(SRCS_TOKENS) $(SRCS_UTILS) $(SRCS_REDIRECTIONS)

OBJ_DIR := objs/
OBJ := $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_A := $(LIBFT_DIR)/libft.a

# =============================================================================
# 🏗️ RULES 🏗️
# =============================================================================

all: libft $(NAME)
	@echo "Compilation of $(NAME) : \033[1;32mOK\033[0m"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS) -lft

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# =============================================================================
# LIBFT
# =============================================================================

LIBFT_DIR := libft

libft:
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean_libft:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean_libft:
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

re_libft:
	@$(MAKE) -C $(LIBFT_DIR) re --no-print-directory

# =============================================================================
# CLEANING RULES
# =============================================================================

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Clean de $(NAME) : \033[1;32mOK\033[0m"

fclean: clean fclean_libft
	@rm -f $(NAME)
	@echo "Fclean de $(NAME) : \033[1;32mOK\033[0m"

re: fclean all

# =============================================================================
# 💼 PHONY RULES 💼
# =============================================================================

.PHONY: all clean fclean re libft clean_libft fclean_libft re_libft
