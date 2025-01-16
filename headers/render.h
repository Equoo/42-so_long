/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:37 by dderny            #+#    #+#             */
/*   Updated: 2025/01/15 16:38:29 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "so_long.h"
# include <immintrin.h>
# include <mlx_int.h>

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_div_epi32(__m256i __a, __m256i __b)
{
	return (__m256i)((__v8si)__a / (__v8si)__b);
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_mullo_epi32(__m256i __a, __m256i __b)
{
	return (__m256i)((__v8si)__a * (__v8si)__b);
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_add_epi32(__m256i __a, __m256i __b)
{
	return ((__m256i)((__v8si)__a + (__v8si)__b));
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_sub_epi32(__m256i __a, __m256i __b)
{
	return ((__m256i)((__v8si)__a - (__v8si)__b));
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_and_si256(__m256i __a, __m256i __b)
{
	return (__a & __b);
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_or_si256(__m256i __a, __m256i __b)
{
	return (__a | __b);
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_set1_epi32(int __i)
{
	return ((__m256i)(__v8si){__i, __i, __i, __i, __i, __i, __i, __i});
}

typedef struct s_data
{
	t_img	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}			t_data;

void		mylx_pixel_put(t_data *data, int x, int y, int color);
void		*mylx_img_scale(void *mlx, void *img, int scale);
void		*mylx_img_add(int x, int y, void *dest, void *src);
void		*mylx_img_addn(int x, int y, void *dest, void *src);

#endif