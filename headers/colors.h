/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:02:00 by dderny            #+#    #+#             */
/*   Updated: 2025/02/05 08:50:51 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H
# include "mm256.h"

typedef struct s_m256i_rgba
{
	__m256i_u	r;
	__m256i_u	g;
	__m256i_u	b;
	__m256i_u	a;
}				t_m256i_rgba;

typedef struct s_rgba
{
	int			r;
	int			g;
	int			b;
	int			a;
}				t_rgba;

t_m256i_rgba	m256_split_channels(__m256i_u rgba, int alpha);
__m256i_u		m256_combine_channels(t_m256i_rgba chans);
t_m256i_rgba	m256_blend_by_alpha(t_m256i_rgba dst, t_m256i_rgba src);

t_rgba	split_channels(int rgba, int alpha);
int		combine_channels(t_rgba chans);
t_rgba	blend_by_alpha(t_rgba dst, t_rgba src);

#endif
