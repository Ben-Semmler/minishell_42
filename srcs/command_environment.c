/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_environment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:47:45 by jgobbett          #+#    #+#             */
/*   Updated: 2022/09/27 14:05:12 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	import_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		insert(get_key(env[i]), get_data(env[i]));
}

int insert_data(char *line, char *key)
{
	int		i;
	t_env	temp;

	temp = search(key);
	i = -1;
	while (temp.data[++i])
		line[i] = temp.data[i];
	return (i);
}

void	command_export(t_inputs *input)
{
	char *key;
	char *data;

	printf("getting key\n");
	key = get_key(input->argv[0]);
	printf("getting data\n");
	data = get_data(input->argv[0]);
	printf("setting env\n");
	insert(key, data);
	printf("done\n");
	printf("key = %s\ndata = %s\n", key, data);
}

void unset(t_inputs *input)
{
	unsigned long	hashindex;
	hashindex = hash(input->argv[0], ENV_SIZE);
	g_env_table[hashindex].key[0] = '\0';
	free(g_env_table[hashindex].key);
	free(g_env_table[hashindex].data);
}

char *get_key(char *str)
{
	int		i;
	char	*rtn;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != ' ')
		i++;
	rtn = malloc(i + 1);
	rtn[i] = '\0';
	while (--i >= 0)
		rtn[i] = str[i];
	return (rtn);
}

char *get_data(char *str)
{
	int		i;
	int		j;
	char	*rtn;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=' && str[i] != ' ')
		i++;
	rtn = malloc(ft_strlen(&str[++i]) + 1);
	while (str[i])
		rtn[j++] = str[i++];
	rtn[j] = '\0';
	return (rtn);
}

void	command_env(void)
{
	int	i;

	i = -1;
	while (++i <= 2048)
		if (g_env_table[i].key)
			printf("%s=%s\n", g_env_table[i].key, g_env_table[i].data);
}

int get_env_len(char *str)
{
	return (ft_strlen(search(get_key(str)).data));
}