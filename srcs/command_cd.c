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

int	cd_absolute(char **argv);
int	cd_relative(char **argv);

int	command_cd(const t_inputs *input)
{
	if (input->argv[0] == NULL)
		return (1);
	if (input->argv[0][0] == '/')
		return (cd_absolute(input->argv));
	else
		return (cd_relative(input->argv));
}

int	cd_absolute(char **argv)
{
	if (chdir(argv[0]) != 0)
	{
		printf("minishell: %s: No such file or directory\n", argv[0]);
		return (1);
	}
	return (0);
}

int	cd_relative(char **argv)
{
	char	*cwd;
	char	*ext;
	char	*cwdext;
	int		returnval;

	returnval = 0;
	cwd = malloc(PATH_MAX + 1);
	if (getcwd(cwd, PATH_MAX + 1) != NULL)
	{
		ext = ft_strjoin("/", argv[0]);
		cwdext = ft_strjoin(cwd, ext);
		if (chdir(cwdext) != 0)
		{
			printf("minishell: %s: No such file or directory\n", argv[0]);
			returnval = 1;
		}
		free(ext);
		free(cwdext);
	}
	else
	{
		printf("Error: could not get working directory\n");
		returnval = 1;
	}
	free(cwd);
	return (returnval);
}
