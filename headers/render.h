/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:37 by dderny            #+#    #+#             */
/*   Updated: 2025/02/05 08:49:28 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "classes/vector2d.h"
# include "mm256.h"
# include "so_long.h"
# include <mlx_int.h>

# define M256_NPIXEL (int)(sizeof(__m256i_u) / sizeof(unsigned int))

typedef struct s_data
{
	t_img		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_data;

void			mylx_pixel_put(t_img *img, int x, int y, int color);
void			mylx_m256_pixel_put(t_img *img, int x, int y, __m256i_u color);
unsigned int	*mylx_pixel_get(t_img *img, int x, int y);
__m256i_u		*mylx_m256_pixel_get(t_img *img, int x, int y);

void			*mylx_img_scale(void *mlx, t_img *img, int scale);
void			*mylx_img_blend(t_iaabb sqr, t_int2d pos, t_img *dest,
					t_img *src);
void			*mylx_img_copy(t_iaabb sqr, t_int2d pos, t_img *dest,
					t_img *src);

#endif