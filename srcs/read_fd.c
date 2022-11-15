/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:13:22 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/15 17:04:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	read_fd2(int *fd, bool print, char *buffer, char *output)
{
	ssize_t		count;

	count = read(fd[0], buffer, sizeof(buffer) - 1);
	if (count == -1)
	{
		if (errno == EINTR)
			return (0);
		else
		{
			perror("read");
			exit(1);
		}
	}
	else if (count == 0)
		return (1);
	else
	{
		buffer[count] = 0;
		if (print)
			printf("%s", buffer);
		else
			output = ft_joinfree(output, 1, buffer, 0);
	}
	return (0);
}	

char	*read_fd(int *fd, bool print)
{
	char		*output;
	char		*buffer;

	output = ft_strdup("");
	buffer = ft_calloc(256, sizeof(char));
	while (true)
	{
		if (read_fd2(fd, print, buffer, output))
			break ;
	}
	if (!print && ft_strncmp(output, "", 1) != 0)
		return (output);
	return (NULL);
}
