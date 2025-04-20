/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frog.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:32:11 by dderny            #+#    #+#             */
/*   Updated: 2025/03/25 02:09:29 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/frog.h"
#include "collisions.h"
#include "render.h"
#include "scene.h"
#include "seed.h"
#include "texture.h"
#include "libft.h"
#include "so_long.h"
#include <stdlib.h>
#include <stdint.h>

void	frog_del(t_element **self)
{
	t_frog	*frog;

	frog = (t_frog *)(*self)->parent;
	actor_del(self);
	if (frog)
		free(frog);
}

static int	init(t_frog *frog, t_render *render)
{
	frog->textures[0] = ft_texture(render, "./textures/frog_blue_blue.xpm");
	frog->textures[1] = ft_texture(render, "./textures/frog_blue_brown.xpm");
	frog->textures[2] = ft_texture(render, "./textures/frog_green_blue.xpm");
	frog->textures[3] = ft_texture(render, "./textures/frog_green_brown.xpm");
	frog->textures[4] = ft_texture(render, "./textures/frog_purple_blue.xpm");
	frog->textures[5] = ft_texture(render, "./textures/frog_purple_white.xpm");
	if (!frog->textures[0] || !frog->textures[1] || !frog->textures[2]
		|| !frog->textures[3] || !frog->textures[4] || !frog->textures[5])
		return (1);
	frog->base->texture = frog->textures[rand_int() % 6];
	frog->base->anim_coroutine = &frog_anim_coroutine;
	frog->base->txt_off_pos = (t_float2d){-21, -31};
	frog->entity->hull = (t_aabb){{-11, -15}, {11, 0}, {0}, {0}};
	return (0);
}

t_frog	*ft_frog(t_scene *scene)
{
	t_actor	*actor;
	t_frog	*frog;

	actor = ft_actor(scene);
	if (!actor)
		return (NULL);
	frog = ft_calloc(1, sizeof(t_frog));
	if (!frog)
	{
		actor->base->del(&actor->base);
		return (NULL);
	}
	frog->base = actor->base;
	frog->entity = actor->entity;
	frog->actor = actor;
	frog->base->class = CLASS_FROG;
	frog->base->parent = frog;
	frog->base->del = &frog_del;
	if (init(frog, &scene->env->render))
	{
		frog->base->del(&frog->base);
		return (NULL);
	}
	return (frog);
}

void frog_anim_coroutine(t_element *self, t_render *render)
{
	t_frog	*frog;
	float	speed;

	(void)render;
	frog = (t_frog *)self->parent;
	speed = float2d_length(frog->entity->velocity);
	if (frog->entity->b_isground && speed >= 0.05)
	{
			frog->base->anim = "Hop";
	}
	else
		frog->base->anim = "Idle";
}
