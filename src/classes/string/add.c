/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:26:45 by dderny            #+#    #+#             */
/*   Updated: 2025/01/05 21:04:42 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/string.h"

t_string *string_add(t_string *self, t_string *b)
{
    t_list	*str;
	t_list	*sstr;

	str = b->str;
	sstr = ft_lstlast(self->str);
	while (str)
	{
		sstr = ft_lstnew(str->content);
		if (!sstr)
			break ;
		ft_lstadd_back(&self->str, sstr);
		str = str->next;
	}
	if (str)
		return (NULL);
	return (self);
}