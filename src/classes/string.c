/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:26:48 by dderny            #+#    #+#             */
/*   Updated: 2025/01/26 23:09:48 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/string.h"
#include <libft.h>
#include <stdlib.h>

static void	string_strdel(t_list *lst)
{
	free(lst);
}

static t_list	*from_char(char *str)
{
	t_list	*lst;
	t_list	*tmp;
	char	*c;

	lst = ft_lstnew(NULL);
	while (lst && *str)
	{
		c = malloc(sizeof(char));
		if (!c)
			break ;
		*c = str;
		tmp = ft_lstnew(c);
		if (!tmp)
			break ;
		ft_lstadd_back(&lst, tmp);
	}
	if (!lst)
		return (newlist);
}

t_string	*ft_string(char *str)
{
	t_string	*string;

	string = ft_calloc(1, sizeof(t_string));
	string->str = from_char(str);
	if (!string->str)
		return (NULL);
	string->copy = &string_copy;
	string->join = &string_join;
	string->add = &string_add;
	string->len = &string_len;
	string->del = &string_del;
	string->join = &string_join;
	return (string);
}
