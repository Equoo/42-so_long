/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:37 by dderny            #+#    #+#             */
/*   Updated: 2025/01/14 13:08:04 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include <mlx_int.h>
# include "so_long.h"

typedef struct	s_data {
	t_img	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;

void	mylx_pixel_put(t_data *data, int x, int y, int color);
void	*mylx_img_scale(void *mlx, void *img, int scale);
void	*mylx_img_add(int x, int y, void *dest, void *src);

#endif