/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:21:48 by bsemmler          #+#    #+#             */
/*   Updated: 2022/06/14 15:26:11 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_pipes
{
	char			**action;
	struct s_pipes	*next;
}	t_pipes;

char	*ft_strncpy(char *src, int size)
{
	int		i;
	char	*out;

	i = 0;
	out = malloc(sizeof(char) * (size + 1));
	while (src[i] && i < size)
	{
		out[i] = src[i];
		i++;
	}
	out[i] = 0;
	return (out);
}

char	**add_element(char **arr, char *toadd)
{
	int		i;
	char	**newarr;

	i = 0;
	while (arr[i] != NULL)
		i++;
	newarr = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (arr[i] != NULL)
	{
		newarr[i] = arr[i];
		i++;
	}
	newarr[i] = toadd;
	newarr[i + 1] = NULL;
	return (newarr);
}

int	main(void)
{
	int		run;
	char	*input;
	char	*output;
	t_pipes pipes;
	char	*pipearg;
	int		i;
	int		i2;

	run = 1;
	while (run == 1)
	{
		input = readline("minishell& ");
		add_history(input);
		//vv - Do stuff with the input in here - vv -b
		t_pipes *temppipes;
		temppipes = &pipes;
		temppipes->action = NULL;
		char	*tempin = NULL;
		i = 0;
		while ((size_t)i < ft_strlen(input))
		{
			i2 = 0;
			while (input[i + i2] && input[i + i2] != '|')
				i2++;
			tempin = ft_strncpy(&input[i], i2);
			if (temppipes->action != NULL)
			{
				temppipes->next = malloc(sizeof(t_pipes));
				temppipes = temppipes->next;
			}
			temppipes->action = get_options(tempin);
			temppipes->next = NULL;
			free(tempin);
			i += i2 + 2;
		}
		temppipes = &pipes;
		pipearg = NULL;
		while (temppipes != NULL)
		{
			output = switch_command(temppipes->action, &run);
			if (temppipes->next != NULL)
				temppipes->action = add_element(temppipes->action, output);
			else if (output != NULL)
			{
				printf("%s", output);
				free(output);
			}
			temppipes = temppipes->next;
		}
		free(input);


		//while ()
		//{
			//temppipes->action = get_options(input);
			//temppipes->next = NULL;
		//}
		//int	c_id = get_command_id(input);
		
		/*i = 0;
		while (split_input != 1)
		s_input = get_options(input);
		output = switch_command(s_input, &run);
		if (output != NULL)
		{
			printf("%s", output);
			free(output);
		}
		free(input);*/
	}
}

void	free_split_input(char **s_input)
{
	int	i;

	//Free the split input
	i = 0;
	while (s_input[i] != NULL)
	{
		free(s_input[i]);
		i++;
	}
	free(s_input);
}

// int	main(int argc, char **argv, char **env)
// {
// 	int		run;
// 	char	*input;
// 	char	*output;

// 	(void)argc;
// 	(void)argv;
// 	(void)env;
// 	char *test = "kerdfgkjny$USER ya mum";

// 	printf("%s\n", test);
// 	printf("%s\n", get_key(test));
// 	printf("%s\n", get_data(test));
// 	check_env(argv);
// 	run = 1;
// 	while (run == 1)
// 	{
// 		input = readline("minishell& ");
// 		add_history(input);
// 		//vv - Do stuff with the input in here - vv -b
// 		output = switch_command(input, &run);
// 		if (output != NULL)
// 		{
// 			printf("%s", output);
// 			free(output);
// 		}
// 		free(input);
// 	}
// }
