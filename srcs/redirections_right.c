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

void	write_file(char *input, char *file)
{
	write(open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644),
		input, ft_strlen(input));
}

void	write_file_append(char *input, char *file)
{
	write(open(file, O_WRONLY | O_CREAT | O_APPEND, 0644),
		input, ft_strlen(input));
}
