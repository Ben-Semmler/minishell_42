/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_left.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:11:38 by marvin            #+#    #+#             */
/*   Updated: 2022/11/15 17:11:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_left(char *command, int outfd)
{
	if (outfd != STDOUT_FILENO)
		printf("%s", read_file(command));
	return (0);
}

char	*read_file(char *filename)
{
	int		fd;
	int		return_val;
	char	buf[256];
	char	*content;

	fd = open(filename, O_RDONLY);
	content = NULL;
	while (true)
	{
		return_val = read(fd, buf, 255);
		if (return_val <= 0)
			break ;
		buf[return_val] = 0;
		if (content != NULL)
			content = ft_joinfree(content, 1, buf, 0);
		else
			content = ft_strdup(buf);
	}
	return (content);
}

int	insert_doc(char *command, int outfd)
{
	char	*input;
	char	*output;

	dup2(STDOUT_FILENO, outfd);
	input = ft_strdup("");
	output = ft_strdup("");
	while (true)
	{
		input = readline("> ");
		if (ft_strncmp(input, command, ft_strlen(input) + 1) == 0)
			break ;
		output = ft_joinfree(output, true, input, true);
		output = ft_joinfree(output, true, "\n", false);
	}
	dup2(outfd, STDOUT_FILENO);
	if (outfd != STDOUT_FILENO)
		printf("%s", output);
	free(input);
	return (0);
}
