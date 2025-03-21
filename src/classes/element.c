/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:42 by dderny            #+#    #+#             */
/*   Updated: 2025/03/21 16:56:56 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include <libft.h>

void	element_del(t_element **self)
{
	free(*self);
	*self = NULL;
}

t_element	*ft_element(t_scene *scene)
{
	static int  elements_count = 0;
	t_element *element;

	element = ft_calloc(1, sizeof(t_element));
	if (!element)
		return (NULL);
	elements_count++;
	*element = (t_element){0};
	element->class = CLASS_ELEMENT;
	element->scene = scene;
	element->del = element_del;
	element->id = elements_count;
	return (element);
}
