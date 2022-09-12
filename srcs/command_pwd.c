/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:18:08 by bsemmler          #+#    #+#             */
/*   Updated: 2022/04/14 18:18:09 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_pwd(const t_inputs *input)
{
	char	*cwd;

	//Use of input to appease -WWW, not needed for function
	if (input->argc == 0)
		;
	//Create buffer with size of PATH_MAX, fill using getcwd to get
	//the working directory and prints
	cwd = malloc(PATH_MAX + 1);
	if (getcwd(cwd, PATH_MAX + 1) != NULL)
		printf("%s\n", cwd);
	else
		printf("Error: could not get directory\n");
	free(cwd);
}
