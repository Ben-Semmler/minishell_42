/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_environment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:47:45 by jgobbett          #+#    #+#             */
/*   Updated: 2022/06/09 12:38:55 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	inti_g_env(char **env)
// {
// 	int	i;

// 	i = -1;
// 	while (env[++i])
// 		insert(hash());
// }

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
	while (++i < 2048)
		if (g_env_table[i].key)
			printf("%s=%s\n", g_env_table[i].key, g_env_table[i].data);
}
