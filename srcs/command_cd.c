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

char	*cd_absolute(char **s_input);
char	*cd_relative(char **s_input);

char	*command_cd(char **s_input)
{
	if (s_input[1] == NULL)
		return (NULL);
	if (s_input[1][0] == '/')
		return (cd_absolute(s_input));
	return (cd_relative(s_input));
}

char	*cd_absolute(char **s_input)
{
	char	*output;

	output = NULL;
	if (chdir(s_input[1]) != 0)
		output = ft_joinfree(ft_strjoin("minishell: ", s_input[1]), 1,
				": No such file or directory\n", 0);
	return (output);
}

char	*cd_relative(char **s_input)
{
	char	*cwd;
	char	*ext;
	char	*cwdext;
	char	*output;

	output = NULL;
	cwd = malloc(PATH_MAX + 1);
	if (getcwd(cwd, PATH_MAX + 1) != NULL)
	{
		ext = ft_strjoin("/", s_input[1]);
		cwdext = ft_strjoin(cwd, ext);
		if (chdir(cwdext) != 0)
			output = ft_joinfree(ft_strjoin("minishell: ", s_input[1]), 1,
					": No such file or directory\n", 0);
		free(ext);
		free(cwdext);
	}
	else
		output = ft_strdup("Error: could not get working directory\n");
	free(cwd);
	return (output);
}
