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
		//printf("1\n");
		ssize_t count = read(fd[0], buffer, sizeof(buffer) - 1);
		//printf("2\n");
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
	if (!print && ft_strncmp(output, "", 1) != 0)
		return (output);
	return (NULL);
}

char	**read_stdout_stderr(int *stdout, int *stderr, bool print)
{
	char	**outputs;
	char	*buffero;
	char	*buffere;

	outputs = malloc(sizeof(char *) * 2);
	outputs[0] = ft_strdup("");
	outputs[1] = ft_strdup("");
	buffero = ft_calloc(256, sizeof(char));
	buffere = ft_calloc(256, sizeof(char));
	while (1)
	{
		//printf("1\n");
		ssize_t counte = read(stderr[0], buffere, sizeof(buffere) - 1);
		ssize_t counto = read(stdout[0], buffero, sizeof(buffero) - 1);
		//printf("2\n");
		/*if (count == -1)
		{
			if (errno == EINTR)
				continue;
			else
			{
				perror("read");
				exit(1);
			}
		}
		else */if (counto == 0 && counte == 0)
			break;
		else
		{
			buffero[counto] = 0;
			buffere[counte] = 0;
			if (print)
				printf("%s", buffero);
			else
				outputs[0] = ft_joinfree(outputs[0], 1, buffero, 0);
			outputs[1] = ft_joinfree(outputs[1], 1, buffere, 0);
		}
	}
	if (!print && ft_strncmp(outputs[0], "", 1) == 0)
	{
		free(outputs[0]);
		outputs[0] = NULL;
	}
	if (!print && ft_strncmp(outputs[1], "", 1) == 0)
	{
		free(outputs[1]);
		outputs[1] = NULL;
	}
	return (outputs);
}


