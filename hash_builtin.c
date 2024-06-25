/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:20:33 by mhuszar           #+#    #+#             */
/*   Updated: 2024/06/25 19:42:40 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_hash(t_data *data)
{
    int counter;
    bool flag;

    data->last_exit_code = 0;
    if (!(data->hashtab))
        return ;
    counter = 0;
    flag = false;
    while (counter < HASHTABLE_SIZE)
    {
        if (data->hashtab[counter++])
            flag = true;
    }
    if (!flag)
        return ;
    printf("key %8s\n\n", "value");
    counter = -1;
    while (++counter < HASHTABLE_SIZE)
    {
        if (data->hashtab[counter])
        {
            printf("%s %15s\n", data->hashtab[counter]->key,
                data->hashtab[counter]->val);
        }
    }
}
