/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:25:17 by mhuszar           #+#    #+#             */
/*   Updated: 2024/06/11 15:28:41 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (keyvalue[counter] != '\n')
	{
		__asm__ ("movq $31, %%rdx; pushq %%rbx;"
			"xorq %%rbx, %%rbx; movb %2, %%bl;"
			"mulq %%rdx; addq %%rbx, %%rax;"
			"divq %%rcx; popq %%rbx;"
			: "=d" (hash2)
			: "a" (hash), "r" (keyvalue[counter]), "c" (hashsize)
			:
			);
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
	while (keyvalue[counter] != '\n')
	{
		__asm__ ("movq $17, %%rdx; pushq %%rbx;"
			"xorq %%rbx, %%rbx; movb %2, %%bl;"
			"mulq %%rdx; addq %%rbx, %%rax;"
			"addq %%rcx, %%rax; popq %%rbx;"
			: "=a" (hash2)
			: "a" (hash), "r" (keyvalue[counter]), "c" (counter)
			:
			);
		hash = hash2;
		counter++;
	}
	return (hash);
}