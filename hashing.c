/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:25:17 by mhuszar           #+#    #+#             */
/*   Updated: 2024/06/11 19:24:16 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_hash(char *keyvalue)
{
	size_t	hash;
	size_t	counter;
	size_t	hash2;
	size_t	hashsize;

	if (keyvalue == NULL)
		return (0);
	hashsize = HASHTABLE_SIZE;
	hash = 0;
	counter = 0;
	hash2 = 0;
	while (keyvalue[counter])
	{
		__asm__("movq $31, %%rdx; pushq %%rbx;"
				"xorq %%rbx, %%rbx; movb %2, %%bl;"
				"mulq %%rdx; addq %%rbx, %%rax;"
				"divq %%rcx; popq %%rbx;"
				: "=d"(hash2)
				: "a"(hash), "r"(keyvalue[counter]), "c"(hashsize)
				:);
		hash = hash2;
		counter++;
	}
	return (hash);
}

size_t	get_hash2(char *keyvalue)
{
	size_t	hash;
	size_t	counter;
	size_t	hash2;

	if (keyvalue == NULL)
		return (0);
	hash = 0;
	counter = 0;
	hash2 = 0;
	while (keyvalue[counter])
	{
		__asm__("movq $17, %%rdx; pushq %%rbx;"
				"xorq %%rbx, %%rbx; movb %2, %%bl;"
				"mulq %%rdx; addq %%rbx, %%rax;"
				"addq %%rcx, %%rax; popq %%rbx;"
				: "=a"(hash2)
				: "a"(hash), "r"(keyvalue[counter]), "c"(counter)
				:);
		hash = hash2;
		counter++;
	}
	return (hash);
}

int	store_data(t_keyvalue **hashtable, char *key, char *val)
{
	t_keyvalue	*new;
	size_t		index;

	new = malloc(sizeof(t_keyvalue));
	if (!new)
		return (0);
	new->key = ft_strdup(key);
	if (!new->key)
		return (free(new), 0);
	new->val = ft_strdup(val);
	if (!new->val)
		return (free(new->key), free(new), 0);
	new->hash2 = get_hash2(key);
	index = get_hash(key);
	new->next = hashtable[index];
	hashtable[index] = new;
	return (1);
}

char	*hash_lookup(t_keyvalue **hashtable, char *key)
{
	size_t index;
	size_t secure_hash;
	t_keyvalue *proxy;

	index = get_hash(key);
	if (!hashtable[index])
		return (NULL);
	secure_hash = get_hash2(key);
	proxy = hashtable[index];
	while (proxy && proxy->hash2 != secure_hash)
		proxy = proxy->next;
	if (proxy)
		return (ft_strdup(proxy->val));
	else
		return (NULL);
}

void free_hashtable(t_keyvalue **hashtable)
{
    size_t      index;
    t_keyvalue *proxy;
    t_keyvalue *prev;

    index = 0;
    while (index < HASHTABLE_SIZE)
    {
        proxy = hashtable[index];
        while (proxy)
        {
            free(proxy->key);
            free(proxy->val);
            prev = proxy;
            proxy = proxy->next;
            free(prev);
        }
        index++;
    }
    free(hashtable);
}
