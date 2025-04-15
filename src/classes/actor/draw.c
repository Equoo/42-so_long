/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:20:50 by dderny            #+#    #+#             */
/*   Updated: 2025/04/16 00:55:55 by dderny           ###   ########.fr       */
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
    {"B_S_1"},
    {"B_S_2"},
    {"Bow_Idle"},
    {"B_I_1"},
    {"B_I_2"},
    {"rook_around"},
    {"R_A_Right"},
    {"R_A_1"},
    {"R_A_2"},
    {"R_A_3"},
    {"R_A_Left"},
    {"R_A_4"},
    {"R_A_5"},
    {"R_A_6"},
    {"Eat"},
    {"Eat_1"},
    {"Eat_2"},
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
    {"On_2_Paws"},
    {"On_4_Paws"},
    {"Scratching"},
    {"Pac-Cat"},
    {"Goomba"}
};

#define ANIM_COUNT 60
#define ANIM_SIZE 32
#define SCREEN_WIDTH 340

// Function to draw each animation at spaced positions
void draw_all_animations(t_element *self, void *texture, t_render *render, t_transform origin) {
	static double last_anim_times[ANIM_COUNT + 1] = {0};
	static double cycles[ANIM_COUNT + 1] = {0};

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
	transform = t_from_pos(to_int2d(float2d_sub(float2d_add(self->pos, self->txt_off_pos), self->scene->cam_pos)));
	if (actor->direction == -1)
		transform.scale.x = -1;

	//draw_all_animations(self, self->texture, render, transform);

	texture_blend_anim(self->texture, render->buffer, transform, self->anim, self->cycle);
	
    t_int2d pos = to_int2d(float2d_sub(self->pos, self->scene->cam_pos));
	if (pos.x >= 0 && pos.x < render->buffer->width && pos.y >= 0 && pos.y < render->buffer->height)
		mylx_pixel_put(render->buffer, pos.x, pos.y, 0x00FF00);
	if (pos.x + actor->entity->hull.a.x >= 0 && pos.x + actor->entity->hull.a.x < render->buffer->width
		&& pos.y + actor->entity->hull.a.y >= 0 && pos.y + actor->entity->hull.a.y < render->buffer->height)
		mylx_pixel_put(render->buffer, pos.x + actor->entity->hull.a.x, pos.y + actor->entity->hull.a.y, 0x0000FF);
	if (pos.x + actor->entity->hull.b.x >= 0 && pos.x + actor->entity->hull.b.x < render->buffer->width
		&& pos.y + actor->entity->hull.b.y >= 0 && pos.y + actor->entity->hull.b.y < render->buffer->height)
		mylx_pixel_put(render->buffer, pos.x + actor->entity->hull.b.x, pos.y + actor->entity->hull.b.y, 0x0000FF);
}
