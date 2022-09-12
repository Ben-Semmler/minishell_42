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

void	cd_absolute(char **argv);
void	cd_relative(char **argv);

void	command_cd(const t_inputs *input)
{
	if (input->argv[0] == NULL)
		return ;
	if (input->argv[0][0] == '/')
		cd_absolute(input->argv);
	else
		cd_relative(input->argv);
}

void	cd_absolute(char **argv)
{
	if (chdir(argv[0]) != 0)
		printf("minishell: %s: No such file or directory\n", argv[0]);
}

void	cd_relative(char **argv)
{
	char	*cwd;
	char	*ext;
	char	*cwdext;

	cwd = malloc(PATH_MAX + 1);
	if (getcwd(cwd, PATH_MAX + 1) != NULL)
	{
		ext = ft_strjoin("/", argv[0]);
		cwdext = ft_strjoin(cwd, ext);
		if (chdir(cwdext) != 0)
			printf("minishell: %s: No such file or directory\n", argv[0]);
		free(ext);
		free(cwdext);
	}
	else
		printf("Error: could not get working directory\n");
	free(cwd);
}
