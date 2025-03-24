/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:42 by dderny            #+#    #+#             */
/*   Updated: 2025/03/24 18:26:14 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include "classes/terrain.h"
#include <libft.h>
#include <stdint.h>

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
	element->base = element;
	element->class = CLASS_ELEMENT;
	element->scene = scene;
	element->del = element_del;
	element->id = elements_count;
	return (element);
}

t_element	*cast_element(void *element)
{
	if (!element)
		return (NULL);
	ft_print_memory(element, sizeof(t_terrain));
	__builtin_printf("%d\n", ((t_element *)(*(uintptr_t *)element))->id);
	return ((t_element *)(*(uintptr_t *)element));
}
