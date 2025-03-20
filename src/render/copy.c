/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:44:50 by dderny            #+#    #+#             */
/*   Updated: 2025/03/20 00:54:22 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "classes/vector2d.h"
#include "mlx_int.h"
#include "render.h"

static void internal_copy(t_copyimg *data, t_int2d real_size, int *i)
{
	t_int2d	pos;
	t_int2d	src_pos;

	while (*i < real_size.x * real_size.y)
	{
		pos = (t_int2d){*i % real_size.x, *i / real_size.x};
		if (data->flip & FLIP_HORIZ)
			src_pos.x = data->from.x + data->size.x - pos.x;
		else
			src_pos.x = data->from.x + pos.x;
		if (data->flip & FLIP_VERT)
			src_pos.y = data->from.y + data->size.y - pos.y;
		else
			src_pos.y = data->from.y + pos.y;
		pos = int2d_add(pos, data->to);
		mylx_pixel_put(data->dest, pos.x, pos.y,
				*mylx_pixel_get(data->src, src_pos.x, src_pos.y));
		(*i)++;
	}
}

static void internal_copy_90(t_copyimg *data, t_int2d real_size, int *i)
{
	t_int2d	pos;
	t_int2d	src_pos;

	while (*i < real_size.x * real_size.y)
	{
		pos = (t_int2d){*i % real_size.x, *i / real_size.x};
		if (data->flip & FLIP_HORIZ)
			src_pos.x = data->from.x + pos.y;
		else
			src_pos.x = data->from.x + data->size.x - pos.y;
		if (data->flip & FLIP_VERT)
			src_pos.y = data->from.y + data->size.y - pos.x;
		else
			src_pos.y = data->from.y + pos.x;
		pos = int2d_add(pos, data->to);
		mylx_pixel_put(data->dest, pos.x, pos.y,
				*mylx_pixel_get(data->src, src_pos.x, src_pos.y));
		(*i)++;
	}
}

static void internal_copy_minus90(t_copyimg *data, t_int2d real_size, int *i)
{
	t_int2d	pos;
	t_int2d	src_pos;

	while (*i < real_size.x * real_size.y)
	{
		pos = (t_int2d){*i % real_size.x, *i / real_size.x};
		if (data->flip & FLIP_HORIZ)
			src_pos.x = data->from.x + data->size.x - pos.y;
		else
			src_pos.x = data->from.x + pos.y;
		if (data->flip & FLIP_VERT)
			src_pos.y = data->from.y + pos.x;
		else
			src_pos.y = data->from.y + data->size.y - pos.x;
		pos = int2d_add(pos, data->to);
		mylx_pixel_put(data->dest, pos.x, pos.y,
				*mylx_pixel_get(data->src, src_pos.x, src_pos.y));
		(*i)++;
	}
}

static void internal_copy_180(t_copyimg *data, t_int2d real_size, int *i)
{
	t_int2d	pos;
	t_int2d	src_pos;

	while (*i < real_size.x * real_size.y)
	{
		pos = (t_int2d){*i % real_size.x, *i / real_size.x};
		if (data->flip & FLIP_HORIZ)
			src_pos.x = data->from.x + pos.x;
		else
			src_pos.x = data->from.x + data->size.x - pos.x;
		if (data->flip & FLIP_VERT)
			src_pos.y = data->from.y + pos.y;
		else
			src_pos.y = data->from.y + data->size.y - pos.y;
		pos = int2d_add(pos, data->to);
		mylx_pixel_put(data->dest, pos.x, pos.y,
				*mylx_pixel_get(data->src, src_pos.x, src_pos.y));
		(*i)++;
	}
}

void	*mylx_img_copy(t_copyimg data)
{
	t_int2d	real_size;
	int		i;

	real_size = data.size;
	if (!(data.angle % 180))
		real_size = (t_int2d){real_size.y, real_size.x};
	i = 0;
	if (data.to.x < 0)
		i += -data.to.x;
	if (data.to.y < 0)
		i += -data.to.y * data.dest->width;
	if (real_size.x + data.to.x > data.dest->width)
		real_size.x -= real_size.x + data.to.x - data.dest->width;
	if (real_size.y + data.to.y > data.dest->width)
		real_size.y -= real_size.y + data.to.y - data.dest->width;
	if (data.angle == 0)
		internal_copy(&data, real_size, &i);
	else if (data.angle == 90)
		internal_copy_90(&data, real_size, &i);
	else if (data.angle == -90)
		internal_copy_minus90(&data, real_size, &i);
	else if (data.angle == 180)
		internal_copy_180(&data, real_size, &i);
	return (data.dest);
}
