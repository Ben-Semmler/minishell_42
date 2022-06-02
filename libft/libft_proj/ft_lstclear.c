/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemmler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:46:08 by bsemmler          #+#    #+#             */
/*   Updated: 2021/09/23 18:54:10 by bsemmler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list *lst, void (*del)(void *))
{
	t_list	*pos;
	t_list	*tmpnxt;

	if (!lst || !del)
		return ;
	pos = lst;
	while (pos != NULL)
	{
		tmpnxt = pos->next;
		ft_lstdelone(pos, (*del));
		pos = tmpnxt;
	}
	lst = NULL;
}
