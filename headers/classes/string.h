/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:26:52 by dderny            #+#    #+#             */
/*   Updated: 2025/01/26 23:06:54 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H
# include <libft.h>

typedef struct s_string {
	t_list  *str;
	t_list	*last;
	int		len;

	t_string	*(*copy)(t_string *self);
	char		(*get)(t_string *self);
	t_string	*(*add)(t_string *self, t_string *b);
	t_string	*(*join)(t_string *self, t_string *b);
	t_string	*(*joinstr)(t_string *self, char *b);
	void		(*strdel)(t_string *self);
	void		(*del)(t_string *self);
}   t_string;


t_string 	*string_add(t_string *self, t_string *b);
t_string 	*string_join(t_string *self, t_string *b);
t_string 	*string_joinstr(t_string *self, char *b);
t_string 	*string_copy(t_string *self);
void	 	string_del(t_string *self);
t_string	*ft_string(char *str);

#endif