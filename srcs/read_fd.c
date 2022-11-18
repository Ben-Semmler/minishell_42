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

char	*read_fd(int *fd, bool print)
{
	char	*output;
	char	*buffer;
	int		count;

	output = ft_strdup("");
	buffer = ft_calloc(256, sizeof(char));
	while (true)
	{
		count = read(fd[0], buffer, sizeof(buffer) - 1);
		if (count <= 0)
			break ;
		else
		{
			buffer[count] = 0;
			if (print)
				printf("%s", buffer);
			else
				output = ft_joinfree(output, 1, buffer, 0);
		}
	}
	if (!print && ft_strncmp(output, "", 1) != 0)
		return (output);
	return (NULL);
}
