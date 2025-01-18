/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:26:45 by dderny            #+#    #+#             */
/*   Updated: 2025/01/18 22:17:42 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/string.h"

t_string	*string_join(t_string *self, t_string *b)
{
	t_string	*new;

	new = self->copy(self);
	if (!new)
		return (NULL);
	if (new->add(new, b))
		return (NULL);
	return (self);
}
