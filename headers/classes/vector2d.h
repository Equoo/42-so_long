/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:40:00 by dderny            #+#    #+#             */
/*   Updated: 2025/01/09 10:13:35 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR2D_H
# define VECTOR2D_H

typedef struct s_vector2d
{
    float x;
    float y;
    
    void        (*add)(struct s_vector2d *self, struct s_vector2d *other);
    void        (*sub)(struct s_vector2d *self, struct s_vector2d *other);
    void        (*scale)(struct s_vector2d *self, float factor);
    float       (*dot)(struct s_vector2d *self, struct s_vector2d *other);
	void        (*normalize)(struct s_vector2d *self);
    float       (*length)(struct s_vector2d *self);
}               t_vector2d;

void           vector2d_add(t_vector2d *self, t_vector2d *other);
void           vector2d_sub(t_vector2d *self, t_vector2d *other);
void           vector2d_scale(t_vector2d *self, float factor);
float          vector2d_dot(t_vector2d *self, t_vector2d *other);
void           vector2d_normalize(t_vector2d *self);
float          vector2d_length(t_vector2d *self);

void           vector2d_del(t_vector2d *self);
t_vector2d     *ft_vector2d(float x, float y);

#endif