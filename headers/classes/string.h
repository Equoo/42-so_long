/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:26:52 by dderny            #+#    #+#             */
/*   Updated: 2025/01/05 21:39:16 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H
# include <libft.h>

typedef struct s_string {
	t_list  *str;

	t_string	*(*copy)(t_string *self);
	char		(*get)(t_string *self);
	t_string	*(*add)(t_string *self, t_string *b);
	t_string	*(*join)(t_string *self, t_string *b);
	size_t		(*len)(t_string *self);
	void		(*strdel)(t_string *self);
	void		(*del)(t_string *self);
}   t_string;


t_string 	*string_add(t_string *self, t_string *b);
t_string 	*string_join(t_string *self, t_string *b);
t_string 	*string_copy(t_string *self);
size_t	 	*string_len(t_string *self);
void	 	string_del(t_string *self);
t_string	*ft_string(char *str);

#endif