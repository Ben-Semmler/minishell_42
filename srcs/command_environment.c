/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_environment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:47:45 by jgobbett          #+#    #+#             */
/*   Updated: 2022/11/18 15:34:35 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_env_table;

void	import_env(char **env)
{
	int	i;

	i = -1;
	g_env_table = malloc(2048 * sizeof(t_env));
	while (++i < 2048)
	{
		g_env_table[i].key = NULL;
		g_env_table[i].data = NULL;
		g_env_table[i].spot = malloc(sizeof(int));
		*g_env_table[i].spot = 0;
	}
	i = -1;
	while (env[++i])
		insert(get_key(env[i]), get_data(env[i]));
}

int	insert_data(char *line, char *key)
{
	int		i;
	t_env	temp;

	temp = search(key);
	i = -1;
	while (temp.data[++i])
		line[i] = temp.data[i];
	return (i);
}

int	command_export(t_args *args)
{
	char			*key;
	char			*data;
	unsigned long	hashindex;

	key = get_key(args->argv[0]);
	data = get_data(args->argv[0]);
	insert(key, data);
	hashindex = hash(args->argv[0], 2048);
	return (0);
}

int	unset(t_args *args)
{
	t_env	temp;

	temp = search(args->argv[0]);
	free(temp.key);
	free(temp.data);
	*temp.spot = 0;
	return (0);
}

int	command_env(void)
{
	int	i;

	i = -1;
	while (++i < 2048)
		if (*g_env_table[i].spot != 0)
			printf("%s=%s\n", g_env_table[i].key, g_env_table[i].data);
	return (0);
}
