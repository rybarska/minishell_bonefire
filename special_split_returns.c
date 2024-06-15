/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split_returns.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:47:37 by mhuszar           #+#    #+#             */
/*   Updated: 2024/06/15 23:13:03 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_substr_protect(t_data *data, char *s, int start, int len)
{
	char			*new_string;
	unsigned int	i;
	unsigned int	s_len;

	i = start;
	s_len = ft_strlen((char *) s);
	if (start >= s_len)
		return (ft_strdup(""));
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

int count_words(t_data *data, char *str, int *elements)
{
    data->is_s_quoted = 0;
    data->is_d_quoted = 0;
    
    
}


char **ft_split_returns(t_data *data, char *str, int *elements)
{
    int start;
    int end;
    int counter;
    char **result;

    start = 0;
    end = 0;
    counter = 0;
    result = malloc(sizeof(char *) * count_words(data, str, elements) + 1);
    if (!result)
        snuff_it(data, "Error: malloc failed at split special\n", NULL, 255);
    while (str[start] && str[end])
    {
        if ((str[end] == '\'' || str[end] == '\"') && !data->is_s_quoted)
            data->is_s_quoted = str[end];
        else if (data->is_s_quoted && str[end] == data->is_s_quoted)
            data->is_s_quoted = 0;
        if ((str[end] == ' ' && !data->is_s_quoted) || !str[end])
        {
            result[counter++] = ft_substr_protect();
            start = end + 1;
        }
        end++;
    }
    result[counter] = NULL;
    return (result);
}

node->split_words = ft_split_returns(data, str, *num_split_words);

void	snuff_it(t_data *data, char *error_msg, char *name, int exit_code)