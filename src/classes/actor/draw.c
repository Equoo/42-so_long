/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:20:50 by dderny            #+#    #+#             */
/*   Updated: 2025/04/06 15:14:51 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/entities/actor.h"
#include "texture.h"
#include "vector2d.h"
#include "render.h"
#include "so_long.h"

typedef struct {
    char *name;
} Animation;

// List of animations
Animation animations[] = {
    {"Sit_1"},
    {"Sit_2"},
    {"Idle_1"},
    {"Idle_2"},
    {"W_1"},
    {"W_2"},
    {"W_3"},
    {"Run_1"},
    {"Run_2"},
    {"Rest_1"},
    {"Rest_2"},
    {"Dream"},
    {"Creep_Up"},
    {"Crawl"},
    {"Sit_U_D"},
    {"Sit_Up"},
    {"Sit_Down"},
    {"Stop"},
    {"Aggress"},
    {"J_1"},
    {"J_U_D"},
    {"J_2"},
    {"J_3"},
    {"Bow_Sit"},
    {"Bow_Idle"},
    {"Eat"},
    {"Dmg"},
    {"Death_1"},
    {"Death_2"},
    {"Deat_End"},
    {"Spawn_2"},
    {"Attack_1"},
    {"Attack_2"},
    {"Attack_3"},
    {"Attack_4"},
    {"Attack_5"},
    {"Dig_1"},
    {"Dig_2"},
    {"Pooping"},
    {"Paws"},
    {"Scratching"},
    {"Pac-Cat"},
    {"Goomba"}
};

#define ANIM_COUNT 42
#define ANIM_SIZE 32
#define SCREEN_WIDTH 340

// Function to draw each animation at spaced positions
void draw_all_animations(t_element *self, void *texture, t_render *render, t_transform origin) {
	static double last_anim_times[ANIM_COUNT] = {0};
	static double cycles[ANIM_COUNT] = {0};

    int x = 8, y = 0;
    for (int i = 0; i < (int)ANIM_COUNT; i++) {
        t_transform transform = origin;
        transform.pos.x = x;
        transform.pos.y = y;

		double time = ((t_gameenv *)self->scene->env)->time;

		if (!last_anim_times[i])
			last_anim_times[i] = time;
		cycles[i] = (time - last_anim_times[i])
				/ texture_slice_time(texture, animations[i].name);
		if (cycles[i] >= 1)
		{
			cycles[i] = 0;
			last_anim_times[i] = time;
		}


        texture_blend_anim(texture, render->buffer, transform, animations[i].name, cycles[i]);

		draw_text(render, animations[i].name, (t_float2d){x + 8, y + 32}, 32);

        x += ANIM_SIZE - 4; // Space between animations
		if (x + ANIM_SIZE + 8 > SCREEN_WIDTH) { // Move to next row if exceeding screen width
            x = 8;
            y += ANIM_SIZE - 4;
        }
    }
}

void	actor_draw(t_element *self, t_render *render)
{
	t_actor		*actor;
	t_transform	transform;

	actor = cast_actor(self->parent);
	if (!actor)
		return ;
	if (actor->anim_couroutine)
		actor->anim_couroutine(actor);
	transform = t_from_pos(to_int2d(float2d_add(self->pos, self->txt_off_pos)));
	if (actor->direction == -1)
		transform.scale.x = -1;

	draw_all_animations(self, self->texture, render, transform);

	texture_blend_anim(self->texture, render->buffer, transform, self->anim, self->cycle);

	//if (self->pos.x >= 0 && self->pos.x < buffer->width && self->pos.y >= 0 && self->pos.y < buffer->height)
	//	mylx_pixel_put(buffer, self->pos.x, self->pos.y, 0x00FF00);
	//if (self->pos.x + actor->entity->hull.a.x >= 0 && self->pos.x + actor->entity->hull.a.x < buffer->width
	//	&& self->pos.y + actor->entity->hull.a.y >= 0 && self->pos.y + actor->entity->hull.a.y < buffer->height)
	//	mylx_pixel_put(buffer, self->pos.x + actor->entity->hull.a.x, self->pos.y + actor->entity->hull.a.y, 0x0000FF);
	//if (self->pos.x + actor->entity->hull.b.x >= 0 && self->pos.x + actor->entity->hull.b.x < buffer->width
	//	&& self->pos.y + actor->entity->hull.b.y >= 0 && self->pos.y + actor->entity->hull.b.y < buffer->height)
	//	mylx_pixel_put(buffer, self->pos.x + actor->entity->hull.b.x, self->pos.y + actor->entity->hull.b.y, 0x0000FF);
}
