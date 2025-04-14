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
#include "scene.h"
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
	frog->actor->anim_couroutine = &frog_anim_coroutine;
	frog->base->update = &frog_update;
	frog->base->class = CLASS_frog;
	frog->base->parent = frog;
	frog->base->del = &frog_del;
	frog->base->texture = ft_texture(&scene->env->render, "./textures/cat.xpm");
	frog->base->txt_off_pos = (t_float2d){-16, -31};
	frog->entity->hull = (t_faabb){{-8, -14}, {8, 0}};
	if (!frog->base->texture)
	{
		frog->base->del(&frog->base);
		return (NULL);
	}
	return (frog);
}

t_frog	*cast_frog(void *frog)
{
	if (!frog)
		return (NULL);
	return ((t_frog *)(((uintptr_t *)frog))[2]);
}
