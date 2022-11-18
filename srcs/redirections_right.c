/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <bsemmler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:21:09 by jgobbett          #+#    #+#             */
/*   Updated: 2022/11/18 16:19:23 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_file(char *file, int infd)
{
	int		file_fd;

	file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(file_fd, STDOUT_FILENO);
	read_fd(infd, true);
	return (0);
}

int	write_file_append(char *file, int infd)
{
	int		file_fd;

	file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(file_fd, STDOUT_FILENO);
	read_fd(infd, true);
	return (0);
}
