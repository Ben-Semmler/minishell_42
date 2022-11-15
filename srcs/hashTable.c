/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashTable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:26:30 by jgobbett          #+#    #+#             */
/*   Updated: 2022/11/15 20:23:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Djb2 hash function
u_int64_t	hash(char *str, int envlen)
{
	u_int64_t	hash;

	hash = 5381L;
	while (*str++)
		hash = ((hash << 5) + hash) + (*str - 1);
	return (hash % envlen);
}

//returns an environmariable from a key
t_env	search(char *key)
{
	unsigned long	hashindex;

	hashindex = hash(key, 2048);
	while (g_env_table[hashindex].key != NULL)
	{
		if (!ft_strncmp(g_env_table[hashindex].key, key, ft_strlen(key)))
			return (g_env_table[hashindex]);
		++hashindex;
		hashindex %= 2048;
	}
	return (g_env_table[hashindex]);
}

//insert a key-value pair into the hashtable
void	insert(char *key, char *data)
{
	unsigned long	hashindex;

	hashindex = hash(key, 2048);
	while (g_env_table[hashindex].key != NULL
		&& ft_strncmp(key, g_env_table[hashindex].key, ft_strlen(key)))
	{
		++hashindex;
		hashindex %= 2048;
	}
	if (g_env_table[hashindex].key)
	{
		free(g_env_table[hashindex].key);
		free(g_env_table[hashindex].data);
	}
	g_env_table[hashindex].key = key;
	g_env_table[hashindex].data = data;
	*g_env_table[hashindex].spot = hashindex;
}
