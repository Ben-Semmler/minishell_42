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

int	main(void)
{
	int		run;
	char	*input;
	char	*output;

	run = 1;
	while (run == 1)
	{
		input = readline("minishell& ");
		add_history(input);
		//vv - Do stuff with the input in here - vv -b
		output = switch_command(input, &run);
		if (output != NULL)
		{
			printf("%s", output);
			free(output);
		}
		free(input);
	}
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
