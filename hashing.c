/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:25:17 by mhuszar           #+#    #+#             */
/*   Updated: 2024/06/26 19:30:58 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t __attribute__ ((naked))	get_hash(void)
{
	__asm__ volatile ("pushq %%rbx; mov %%rdi, %%rbx;"
		"xor %%rax, %%rax; xor %%rdx, %%rdx;"
		"1:"
		"movb (%%rbx), %%cl; cmpb $0, %%cl; jz 2f;"
		"shl $5, %%rax; sub %%rdx, %%rax; movzx %%cl, %%rcx;"
		"addq %%rcx, %%rax; div %%rsi; mov %%rdx, %%rax;"
		"inc %%rbx; jmp 1b;"
		"2:"
		"popq %%rbx; ret;"
		:
		:
		: "rax", "rdx", "rcx"
	);
}

// size_t __attribute__ ((naked))	get_hash(void)
// {
// 	__asm__ volatile ("pushq %%rbx; mov %%rdi, %%rbx; xor %%rax, %%rax;"
// 		"xor %%rcx, %%rcx; xor %%rdx, %%rdx;"
// 		"1:"
// 		"movb (%%rbx), %%cl; cmpb $0, %%cl; jz 2f;"
// 		"imulq $31, %%rax; movzx %%cl, %%rcx;"
// 		"addq %%rcx, %%rax; div %%rsi; mov %%rdx, %%rax;"
// 		"inc %%rbx; jmp 1b;"
// 		"2:"
// 		"popq %%rbx; ret;"
// 		:
// 		:
// 		: "rax", "rdx", "rcx"
// 	);
// }

size_t __attribute__ ((always_inline))	get_hash2(char *keyvalue)
{
	size_t register	hash;

	__asm__ volatile ("pushq %%rbx; mov %%rdi, %%rbx;"
		"xor %%rax, %%rax; xor %%r8, %%r8;"
		"1:"
		"movb (%%rbx), %%dl; cmpb $0, %%dl; jz 2f;"
		"movl $17, %%ecx; movzx %%dl, %%rdx;"
		"mulq %%rcx; add %%rdx, %%rax; add %%r8, %%rax;"
		"inc %%rbx; inc %%r8; jmp 1b;"
		"2:"
		"mov %%rax, %0; popq %%rbx;"
		: "=r"(hash)
		: "D" (keyvalue)
		: "rax", "rdx", "rcx", "r8"
	);
	return (hash);
}

int	store_data(t_keyvalue **hashtable, char *key, char *val)
{
	t_keyvalue	*new;
	size_t		index;

	__asm__ volatile (
		"push %%rdi; push %%rsi; push %%rdx; movq %1, %%rdi; movl %2, %%esi;"
		"callq *%3; movq %%rax, %0; pop %%rdx; pop %%rsi; pop %%rdi;"
		: "=r" (index)
		: "r" (key), "r" (HASHTABLE_SIZE), "r" (get_hash)
		:
	);
	if (hashtable[index])
		return (1);
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
	new->next = hashtable[index];
	hashtable[index] = new;
	return (1);
}

char	*hash_lookup(t_keyvalue **hashtable, char *key)
{
	size_t		index;
	size_t		secure_hash;
	t_keyvalue	*proxy;

	__asm__ volatile (
		"push %%rdi; push %%rsi; movq %1, %%rdi; movl %2, %%esi;"
		"callq *%3; movq %%rax, %0;"
		"pop %%rsi; pop %%rdi;"
		: "=r" (index)
		: "r" (key), "r" (HASHTABLE_SIZE), "r" (get_hash)
		:
	);
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

void	free_hashtable(t_keyvalue **hashtable, bool end_flag)
{
	size_t		index;
	t_keyvalue	*proxy;
	t_keyvalue	*prev;

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
		hashtable[index] = NULL;
		index++;
	}
	if (end_flag)
		free(hashtable);
}

// size_t	get_hash(char *keyvalue)
// {
// 	size_t	hash;
// 	size_t	counter;
// 	size_t	hash2;
// 	size_t	hashsize;

// 	if (keyvalue == NULL)
// 		return (0);
// 	hashsize = HASHTABLE_SIZE;
// 	hash = 0;
// 	counter = 0;
// 	hash2 = 0;
// 	while (keyvalue[counter])
// 	{
// 		 __asm__ volatile ("movq $31, %%rdx; pushq %%rbx;"
// 				"xorq %%rbx, %%rbx; movb %2, %%bl;"
// 				"mulq %%rdx; addq %%rbx, %%rax;"
// 				"divq %%rcx; popq %%rbx;"
// 				: "=d"(hash2)
// 				: "a"(hash), "r"(keyvalue[counter]), "c"(hashsize)
// 				:
//         );
// 		hash = hash2;
// 		counter++;
// 	}
// 	return (hash);
// }

// size_t	get_hash2(char *keyvalue)
// {
// 	size_t	hash;
// 	size_t	counter;
// 	size_t	hash2;

// 	if (keyvalue == NULL)
// 		return (0);
// 	hash = 0;
// 	counter = 0;
// 	hash2 = 0;
// 	while (keyvalue[counter])
// 	{
// 		__asm__ volatile("movq $17, %%rdx; pushq %%rbx;"
// 							"xorq %%rbx, %%rbx; movb %2, %%bl;"
// 							"mulq %%rdx; addq %%rbx, %%rax;"
// 							"addq %%rcx, %%rax; popq %%rbx;"
// 							: "=a"(hash2)
// 							: "a"(hash), "r"(keyvalue[counter]), "c"(counter)
// 							:);
// 		hash = hash2;
// 		counter++;
// 	}
// 	return (hash);
// }
