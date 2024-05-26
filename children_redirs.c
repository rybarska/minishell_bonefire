/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_redirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:17:19 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/11 21:17:21 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_bad_infile(t_data *data, t_redirection *in_redir)
{
	if (access(in_redir->file, F_OK) != 0)
		snuff_it(data, "Error: file does not exist\n", in_redir->file, 1);
	else if (access(in_redir->file, R_OK | X_OK) != 0)
		snuff_it(data, "Error opening file\n", in_redir->file, 126);
	else
		snuff_it(data, "Error: bad file\n", in_redir->file, 126);
}

void	process_out_files(t_data *data, t_exec **exec)
{
	(void) data;
	t_redirection	*out_redir;

	out_redir = (*exec)->out_redirs;
	while (out_redir != NULL)
	{
		if (out_redir->type == TRUNCATE)
			out_redir->fd = open(out_redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (out_redir->type == APPEND)
			out_redir->fd = open(out_redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (out_redir->fd < 0)
			snuff_it(data, "Error: permission denied\n", out_redir->file, 126);
		if (out_redir->next)
			close_fd_set_minus1(&out_redir->fd);
		else
		{
			if (dup2(out_redir->fd, STDOUT_FILENO) < 0)
				snuff_it(data, "Error redirecting out_redir->fd\n", out_redir->file, 255);
			close_fd_set_minus1(&out_redir->fd);
		}	
		out_redir = out_redir->next;
	}
}

void	process_in_files(t_data *data, t_exec **exec)
{
	t_redirection	*in_redir;

	in_redir = (*exec)->in_redirs;
	while (in_redir != NULL)
	{
		if (in_redir->type == INFILE)
			in_redir->fd = open(in_redir->file, O_RDONLY);
		else if (in_redir->type == HEREDOC)
		{
			get_heredoc(data, &in_redir);
			in_redir->fd = open(in_redir->file, O_RDONLY);
		}
		if (in_redir->fd < 0)
			handle_bad_infile(data, in_redir);
		if (in_redir->next)
			close_fd_set_minus1(&in_redir->fd);
		else
		{
			if (dup2(in_redir->fd, STDIN_FILENO) < 0)
				snuff_it(data, "Error redirecting in_redir->fd\n", in_redir->file, 255);
			close_fd_set_minus1(&in_redir->fd);
		}
		in_redir = in_redir->next;
	}
}
