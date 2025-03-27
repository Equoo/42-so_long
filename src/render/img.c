/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:12 by dderny            #+#    #+#             */
/*   Updated: 2025/03/27 01:42:28 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <errno.h>
#include "classes/vector2d.h"
#include "mlx_int.h"
#include "render.h"

t_img	*mylx_xpm_to_img(void *mlx, char *path, int *width, int *height)
{
	t_img	*img;

	if (open(path, O_RDONLY) == -1)
		return (NULL);
	img = mlx_xpm_file_to_image(mlx, path, width, height);
	if (errno == 11)
		errno = 0;
	return (img);
}

/*void	*mylx_img_scale(void *mlx, t_img *img, int scale)
{
	t_img			*dest;
	t_int2d			pos;
	unsigned int	pixels[M256_NPIXEL];
	unsigned int	*src_pixels;
	int				width_scaled;

	width_scaled = img->width * scale;
	dest = mlx_new_image(mlx, width_scaled, img->height * scale);
	if (!dest)
		return (NULL);
	pos.y = -1;
	while (pos.y < img->height && ++pos.y + 1)
	{
		pos.x = 0;
		while (pos.x < width_scaled)
		{
			src_pixels = mylx_pixel_get(img, pos.x / scale, pos.y);
			if (width_scaled - pos.x >= M256_NPIXEL)
			{
				int i = 0;
				while (i < M256_NPIXEL)
				{
					pixels[i] = src_pixels[(pos.x % scale + i) / scale];
					i++;
				}
				mylx_m256_pixel_put(dest, pos.x, pos.y * scale, (__m256i)(__v8si){pixels[0], pixels[1], pixels[2], pixels[3], pixels[4], pixels[5], pixels[6], pixels[7]});
				pos.x += M256_NPIXEL;			
			}
			else
				mylx_pixel_put(dest, pos.x++, pos.y * scale, *src_pixels);
		}
		int i = 1;
		while (i < scale)
		{
			ft_memcpy(mylx_pixel_get(dest, 0, pos.y * scale + i), mylx_pixel_get(dest, 0, pos.y * scale), dest->width * sizeof(int));
			i++;
		}
	}
	return (dest);
}*/

void	*mylx_img_scale(void *mlx, t_img *img, int scale)
{
	t_img			*dest;
	t_int2d			pos;
	unsigned int	*src_pixels;
	unsigned int	*dst_pixels;
	int				i;

	dest = mlx_new_image(mlx, img->width * scale, img->height * scale);
	if (!dest)
		return (NULL);
	pos.y = -1;
	while (pos.y < img->height && ++pos.y + 1)
	{
		pos.x = 0;
		src_pixels = mylx_pixel_get(img, 0, pos.y);
		dst_pixels = mylx_pixel_get(dest, 0, pos.y * scale);
		while (pos.x < img->width)
		{
			i = 0;
			while (i < scale)
				dst_pixels[pos.x * scale + i++] = src_pixels[pos.x];
			pos.x++;
		}
		i = 1;
		while (i < scale)
		{
			ft_memcpy(mylx_pixel_get(dest, 0, pos.y * scale + i), dst_pixels, dest->width * sizeof(int));
			i++;
		}
	}
	return (dest);
}
