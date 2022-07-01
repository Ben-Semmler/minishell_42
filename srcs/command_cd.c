/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:31:21 by bsemmler          #+#    #+#             */
/*   Updated: 2022/04/14 17:31:22 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_absolute(char **s_input);
void	cd_relative(char **s_input);

void	command_cd(char **s_input)
{
	if (s_input[1] == NULL)
		return ;
	if (s_input[1][0] == '/')
		cd_absolute(s_input);
	cd_relative(s_input);
}

void	cd_absolute(char **s_input)
{
	if (chdir(s_input[1]) != 0)
		printf("minishell: %s: No such file or directory\n", s_input[1]);
}

void	cd_relative(char **s_input)
{
	char	*cwd;
	char	*ext;
	char	*cwdext;

	cwd = malloc(PATH_MAX + 1);
	if (getcwd(cwd, PATH_MAX + 1) != NULL)
	{
		ext = ft_strjoin("/", s_input[1]);
		cwdext = ft_strjoin(cwd, ext);
		if (chdir(cwdext) != 0)
			printf("minishell: %s: No such file or directory\n", s_input[1]);
		free(ext);
		free(cwdext);
	}
	else
		printf("Error: could not get working directory\n");
	free(cwd);
}
