/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:21:09 by jgobbett          #+#    #+#             */
/*   Updated: 2022/11/15 17:15:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_file(char *file)
{
	char	*input;
	input = read_fd(STDIN_FILENO, false);
	write(open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644),
		input, ft_strlen(input));
	free(input);
	return (0);
}

int	write_file_append(char *file)
{
	char *input;
	input = read_fd(STDIN_FILENO, false);
	write(open(file, O_WRONLY | O_CREAT | O_APPEND, 0644),
		input, ft_strlen(input));
	free(input);
	return (0);
}
