#include "minishell.h"

char	*ft_strncpy(char *src, int size)
{
	int		i;
	char	*out;

	i = 0;
	out = malloc(sizeof(char) * (size + 1));
	while (src[i] && i < size)
	{
		out[i] = src[i];
		i++;
	}
	out[i] = 0;
	return (out);
}

int	check_pipe_chars(char *input)
{
	if (input[0] != '|' && input[0] != '>' && input[0] != '<')
		return (0);
	if (input[1] == 0 || (ft_strncmp(input, ">>", 2) != 0
			&& ft_strncmp(input, "<<", 2) != 0))
		return (1);
	return (2);
}

char	*find_relation(char *input)
{
	int		size;

	size = check_pipe_chars(input);
	if (!size)
		return (NULL);
	return (ft_strncpy(input, size));
}
