/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split_returns.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:47:37 by mhuszar           #+#    #+#             */
/*   Updated: 2024/06/16 19:31:29 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr_prot(t_data *data, char *s, int start, int len)
{
	char			*new_string;
	int	i;
	int	s_len;

	i = start;
	s_len = ft_strlen((char *)s);
	// if (start >= s_len) //will this ever happen?
	// 	return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	new_string = malloc(sizeof(char) * (len + 1));
	if (new_string == NULL)
		snuff_it(data, "Error: malloc failed at substr_protect\n", NULL, 255);
	while (s[i] && len > 0)
	{
        new_string[i - start] = s[i];
		len--;
		i++;
	}
	new_string[i - start] = '\0';
	return (new_string);
}

int	count_words_q(t_data *data, char *str, int *elements)
{
	int		words;
	bool	flag;

	data->is_s_quoted = 0;
	words = 0;
	flag = false;
	if (!str)
		return (words);
	while (*str)
	{
		if ((*str == '\'' || *str == '\"') && !data->is_s_quoted)
			data->is_s_quoted = *str;
		else if (*str == '\'' || *str == '\"')
			data->is_s_quoted = 0;
		if (*str == ' ' && !data->is_s_quoted)
			flag = false;
		else if (flag == false)
		{
			words++;
			flag = true;
		}
		str++;
	}
	*elements = words;
	return (words);
}

// char	**ft_split_returns(t_data *data, char *str, int *elements)
// {
// 	int		start;
// 	int		end;
// 	int		counter;
// 	char	**result;

// 	start = 0;
// 	end = -1;
// 	counter = 0;
// 	result = malloc(sizeof(char *) * (count_words_q(data, str, elements) + 1));
// 	if (!result)
// 		snuff_it(data, "Error: malloc failed at split special\n", NULL, 255);
// 	while (str[start])
// 	{
// 		if (str[++end] == data->is_s_quoted && data->is_s_quoted)
// 			data->is_s_quoted = 0;
//         else if ((str[end] == '\'' || str[end] == '\"') && !data->is_s_quoted)
// 			data->is_s_quoted = str[end];
// 		if ((str[end] == ' ' && !data->is_s_quoted) || !str[end])
// 		{
// 			result[counter++] = ft_substr_prot(data, str, start, end - start);
// 			start = end + (str[end] != '\0');
// 		}
// 	}
// 	result[counter] = NULL;
// 	return (result);
// }

// node->split_words = ft_split_returns(data, str, *num_split_words);

// void	snuff_it(t_data *data, char *error_msg, char *name, int exit_code)

// int	main(void)
// {
// 	char **res;
// 	t_data data;
// 	int elems = 0;
// 	data.is_s_quoted = 0;
// 	res = ft_split_returns(&data, "\"\"hehe lol", &elems);
// 	printf("first str: %s, second: %s, third: %s\n", res[0], res[1], res[2]);
// 	return (0);
// }

void init_vals(int *start, int *end, int *ctr, bool *flag)
{
    *end = -1;
	*ctr = 0;
    *flag = false;
	*start = 0;
}

char **malloc_for_res(t_data *data, int size)
{
    char **result;

    result = malloc(sizeof(char *) * (size + 1));
    if (!result)
		snuff_it(data, "Error: malloc failed at split special\n", NULL, 255);
    return (result);
}

char	**ft_split_returns(t_data *data, char *str, int *elements)
{
	int		start;
	int		end;
	int		counter;
	char	**result;
    bool    flag;

	init_vals(&start, &end, &counter, &flag);
    result = malloc_for_res(data, count_words_q(data, str, elements));
	while (str[start])
	{
		if (str[++end] == data->is_s_quoted && data->is_s_quoted)
			data->is_s_quoted = 0;
        else if ((str[end] == '\'' || str[end] == '\"') && !data->is_s_quoted)
			data->is_s_quoted = str[end];
		if ((((str[end] == ' ' && !data->is_s_quoted) || !str[end])) && flag)
		{
            result[counter++] = ft_substr_prot(data, str, start, end - start);
			start = end + (str[end] != '\0');
            flag = false;
		}
        start += (flag == 0 && str[start] == ' ');
        flag = (str[end] != ' ' && !data->is_s_quoted); //quotes?
	}
	result[counter] = NULL;
	return (result);
}

// char	**ft_split_returns(t_data *data, char *str, int *elements)
// {
// 	int		start;
// 	int		end;
// 	int		counter;
// 	char	**result;
//     bool    flag;

// 	init_vals(&start, &end, &counter, &flag);
//     result = malloc_for_res(data, count_words_q(data, str, elements));
// 	while (str[start])
// 	{
// 		if (str[++end] == data->is_s_quoted && data->is_s_quoted)
// 			data->is_s_quoted = 0;
//         else if ((str[end] == '\'' || str[end] == '\"') && !data->is_s_quoted)
// 			data->is_s_quoted = str[end];
// 		if ((((str[end] == ' ' && !data->is_s_quoted) || !str[end])) && flag)
// 		{
// 			printf("increment is: %d, str[end] is: %d|\n", (str[end] != 0), str[end]);
//             result[counter++] = ft_substr_prot(data, str, start, end - start);
// 			start = end + (str[end] != '\0');
//             flag = false;
// 		}
//         else
//             printf("str[end] is: %d, quotes are: %d, flag is: %d\n", str[end], data->is_s_quoted, flag);
//         start += (flag == 0 && str[start] == ' ');
//         flag = (str[end] != ' ' && !data->is_s_quoted); //quotes?
// 	}
//     printf("res[0] is: %s\n", result[0]);
// 	result[counter] = NULL;
// 	return (result);
// }


//debug version
// char	**ft_split_returns(t_data *data, char *str, int *elements)
// {
// 	int		start;
// 	int		end;
// 	int		counter;
// 	char	**result;
//     bool    flag;

// 	start = 0;
// 	end = -1;
// 	counter = 0;
//     flag = false;
// 	result = malloc(sizeof(char *) * (count_words_q(data, str, elements) + 1));
// 	if (!result)
// 		snuff_it(data, "Error: malloc failed at split special\n", NULL, 255);
// 	printf("num of elements: %d\n", *elements);
// 	while (str[start])
// 	{
// 		if (str[++end] == data->is_s_quoted && data->is_s_quoted)
// 			data->is_s_quoted = 0;
//         else if ((str[end] == '\'' || str[end] == '\"') && !data->is_s_quoted)
// 			data->is_s_quoted = str[end];
// 		if (((str[end] == ' ' && !data->is_s_quoted) || !str[end]) && flag)
// 		{
// 			printf("substr time! start is: %c|\n", str[start]);
// 			result[counter++] = ft_substr_prot(data, str, start, end - start);
// 			start = end + (str[end] != '\0');
//             printf("increment is: %d, str[end] is: %d|\n", (str[end] != 0), str[end]);
//             flag = false;
// 		}
//         else if (str[end] != ' ') //should i look for quotes here?
//             flag = true;
//         else if (!flag)
//             start++;
// 	}
//     printf("counter is: %d\n", counter);
// 	result[counter] = NULL;
// 	return (result);
// }

//void	snuff_it(t_data *data, char *error_msg, char *name, int exit_code)
// {
// 	// if (name)
// 	// {
// 	// 	write(2, name, ft_strlen(name));
// 	// 	write(2, ": ", 2);
// 	// }
// 	// write(2, error_msg, ft_strlen(error_msg));
// 	// clean_up_data(data);
// 	// clean_up_env_vars(data);
// 	// free_hashtable(data->hashtab);
// 	// exit(exit_code);
// 	(void)data;
// 	(void)error_msg;
// 	(void)name;
// 	(void)exit_code;
// 	return ;
// }