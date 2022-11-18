/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <bsemmler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:13:22 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/18 16:17:07 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*read_fd(int fd, bool print)
{
	char	*output;
	char	*buffer;
	int		count;

	output = ft_strdup("");
	buffer = ft_calloc(256, sizeof(char));
	while (true)
	{
		count = read(fd, buffer, sizeof(buffer) - 1);
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
