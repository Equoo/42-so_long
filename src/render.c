/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:12 by dderny            #+#    #+#             */
/*   Updated: 2025/01/15 02:38:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <immintrin.h>
#include <mlx.h>

#define NPIXELS (sizeof(__m256i_u) / 4)

void	mylx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	mylx_pixel_get(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

void	*mylx_img_scale(void *mlx, void *img, int scale)
{
	t_data	a;
	t_data	b;
	int		x;
	int		y;
	int		i;
	unsigned int color;

	a.img = img;
	a.addr = mlx_get_data_addr(a.img, &a.bpp, &a.line_length, &a.endian);
	b.img = mlx_new_image(mlx, a.img->width * scale, a.img->height * scale);
	b.addr = mlx_get_data_addr(b.img, &b.bpp, &b.line_length, &b.endian);
	y = 0;
	while (y < a.img->height)
	{
		x = 0;
		while (x < a.img->width)
		{
			color = mylx_pixel_get(&a, x, y);
			if (color == 0xFF000000 && ++x)
				continue ;
			i = 0;
			while (i < scale * scale && ++i)
				mylx_pixel_put(&b, x * scale + (i - 1) / scale, y * scale + (i
						- 1) % scale, color);
			x++;
		}
		y++;
	}
	return (b.img);
}

void	*mylx_img_addn(int x, int y, void *dest, void *src)
{
	t_data	a;
	t_data	b;

	a.img = dest;
	a.addr = mlx_get_data_addr(a.img, &a.bpp, &a.line_length, &a.endian);
	b.img = src;
	b.addr = mlx_get_data_addr(b.img, &b.bpp, &b.line_length, &b.endian);
	
	int		xi;
	int		yi;
	__m256i_u src_pixels;
	char	*dst;
	yi = 0;
	while (yi < b.img->height)
	{
		xi = 0;
		while ((unsigned long)xi < b.img->width / NPIXELS)
		{
			src_pixels = _mm256_loadu_si256((__m256i_u *)(b.addr + (yi * b.line_length + xi * NPIXELS * (b.bpp / 8))));
			dst = a.addr + ((yi + y) * a.line_length + (xi * NPIXELS + x) * (a.bpp / 8));
			
			_mm256_storeu_si256((__m256i_u *)dst, src_pixels);

			xi++;
		}
		yi++;
	}
	return (a.img);
}

void	*mylx_img_add(int x, int y, void *dest, void *src)
{
	t_data	a;
	t_data	b;

	a.img = dest;
	a.addr = mlx_get_data_addr(a.img, &a.bpp, &a.line_length, &a.endian);
	b.img = src;
	b.addr = mlx_get_data_addr(b.img, &b.bpp, &b.line_length, &b.endian);
	
	int		xi;
	int		yi;
	__m256i_u src_pixels;
	__m256i_u dst_pixels;
	//unsigned int color;
	char	*dst;
	yi = 0;
	while (yi < b.img->height)
	{
		xi = 0;
		while ((unsigned long)xi < b.img->width / NPIXELS)
		{
			src_pixels = _mm256_loadu_si256((__m256i_u *)(b.addr + (yi * b.line_length + xi * NPIXELS * (b.bpp / 8))));
			dst = a.addr + ((yi + y) * a.line_length + (xi * NPIXELS + x) * (a.bpp / 8));
			dst_pixels = _mm256_loadu_si256((__m256i_u *)dst);

			__m256i src_alpha = _mm256_srli_epi32(src_pixels, 24);
            __m256i src_red = _mm256_and_si256(_mm256_srli_epi32(src_pixels, 16), _mm256_set1_epi32(0xFF));
            __m256i src_green = _mm256_and_si256(_mm256_srli_epi32(src_pixels, 8), _mm256_set1_epi32(0xFF));
            __m256i src_blue = _mm256_and_si256(src_pixels, _mm256_set1_epi32(0xFF));

            __m256i dst_red = _mm256_and_si256(_mm256_srli_epi32(dst_pixels, 16), _mm256_set1_epi32(0xFF));
            __m256i dst_green = _mm256_and_si256(_mm256_srli_epi32(dst_pixels, 8), _mm256_set1_epi32(0xFF));
            __m256i dst_blue = _mm256_and_si256(dst_pixels, _mm256_set1_epi32(0xFF));

            __m256i inv_src_alpha = _mm256_sub_epi32(_mm256_set1_epi32(255), src_alpha);

            __m256i blended_red = _mm256_div_epi32(
                _mm256_add_epi32(
                	_mm256_mullo_epi32(src_red, inv_src_alpha),
                    _mm256_mullo_epi32(dst_red, src_alpha)),
                _mm256_set1_epi32(255));

            __m256i blended_green = _mm256_div_epi32(
                _mm256_add_epi32(
                    _mm256_mullo_epi32(src_green, inv_src_alpha),
                    _mm256_mullo_epi32(dst_green, src_alpha)),
                _mm256_set1_epi32(255));

            __m256i blended_blue = _mm256_div_epi32(
                _mm256_add_epi32(
                    _mm256_mullo_epi32(src_blue, inv_src_alpha),
                    _mm256_mullo_epi32(dst_blue, src_alpha)),
                _mm256_set1_epi32(255));

            // Reconstruct blended pixels
            __m256i blended_pixels = _mm256_or_si256(
                _mm256_or_si256(
                    _mm256_slli_epi32(blended_red, 16),
                    _mm256_slli_epi32(blended_green, 8)),
                blended_blue);

			//blended_pixels = _mm256_sub_epi32(_mm256_set1_epi32(255), blended_pixels);

			_mm256_storeu_si256((__m256i_u *)dst, blended_pixels);
			//*(__m256i_u *)dst = blended_red;

			xi++;
		}
		yi++;
	}
	return (a.img);
}
