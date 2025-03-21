/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:59:04 by dderny            #+#    #+#             */
/*   Updated: 2025/03/20 03:17:33 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "classes/vector2d.h"
#include "colors.h"
#include "mlx_int.h"
#include "render.h"

static void internal_blend(t_copyimg *data, t_int2d real_size, int *i)
{
	t_int2d	pos;
	t_int2d	srcpos;

	while (*i < real_size.x * real_size.y)
	{
		pos = (t_int2d){*i % real_size.x, *i / real_size.x};
		if (data->flip & FLIP_HORIZ)
			srcpos.x = data->from.x + data->size.x - pos.x - 1;
		else
			srcpos.x = data->from.x + pos.x;
		if (data->flip & FLIP_VERT)
			srcpos.y = data->from.y + data->size.y - pos.y - 1;
		else
			srcpos.y = data->from.y + pos.y;
		pos = int2d_add(pos, data->to);
		mylx_pixel_put(data->dest, pos.x, pos.y,
			combine_channels(blend_by_alpha(
			split_channels(*mylx_pixel_get(data->dest, pos.x, pos.y), 0),
			split_channels(*mylx_pixel_get(data->src, srcpos.x, srcpos.y), 1)
			)));
		(*i)++;
	}
}

static void internal_blend_90(t_copyimg *data, t_int2d real_size, int *i)
{
	t_int2d	pos;
	t_int2d	srcpos;

	while (*i < real_size.x * real_size.y)
	{
		pos = (t_int2d){*i % real_size.x, *i / real_size.x};
		if (data->flip & FLIP_HORIZ)
			srcpos.x = data->from.x + pos.y;
		else
			srcpos.x = data->from.x + data->size.x - pos.y - 1;
		if (data->flip & FLIP_VERT)
			srcpos.y = data->from.y + data->size.y - pos.x - 1;
		else
			srcpos.y = data->from.y + pos.x;
		pos = int2d_add(pos, data->to);
		mylx_pixel_put(data->dest, pos.x, pos.y,
			combine_channels(blend_by_alpha(
			split_channels(*mylx_pixel_get(data->dest, pos.x, pos.y), 0),
			split_channels(*mylx_pixel_get(data->src, srcpos.x, srcpos.y), 1)
			)));
		(*i)++;
	}
}

static void internal_blend_minus90(t_copyimg *data, t_int2d real_size, int *i)
{
	t_int2d	pos;
	t_int2d	srcpos;

	while (*i < real_size.x * real_size.y)
	{
		pos = (t_int2d){*i % real_size.x, *i / real_size.x};
		if (data->flip & FLIP_HORIZ)
			srcpos.x = data->from.x + data->size.x - pos.y - 1;
		else
			srcpos.x = data->from.x + pos.y;
		if (data->flip & FLIP_VERT)
			srcpos.y = data->from.y + pos.x;
		else
			srcpos.y = data->from.y + data->size.y - pos.x - 1;
		pos = int2d_add(pos, data->to);
		mylx_pixel_put(data->dest, pos.x, pos.y,
			combine_channels(blend_by_alpha(
			split_channels(*mylx_pixel_get(data->dest, pos.x, pos.y), 0),
			split_channels(*mylx_pixel_get(data->src, srcpos.x, srcpos.y), 1)
			)));
		(*i)++;
	}
}

static void internal_blend_180(t_copyimg *data, t_int2d real_size, int *i)
{
	t_int2d	pos;
	t_int2d	srcpos;

	while (*i < real_size.x * real_size.y)
	{
		pos = (t_int2d){*i % real_size.x, *i / real_size.x};
		if (data->flip & FLIP_HORIZ)
			srcpos.x = data->from.x + pos.x;
		else
			srcpos.x = data->from.x + data->size.x - pos.x - 1;
		if (data->flip & FLIP_VERT)
			srcpos.y = data->from.y + pos.y;
		else
			srcpos.y = data->from.y + data->size.y - pos.y - 1;
		pos = int2d_add(pos, data->to);
		mylx_pixel_put(data->dest, pos.x, pos.y,
			combine_channels(blend_by_alpha(
			split_channels(*mylx_pixel_get(data->dest, pos.x, pos.y), 0),
			split_channels(*mylx_pixel_get(data->src, srcpos.x, srcpos.y), 1)
			)));
		(*i)++;
	}
}

void	*mylx_img_blend(t_copyimg data)
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
		internal_blend(&data, real_size, &i);
	else if (data.angle == 90)
		internal_blend_90(&data, real_size, &i);
	else if (data.angle == -90)
		internal_blend_minus90(&data, real_size, &i);
	else if (data.angle == 180)
		internal_blend_180(&data, real_size, &i);
	return (data.dest);
}
