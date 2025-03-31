/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:06:41 by dderny            #+#    #+#             */
/*   Updated: 2025/03/31 17:30:53 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "classes/vector2d.h"
# include <ft_bool.h>
# include <libft.h>

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
	CLASS_TERRAIN,
	CLASS_BACKGROUND
}	t_class;

typedef struct s_scene
{
	char		*name;
	void		*env;
	t_bool		removed;
	t_int2d		cam_pos;
	void		*terrain;
	t_list		*elements;

	void		(*update)(struct s_scene *self);
}	t_scene;

void	scene_del(void *self);
t_scene	*ft_scene(void *env, char *name);

int		scene_add(t_scene *self, void *element);

#endif
