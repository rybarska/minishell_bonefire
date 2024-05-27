/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:51:49 by arybarsk          #+#    #+#             */
/*   Updated: 2024/03/10 19:51:53 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

extern volatile sig_atomic_t	g_o_on;

extern char	**environ;

# define MAX_FILENAME_LEN 42
# define MAX_PATH_LEN 1024
# define HISTORY_SIZE 100

typedef enum e_token_type
{
	WHITESPACE = 0,
	WORD = 1,
	VAR = 2,
	SINGLE_QUOTE = 3,
	DOUBLE_QUOTE = 4,
	PIPE = 5,
	INFILE = 6,
	TRUNCATE = 7,
	APPEND = 8,
	HEREDOC = 9,
	EXPORT = 10,
	ASSIGNMENT = 11,
	EOF_TOKEN = 12
}			t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char		*value;
	char		**split_words;
	int		num_split_words;
}				t_token;

typedef struct s_token_node
{
	t_token_type		type;
	char			*value;
	char		**split_words;
	int		num_split_words;
	struct s_token_node	*previous;
	struct s_token_node	*next;
}				t_token_node;

typedef struct s_redirection
{
	int			type;
	char			*file;
	char			*delimiter;
	int			fd;
	struct s_redirection	*previous;
	struct s_redirection	*next;
}				t_redirection;

typedef struct s_env_var
{
	char	*name;
	char	*value;
	int	is_exported;
	struct	s_env_var	*next;
}				t_env_var;

typedef struct s_exec
{
	char			*name;
	char			*cmd_exec_path;
	char			**arguments;
	int			is_full_path;
	struct s_redirection	*in_redirs;
	struct s_redirection	*out_redirs;
	int			is_export;
	struct s_exec		*previous;
	struct s_exec		*next;
}				t_exec;

typedef struct s_process
{
	pid_t			child_pid;
	int			status;
	struct s_process	*previous;
	struct s_process	*next;
}				t_process;

typedef struct s_data
{
	t_exec		*exec_list_head;
	t_token_node	*token_list_head;
	t_token_node	*token_list_tail;
	int		pos;
	char		*text;
	int		text_len;
	int		urandom;
	char		**cmd_paths;
	char		*found_path;
	int		index;
	int		exec_num;
	int		fd[2];
	int		std_in;
	pid_t		pid;
	int		last_exit_code;
	t_process	*child_list_head;
	t_process	*child_list_tail;
	t_env_var	*env_vars_head;
	char		**ft_environ;
}			t_data;

void	print_execs(t_exec *execs);
void	print_tokens(t_token_node *head);
void	print_envs(t_env_var *env_vars_head);
/* init */
void	init_data(t_data *data);
/* parse */
void	read_input(t_data *data);
t_token	get_next_token(t_data *data);
char	*parse_word(t_data *data);
char	*parse_var(t_data *data);
char	*parse_single_quotes(t_data *data);
char	*parse_double_quotes(t_data *data);
char	*expand_var(char *var_name);
t_token	parse_in_redirections(t_data *data);
t_token	parse_out_redirections(t_data *data);
char	*parse_delimiter(t_data *data);
/* utils */
void	boo(t_data *data, char *error_msg, char *name, int exit_code);
char	*ft_getenv(t_data *data, char *name);
int	has_unquoted_equals(char *str);
/* tokens_utils */
int	is_separating(t_token_type type);
int	is_redirecting(t_token_type type);
int	is_substantive(t_token_type type);
void	process_vars_and_quotes(t_data *data, char **string);
/* execs_utils */
t_exec	*make_empty_exec(t_data *data);
void	exec_lstadd_back(t_exec **lst, t_exec *new);
void	redir_lstadd_back(t_redirection **lst, t_redirection *new_redirection);
int	count_executives(t_data *data);
/* tokens_lists */
void	make_token_list(t_data *data);
void	clear_token_list(t_data *data);
void	print_tokens(t_token_node *head);
/* tokens_merge_strings */
void	merge_unseparated(t_token_node **head);
/* syntax */
int	check_quote_syntax(t_data *data);
int	check_token_syntax(t_data *data);
/* tokens_to_execs */
void	make_executives(t_data *data);
void	extend_redirection_lists(t_data *data, t_token_node *temp, t_exec **exec);
/* arg_expand */
char	*expand_arg(t_data *data, char *arg);
/* arg_expand */
int	add_expanded(char **temp_str, char *expanded);
int	allocate_and_expand(t_data *data, char **temp_str, char *var_name_start,
	char *var_name_end);
/* arg_rm_quotes */
char	*rm_quotes(t_data *data, char *arg);
/* tokens_to_commands */
void	put_cmd_in_exec(t_data *data, t_token_node *node, int arg_count,
	t_exec **exec);
/* tokens_to_env_vars */
void	add_or_update_env_var_list(t_data *data, char *name, char *value, int is_exported);
void	put_env_in_list(t_data *data, t_token_node *node, int env_count,
	int is_exported);
/* cleanup_lists */
void	process_lstclear(t_process **lst);
void	exec_lstclear(t_exec **lst);
void	redir_lstclear(t_redirection **lst);
void	redir_lst_close_fds(t_redirection **lst);
void	token_node_lstclear(t_token_node **lst);
/* cleanup_utils */
void	close_fd_set_minus1(int *fd);
void	free_array(char **array);
void	reset_ints(t_data *data);
/* cleanup */
void	clean_up_data(t_data *data);
void	clean_up_env_vars(t_data *data);
void	snuff_it(t_data *data, char *error_msg, char *name, int exit_code);
void	exit_like_a_boss(t_data *data, int exit_code);
/* path */
void	get_all_cmd_paths(t_data *data);
void	get_path_from_env(t_data *data, char *command);
void	check_if_full_path(t_data *data, t_exec **exec, char *command);
/* children */
void	execute_execs(t_data *data);
void	handle_parent(t_data *data, t_exec **exec);
//void	make_child(t_data *data, t_exec **exec);
/* children_lone */
void	execute_lone_exec_no_pipe(t_data *data, t_exec **exec);
/* children_redirs */
void	close_redir_fds(t_redirection *redir);
void	process_out_files(t_data *data, t_exec **exec);
void	process_in_files(t_data *data, t_exec **exec);
int	has_in_redirs(t_data *data, t_redirection *in_redir);
int	has_out_redirs(t_data *data, t_redirection *out_redir);
/* here_doc */
void	get_heredoc(t_data *data, t_redirection **redir);
/* heredoc_expand */
char	*heredoc_expand_var(t_data *data, char *arg);
/* children_execve */
void	exec_first_command(t_data *data, t_exec *exec);
void	exec_mid_command(t_data *data, t_exec *exec);
void	exec_last_command(t_data *data, t_exec *exec);
/* builtins */
int	is_builtin(char *command);
int	execute_builtin(t_data *data, t_exec **exec, char *command);
/* builtins_export */
void	execute_export(t_data *data, char **args);
/* builtins_export_2 */
void	update_var_in_env(t_data *data, char *name, char *value);
void	add_var_to_env(t_data *data, char *name, char *value);
void	print_export_strings(t_data *data);
int	check_env_var_name(t_data *data, char *name);
/* builtins_short */
void	execute_cd(t_data *data, char *dir);
void	execute_echo(t_exec **exec);
void	execute_env(t_data *data);
void	execute_exit(t_data *data);
void	execute_pwd();
/* signals */
void	set_signal_controls(t_data *data);
void	handle_eof(t_data *data);

#endif
