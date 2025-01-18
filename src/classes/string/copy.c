/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:26:45 by dderny            #+#    #+#             */
/*   Updated: 2025/01/18 22:18:27 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/string.h"

t_string	*string_copy(t_string *self)
{
	t_list	*str;
	t_list	*newlist;
	t_list	*new;

	str = self->str;
	newlist = NULL;
	new = NULL;
	while (str)
	{
		new = ft_lstnew(str->content);
		if (!new)
			break ;
		if (!newlist)
			newlist = new;
		str = str->next;
	}
	if (str)
		ft_lstclear(&newlist, &self->strdel);
	return (newlist);
}
