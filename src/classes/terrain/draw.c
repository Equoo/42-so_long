/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:17:11 by dderny            #+#    #+#             */
/*   Updated: 2025/03/31 14:59:45 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "classes/vector2d.h"
#include "ft_bool.h"
#include "libft.h"
#include "seed.h"

typedef struct s_prob {
	double	ratio;
	char	*type;
}	t_prob;

char	getindir(t_terrain *self, t_int2d pos, int dir)
{
	const int dirs[][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};

	if (pos.x + dirs[dir][0] < 0 || pos.x + dirs[dir][0] >= self->w
		|| pos.y + dirs[dir][1] < 0 || pos.y + dirs[dir][1] >= self->h)
		return (MAP_WALL);
	return (self->grid[pos.x + pos.y * self->w + dirs[dir][0] + dirs[dir][1] * self->w]);
}

int	get_facing(t_terrain *self, t_int2d pos, int dirs[4])
{
	int			cur_dirs[4];
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (i < 4)
	{
		cur_dirs[i] = 0;
		if (getindir(self, pos, i) == MAP_WALL)
		{
			cur_dirs[i] = 1;
			count++;
		}
	}
	ft_memcpy(dirs, cur_dirs, sizeof(int) * 4);
	return (count);
}

typedef char *(*t_frule)(t_terrain *self, t_int2d pos, t_transform *transform);

t_bool	rule_top_grass(t_terrain *self, t_int2d pos, char **slice, t_transform *transform)
{
	const char 	textures[][19] = {"ground_top_green_1", "ground_top_green_2"};
	int			dirs[4];
	
	if (get_facing(self, pos, dirs) != 3)
		return (FALSE);
	if (dirs[DIR_TOP] == 0)
		transform->angle = 180;
	else if (dirs[DIR_LEFT] == 0)
		transform->angle = 90;
	else if (dirs[DIR_RIGHT] == 0)
		transform->angle = -90;
	*slice = ft_strdup(textures[rand_int() % 2]);
	return (TRUE);
}

t_bool	rule_corner_grass(t_terrain *self, t_int2d pos, char **slice, t_transform *transform)
{
	const char 	textures[][22] = {"ground_corner_green_1",
				"ground_corner_green_2"};
	int			dirs[4];
	
	if (get_facing(self, pos, dirs) != 2)
		return (FALSE);
	if (dirs[DIR_TOP] == 0 && dirs[DIR_RIGHT] == 0)
		transform->angle = 90;
	else if (dirs[DIR_BOTTOM] == 0 && dirs[DIR_LEFT] == 0)
		transform->angle = -90;
	else if (dirs[DIR_BOTTOM] == 0 && dirs[DIR_RIGHT] == 0)
		transform->angle = 180;
	if (!transform->angle && !(dirs[DIR_TOP] == 0 && dirs[DIR_LEFT] == 0) )
		return (FALSE);
	*slice = ft_strdup(textures[rand_int() % 2]);
	return (TRUE);
}

t_bool	rule_platform(t_terrain *self, t_int2d pos, char **slice, t_transform *transform)
{
	const char 	textures[][20] = {"platform_left_start", "platform",
			"platform_right_start"};
	int			dirs[4];
	
	if (get_facing(self, pos, dirs) != 2)
		return (FALSE);
	if (dirs[DIR_TOP] == 0 && dirs[DIR_BOTTOM] == 0)
	{
		if (dirs[DIR_LEFT] == 0)
			transform->angle = 90;
		else if (dirs[DIR_RIGHT] == 0)
			transform->angle = -90;
	}
	else if (dirs[DIR_LEFT] == 0 && dirs[DIR_RIGHT] == 0)
	{
		if (dirs[DIR_TOP] == 0)
			transform->angle = 0;
		else if (dirs[DIR_BOTTOM] == 0)
			transform->angle = 180;
	}
	if (!transform->angle)
		return (FALSE);
	return (TRUE);
}

void	get_wall_rules()
{
	const t_frule	*rules[] = {&rule_top_grass, &rule_corner_grass};

}








void	terrain_draw(t_element *self_element, t_img *buffer)
{
	const char 	corner_ground_slices[][64] = {"ground_corner_green_1", "ground_corner_green_2"};
	const char 	ground_slices[][64] = {"ground_mid_moss", "ground_mid_green_2", "ground_mid_green_3", "ground_mid_green_4", "ground_mid_red", "ground_mid_moss"};
	t_terrain	*self;
	int			i;
	t_int2d		pos;
	t_int2d		offset;
	char		*tex;

	offset = (t_int2d){0, 0};

	self = (t_terrain *)self_element->parent;
	i = -1;
	while (++i + 1 && self->grid[i])
	{
		if (self->grid[i] != MAP_WALL)
			continue;
		pos = (t_int2d){i % self->w, i / self->w};

		int		angle = 0;
		if (getindir(self, pos, DIR_TOP) != MAP_WALL // PLATFORMS
			&& getindir(self, pos, DIR_BOTTOM) != MAP_WALL)
		{
			if (getindir(self, pos, DIR_RIGHT) == MAP_WALL
				&& (getindir(self, int2d_add(pos, (t_int2d){1,0}), DIR_TOP) == MAP_WALL
				|| getindir(self, int2d_add(pos, (t_int2d){1,0}), DIR_BOTTOM) == MAP_WALL))
				tex = "platform_left_start";
			else if (getindir(self, pos, DIR_LEFT) == MAP_WALL
				&& (getindir(self, int2d_add(pos, (t_int2d){-1,0}), DIR_TOP) == MAP_WALL
				|| getindir(self, int2d_add(pos, (t_int2d){-1,0}), DIR_BOTTOM) == MAP_WALL))
				tex = "platform_right_start";
			else
				tex = "platform";
		}
		else if (getindir(self, pos, DIR_TOP) != MAP_WALL // GROUNDS FACING AIR
			|| getindir(self, pos, DIR_BOTTOM) != MAP_WALL)
		{
			if (getindir(self, pos, DIR_LEFT) != MAP_WALL
				|| getindir(self, pos, DIR_RIGHT) != MAP_WALL)
			{
				angle = getindir(self, pos, DIR_RIGHT) != MAP_WALL ? (getindir(self, pos, DIR_BOTTOM) != MAP_WALL ? 180 : -90) : (getindir(self, pos, DIR_BOTTOM) != MAP_WALL ? 90 : 0);
				tex = (char *)corner_ground_slices[rand_int() % 2];
			}
			else
			{
				angle = getindir(self, pos, DIR_TOP) != MAP_WALL ? 0 : 180;
				tex = (char *)top_ground_slices[rand_int() % 2];
			}
		}
		else if (getindir(self, pos, DIR_LEFT) != MAP_WALL // GROUNDS FACING AIR
			|| getindir(self, pos, DIR_RIGHT) != MAP_WALL)
		{
			angle = getindir(self, pos, DIR_LEFT) != MAP_WALL ? 90 : -90;
			tex = (char *)top_ground_slices[rand_int() % 2];
		}
		else // GROUND
			tex = "ground";
		texture_draw_slice(self->base->texture, buffer, (t_transform){(t_int2d){
				offset.x + pos.x * 16, offset.y + pos.y * 16},
				.angle = angle}, tex);
	}

	i = -1;
	while (++i + 1 && self->grid[i])
	{
		if (self->grid[i] != MAP_WALL || rand_int() % 8 != 0)
			continue;
		pos = (t_int2d){i % self->w, i / self->w};

		if (getindir(self, pos, DIR_TOP) == MAP_WALL
			&& getindir(self, pos, DIR_BOTTOM) == MAP_WALL
			&& getindir(self, pos, DIR_LEFT) == MAP_WALL
			&& getindir(self, pos, DIR_RIGHT) == MAP_WALL)
			tex = (char *)ground_slices[rand_int() % 6];
		else
			continue;

		texture_draw_slice(self->base->texture, buffer,(t_transform){
			{offset.x + pos.x * 16, offset.y + pos.y * 16}, {0}, 0}, tex);
	}
}
