/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_environment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:47:45 by jgobbett          #+#    #+#             */
/*   Updated: 2022/11/10 15:19:34 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_env_table;

void	import_env(char **env)
{
	int	i;

	i = -1;
	g_env_table = malloc(ENV_SIZE * sizeof(t_env));
	while (++i < ENV_SIZE)
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

int	command_export(t_inputs *input)
{
	char			*key;
	char			*data;
	unsigned long	hashindex;

	key = get_key(input->argv[0]);
	data = get_data(input->argv[0]);
	insert(key, data);
	hashindex = hash(input->argv[0], ENV_SIZE);
	return (0);
}

int	unset(t_inputs *input)
{
	t_env	temp;

	temp = search(input->argv[0]);
	free(temp.key);
	free(temp.data);
	*temp.spot = 0;
	return (0);
}

char	*get_key(char *str)
{
	int		i;
	char	*rtn;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != ' ' && str[i] != '"')
		i++;
	rtn = malloc(i + 1);
	rtn[i] = '\0';
	while (--i >= 0)
		rtn[i] = str[i];
	return (rtn);
}
