#include "minishell.h"

char	*get_data(char *str)
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

int	command_env(void)
{
	int	i;

	i = -1;
	while (++i < 2048)
		if (*g_env_table[i].spot != 0)
			printf("%s=%s\n", g_env_table[i].key, g_env_table[i].data);
	return (0);
}

int	get_env_len(char *str)
{
	return (ft_strlen(search(get_key(str)).data));
}
