/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:12 by dderny            #+#    #+#             */
/*   Updated: 2025/04/23 17:00:47 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <errno.h>
#include "vector2d.h"
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
	while (++pos.y < img->height)
	{
		src_pixels = mylx_pixel_get(img, 0, pos.y);
		dst_pixels = mylx_pixel_get(dest, 0, pos.y * scale);
		pos.x = img->width * scale;
		while (pos.x-- > 0)
			dst_pixels[pos.x] = src_pixels[pos.x / scale];
		i = 1;
		while (i < scale)
			ft_memcpy(mylx_pixel_get(dest, 0, pos.y * scale + i++),
				dst_pixels, dest->width * sizeof(int));
	}
	return (dest);
}
