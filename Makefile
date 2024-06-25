LIBFT_DIR = libft
INCLUDE_DIR = include

HEADER_SRC = $(INCLUDE_DIR)/minishell.h
SRC = ./main.c \
      ./utils.c \
      ./init.c \
      ./path.c \
      ./tokens.c \
      ./tokens_utils.c \
      ./tokens_redirections.c \
      ./tokens_delimiter.c \
      ./tokens_quotes.c \
      ./tokens_lists.c \
      ./tokens_merge_strings.c \
      ./vars_and_quotes.c \
      ./syntax.c \
      ./exec_utils.c \
      ./redir_utils.c \
      ./tokens_to_execs.c \
      ./tokens_to_commands.c \
      ./tokens_to_env_vars.c \
      ./arg_expand.c \
      ./arg_expand_2.c \
      ./arg_rm_quotes.c \
      ./get_next_line.c \
      ./heredoc.c \
      ./heredoc_expand.c \
      ./children.c \
      ./children_redirs.c \
      ./children_lone.c \
      ./children_execve.c \
      ./print.c \
      ./cleanup_lists.c \
      ./cleanup_utils.c \
      ./cleanup.c \
      ./builtins.c \
      ./builtins_cd.c \
      ./builtins_export.c \
      ./builtins_export_2.c \
      ./builtins_short.c \
      ./signals.c \
      ./num_check.c \
      ./thrash_list.c \
      ./hashing.c \
      ./special_split_returns.c \
      ./ft_split_bonefire.c \
      ./hash_builtin.c \

OBJ = $(SRC:%.c=%.o)

CC = cc
CFLAGS = -Werror -Wextra -Wall -I ./include -I $(LIBFT_DIR) -g
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
