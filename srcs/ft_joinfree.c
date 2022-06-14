/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:09:21 by bsemmler          #+#    #+#             */
/*   Updated: 2022/06/06 12:25:47 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Same as ft_strjoin but has the option to free strings used as input

char	*ft_joinfree(char *str1, int free1, char *str2, int free2)
{
	char	*joined;

	joined = ft_strjoin(str1, str2);
	if (free1 == 1)
		free(str1);
	if (free2 == 1)
		free(str2);
	return (joined);
}
