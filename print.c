/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:37:31 by arybarsk          #+#    #+#             */
/*   Updated: 2024/04/28 18:37:34 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redirections(t_redirection *redirections)
{
    while (redirections != NULL) {
        printf("Type: %d, File: %s\n", redirections->type, redirections->file);
        redirections = redirections->next;
    }
}

void	print_execs(t_exec *execs)
{
    printf("Executives:\n");
    while (execs != NULL) {
        printf("Name: %s, Path: %s\n", execs->name, execs->cmd_exec_path);
        printf("Arguments:\n");
        if (execs->arguments != NULL)
        {
		for (int i = 0; execs->arguments[i] != NULL; ++i)
		{
			printf("  %s\n", execs->arguments[i]);
		}
        }
        printf("Redirections:\n");
        print_redirections(execs->in_redirs);
        print_redirections(execs->out_redirs);
        execs = execs->next;
    }
}

void	print_tokens(t_token_node *head)
{
    t_token_node *current;

	current = head;
	while (current != NULL)
	{
		if (current->value != NULL)
			printf("Token: type %d, value %s\n", current->type, current->value);
		else
			printf("Token: type %d, value (null)\n", current->type);
		 if (current->split_words != NULL)
		{
		    printf("  Split words:\n");
		    for (int i = 0; current->split_words[i] != NULL; i++)
		    {
		        printf("    [%d]: %s\n", i, current->split_words[i]);
		    }
		}
		current = current->next;
	}
}

void	print_envs(t_env_var *env_vars_head)
{
    t_env_var *current = env_vars_head;

    printf("Environment Variables:\n");
    while (current != NULL)
    {
        printf("Name: %s, Value: %s, Exported: %d\n", current->name, current->value, current->is_exported);
        current = current->next;
    }
}

