/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:37 by dderny            #+#    #+#             */
/*   Updated: 2025/04/01 02:22:55 by dderny           ###   ########.fr       */
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

typedef enum e_imgflip
{
	FLIP_NONE,
	FLIP_HORIZ,
	FLIP_VERT
}				t_imgflip;

typedef struct s_copyimg
{
	t_int2d		from;
	t_int2d		size;
	t_int2d		to;
	t_img		*src;
	t_img		*dest;
	t_imgflip	flip;
	int			angle;
}				t_copyimg;

void			mylx_pixel_put(t_img *img, int x, int y, unsigned int color);
void			mylx_m256_pixel_put(t_img *img, int x, int y, __m256i_u color);
unsigned int	*mylx_pixel_get(t_img *img, int x, int y);
__m256i_u		*mylx_m256_pixel_get(t_img *img, int x, int y);


/**
** Secure way to open a xpm image
** @param mlx: the mlx pointer
** @param path: the image path
** @param width: width pointer
** @param height: height pointer
** @return the new image
*/
t_img	*mylx_xpm_to_img(void *mlx, char *path, int *width, int *height);

/**
** Copy and scale an image to a new image
** @param mlx: the mlx pointer
** @param img: the image to scale
** @param scale: the scale factor
** @return the new image
*/
void			*mylx_img_scale(void *mlx, t_img *img, int scale);

/*
** Copy an image to a new image
** @param sqr: the square to copy
** @param pos: the position to paste
** @param dest: the destination image
** @param src: the source image
** @return the destination image
*/
void			*mylx_img_fast_blend(t_iaabb sqr, t_int2d pos, t_img *dest,
					t_img *src);

void			*mylx_img_blend(t_copyimg data);

/*
** Blend an image to a new image with alpha channel
** @param sqr: the square to blend
** @param pos: the position to paste
** @param dest: the destination image
** @param src: the source image
** @return the destination image
*/
void			*mylx_img_fast_copy(t_iaabb sqr, t_int2d pos, t_img *dest,
					t_img *src);

void			*mylx_img_copy(t_copyimg data);



#endif
