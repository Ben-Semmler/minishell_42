/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:31:21 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/15 15:59:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_absolute(char **argv);
int	cd_relative(char **argv);

int	command_cd(const t_args *args)
{
	if (args->argv[0] == NULL)
		return (1);
	if (args->argv[0][0] == '/')
		return (cd_absolute(args->argv));
	else
		return (cd_relative(args->argv));
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

int	cd_relative2(char *ext, char *cwdext, char **argv)
{
	int	i;

	i = 0;
	if (chdir(cwdext) != 0)
	{
		printf("minishell: %s: No such file or directory\n", argv[0]);
		i = 1;
	}
	free(ext);
	free(cwdext);
	return (i);
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
		returnval = cd_relative2(ext, cwdext, argv);
	}
	else
	{
		printf("Error: could not get working directory\n");
		returnval = 1;
	}
	free(cwd);
	return (returnval);
}
