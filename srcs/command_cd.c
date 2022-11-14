/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:31:21 by bsemmler          #+#    #+#             */
/*   Updated: 2022/11/14 15:45:33 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		cwdext = ft_strjoin(cwd, ext);
		ext = ft_strjoin("/", argv[0]);
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
