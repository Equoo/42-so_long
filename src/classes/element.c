/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:42 by dderny            #+#    #+#             */
/*   Updated: 2025/01/27 09:26:43 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include <libft.h>

static void	element_draw(t_element *self)
{
}

void	element_del(t_element *self)
{
	free(self);
}

t_element	*ft_element(void)
{
	t_element *element;

	element = ft_calloc(1, sizeof(t_element));
	element->draw = &element_draw;
	return (element);
}