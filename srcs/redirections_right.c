/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:21:09 by jgobbett          #+#    #+#             */
/*   Updated: 2022/11/07 22:25:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	writeToFile(char *input, char *file)
{
	//DEBUG
	if (debug)
		printf("WRITING TO FILE (NO OVERWRITE) (REDIRECTION '>')\n");
	//DEBUG

	//Doesnt overwrite file
	write(open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644), input, ft_strlen(input));
}

void	writeToFile_append(char *input, char *file)
{
	//DEBUG
	if (debug)
		printf("WRITING TO FILE (OVERWRITES) (REDIRECTION '>>')\n");
	//DEBUG

	write(open(file, O_WRONLY | O_CREAT | O_APPEND, 0644), input, ft_strlen(input));
}

/*void	append_right(char *input)
{
	int		i;
	char	*name;
	char	*out;
	int		sign;

	i = 1;
	sign = 0;
	while (input[i])
	{
		 if (ft_strncmp(input[i], ">>", 2))
		 {
			 sign = 1;
			 break ;
		 }
		 else if( ft_strncmp(input[i], ">", 1))
			 break ;
		i++;
	}
	name = input[i + 1];
	i = 0;
	while (*name && (*name == ' ' || *name == '	'))
		name++;
	if (sign)
		writeToFile_append(out, name);
	else
		writeToFile(out, name);
}*/