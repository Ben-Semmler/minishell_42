/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:58:33 by bsemmler          #+#    #+#             */
/*   Updated: 2022/07/12 14:58:34 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_quotations(char to_check, char quotations)
{
	if (to_check == 34 || to_check == 39)
	{
		if (quotations == 0)
			quotations = to_check;
		else if (quotations == to_check)
			quotations = 0;
	}
	return (quotations);
}
