LIBFT_DIR = libft
INCLUDE_DIR = include

HEADER_SRC = $(INCLUDE_DIR)/minishell.h
SRC = ./src/main/main.c \
      ./src/main/utils.c \
      ./src/main/init.c \
      ./src/parsing/tokens.c \
      ./src/parsing/tokens_utils.c \
      ./src/parsing/tokens_redirections.c \
      ./src/parsing/tokens_delimiter.c \
      ./src/parsing/tokens_quotes.c \
      ./src/parsing/tokens_lists.c \
      ./src/parsing/tokens_merge_strings.c \
      ./src/parsing/tokens_split.c \
      ./src/parsing/vars_and_quotes.c \
      ./src/parsing/syntax.c \
      ./src/parsing/tokens_to_execs.c \
      ./src/parsing/tokens_to_commands.c \
      ./src/parsing/tokens_to_env_vars.c \
      ./src/parsing/arg_expand.c \
      ./src/parsing/arg_expand_2.c \
      ./src/parsing/arg_rm_quotes.c \
      ./src/parsing/ft_split_bonefire.c \
      ./src/parsing/ft_split_bonefire_regular.c \
      ./src/heredoc/get_next_line.c \
      ./src/heredoc/heredoc.c \
      ./src/heredoc/heredoc_expand.c \
      ./src/exec/children.c \
      ./src/exec/children_redirs.c \
      ./src/exec/children_lone.c \
      ./src/exec/children_execve.c \
      ./src/exec/exec_utils.c \
      ./src/exec/redir_utils.c \
      ./src/exec/path.c \
      ./src/builtins/builtins.c \
      ./src/builtins/builtins_cd.c \
      ./src/builtins/builtins_export.c \
      ./src/builtins/builtins_export_2.c \
      ./src/builtins/builtins_short.c \
      ./src/builtins/num_check.c \
      ./src/signals/signals.c \
      ./src/signals/signals_handlers.c \
      ./src/hotrace/hashing.c \
      ./src/hotrace/hash_builtin.c \
      ./src/cleanup/thrash_list.c \
      ./src/cleanup/cleanup_lists.c \
      ./src/cleanup/cleanup_utils.c \
      ./src/cleanup/cleanup.c \

OBJ = $(SRC:%.c=%.o)

CC = cc
CFLAGS = -Werror -Wextra -Wall -I ./include -I $(LIBFT_DIR)
LDFLAGS = -L$(LIBFT_DIR) -L. -lft -lreadline

NAME = minishell

all:$(NAME)

$(NAME):$(OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)
	
$(OBJ): $(HEADER_SRC) $(LIBFT_DIR)/libft.h

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) libft.a
	make -C $(LIBFT_DIR) fclean

re: fclean all

valgrind: $(NAME)
	valgrind --suppressions=ignore_readline.supp --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re
