/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   food.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/01/27 14:37:56 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOOD_H
# define FOOD_H
# include "entity.h"

typedef struct s_entity t_food;

t_food			*ft_food(void);

void			food_del(void);

#endif