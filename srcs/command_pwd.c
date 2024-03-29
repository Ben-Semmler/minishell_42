/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:18:08 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/15 16:16:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_pwd(void)
{
	char	*cwd;

	cwd = malloc(PATH_MAX + 1);
	if (getcwd(cwd, PATH_MAX + 1) != NULL)
		printf("%s\n", cwd);
	else
	{
		printf("Error: could not get directory\n");
		free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}
