/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:37 by dderny            #+#    #+#             */
/*   Updated: 2025/01/15 02:35:21 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include <mlx_int.h>
# include "so_long.h"

#include <immintrin.h>

static __inline __m256i_u __attribute__((__always_inline__, __nodebug__))
_mm256_div_epi32(__m256i_u __a, __m256i_u __b)
{
  return __a / __b;
}

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
void	*mylx_img_addn(int x, int y, void *dest, void *src);

#endif