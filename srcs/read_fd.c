/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:13:22 by bsemmler          #+#    #+#             */
/*   Updated: 2022/06/28 15:13:23 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*read_fd(int *fd, bool print)
{
	char		*output;
	char		*buffer;

	output = ft_strdup("");
	buffer = ft_calloc(256, sizeof(char));
	while (1)
	{
		printf("1\n");
		ssize_t count = read(fd[0], buffer, sizeof(buffer) - 1);
		printf("2\n");
		if (count == -1)
		{
			if (errno == EINTR)
				continue;
			else
			{
				perror("read");
				exit(1);
			}
		}
		else if (count == 0)
			break;
		else
		{
			buffer[count] = 0;
			if (print)
				printf("%s", buffer);
			else
				output = ft_joinfree(output, 1, buffer, 0);
		}
	}
	if (!print)
		return (output);
	return (NULL);
}
