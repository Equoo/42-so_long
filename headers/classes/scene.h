/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:06:41 by dderny            #+#    #+#             */
/*   Updated: 2025/03/21 17:22:02 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

#include "ft_vector.h"
enum e_scene
{
	SCENE_GAME,
	SCENE_MENU
};

typedef enum e_class
{
	CLASS_ELEMENT,
	CLASS_ENTITY,
	CLASS_ACTOR,
	CLASS_PLAYER,
	CLASS_ENEMY,
	CLASS_ITEM,
	CLASS_HUD,
	CLASS_TERRAIN
}	t_class;

typedef struct s_scene
{
	char		*name;
	void		*env;
	void		*terrain;
	t_vector	elements;

	void		(*update)(struct s_scene *self);
}	t_scene;

void	scene_del(t_scene **self);
t_scene	*ft_scene(void *env, char *name);

#endif
