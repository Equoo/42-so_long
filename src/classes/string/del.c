/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:26:45 by dderny            #+#    #+#             */
/*   Updated: 2025/01/05 21:15:10 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/string.h"
#include <stdlib.h>

void	string_del(t_string *self)
{
    ft_lstclear(self->str, &self->strdel);
	free(self);
}