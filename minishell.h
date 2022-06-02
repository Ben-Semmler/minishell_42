/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:22:03 by bsemmler          #+#    #+#             */
/*   Updated: 2022/04/11 17:22:03 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>

char	*ft_joinfree(char *str1, int free1, char *str2, int free2);

int		get_command_id(char *input);
char	*switch_command(char *input, int *run);
char	**get_options(char *input);

char	*run_executable(char **input);
char	*command_echo(char **s_input);
char	*command_cd(char **s_input);
char	*command_pwd(char **s_input);

#endif
