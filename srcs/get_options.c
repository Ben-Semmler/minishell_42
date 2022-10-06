/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:05:05 by bsemmler          #+#    #+#             */
/*   Updated: 2022/09/16 18:42:13 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_command(t_action *action, char *input, int returnval);
int		get_argn(char *input);
char	*copy_arg(char *input, int returnval);
int		get_arg_size(char *input, bool include_quotes, int returnval);
int 	get_env_len(char *str);
char	 *get_key(char *str);

void	get_options(t_action *action, char *input, int returnval)
{
	int		i;
	int		argi;
	int		argn;

	i = get_command(action, input, returnval);
	argi = 0;
	argn = get_argn(&input[i]);
	action->argv = malloc(sizeof(char *) * (argn + 1));
	while (input[i] && argi < argn)
	{
		while (input[i] && input[i] == ' ')
			i++;
		action->argv[argi] = copy_arg(&input[i], returnval);
		i += get_arg_size(&input[i], 1, returnval);
		argi++;
	}
	action->argv[argi] = NULL;
	action->argc = argi;
}

int	get_command(t_action *action, char *input, int returnval)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (ft_strncmp(&input[i], "./", 2) == 0)
	{
		if (input[i] == 34 || input[i] == 39)
			i++;
		action->command = ft_strdup("./");
		i += 2;
	}
	else
	{
		action->command = copy_arg(&input[i], returnval);
		i += get_arg_size(&input[i], true, returnval);
	}
	return (i);
}

int	get_argn(char *input)
{
	char	quotations;
	int		argn;
	int		i;

	argn = 0 - (input[0] == ' ');
	i = 0;
	if (ft_strncmp(input, "./", 2) == 0)
		i += 2;
	while (input[i])
	{
		quotations = 0;
		while (input[i] && (quotations != 0 || input[i] != ' '))
		{
			quotations = check_quotations(input[i], quotations);
			if (input[i] == '\\')
				i++;
			i++;
		}
		while (input[i] == ' ')
			i++;
		argn++;
	}
	return (argn);
}

char	*copy_arg(char *input, int returnval)
{
	//insert env variables into the output string
	int		i;
	int		offset;
	char	quotations;
	char	prev_quotations;
	char	*arg;
	bool	interpret;

	//printf("==========================================\ncopying arg =%s\n", input);

	int arg_size = get_arg_size(input, 0, returnval);

	arg = malloc(arg_size + 1);
	i = 0;
	quotations = 0;
	offset = 0;
	interpret = true;

	while (input[i] && i - offset < arg_size)
	{
		prev_quotations = quotations;
		quotations = check_quotations(input[i], quotations);
		if (input[i] == 39)
		 	interpret = !interpret;
		if (input[i] == '$' && interpret)
		{
			if (input[i + 1] == '?')
			{
				int i2 = 0;
				while (ft_itoa(returnval)[i2])
				{
					arg[i - offset + i2] = ft_itoa(returnval)[i2];
					i2++;
				}
				i += 2;
				offset -= i2;
			}
			else
			{
				i++;
				offset++;
				//printf("insert data size =%d=\n", insert_data(&arg[i - offset], get_key(&input[i])));
				offset -= insert_data(&arg[i - offset], get_key(&input[i])) - ft_strlen(get_key(&input[i]));
				i += ft_strlen(get_key(&input[i]));
				//printf("offset	=%d=\ni	=%d=\noffset + i	=%d=\n", offset, i, i - offset);
			}
		}
		else if (input[i] == '\\' && input[i] && interpret)
		{
			arg[i - offset] = input[i + 1];
			offset++;
			i += 2;
		}
		else
		{
			if (prev_quotations != quotations)
				offset++;
			else
				arg[i - offset] = input[i];
			i++;
		}
	}
	arg[i - offset] = 0;
	//printf("arg =%s=\n==============================================\n", arg);
	return (arg);
}

int	get_arg_size(char *input, bool include_quotes, int returnval)
{
	//Add the size of env variables here
	int		len;
	bool	interpret;
	int		adjust;
	char	quotations;
	char	prev_quotations;
	int		env_len;

	len = 0;
	interpret = true;
	env_len = 0;
	adjust = 0;
	quotations = 0;
	while (input[len] && (quotations != 0 || input[len] != ' '))
	{
		if (input[len] == 39)
		 	interpret = !interpret;
		if (input[len] == '$' && interpret)
		{
			if (input[len + 1] == '?')
			{
				len += 2;
				env_len -= ft_strlen(ft_itoa(returnval));
			}
			else
			{
				len++;
				env_len += ft_strlen(search(get_key(&input[len])).data);
				//printf("env len for =%s=\n	got =%d=\n", search(get_key(&input[len])).data, env_len);
				env_len -= ft_strlen(get_key(&input[len])) + 1;
				//printf("env KEY len for =%s=\n	got =%zu=\n", get_key(&input[len]), ft_strlen(get_key(&input[len])));
				len += ft_strlen(get_key(&input[len]));
				if (include_quotes)
					env_len -= 2;
			}
		}
		else if (input[len] == '\\' && input[len] && interpret)
		{
			env_len--;
			len += 2;
		}
		else 
		{
			prev_quotations = quotations;
			quotations = check_quotations(input[len], quotations);
			if (prev_quotations != quotations)
				adjust++;
			len++;
		}
	}
	len += env_len;
	if (include_quotes)
		return (len);
	return (len - adjust);
}
