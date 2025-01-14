
#ifndef ELEMENT_H
# define ELEMENT_H
# include "texture.h"
# include "vector2d.h"

typedef struct s_element
{
	t_texture	*texture;
	t_vector2d	*pos;
	int			z;

	void		(*draw)(t_element *self);
	void		(*del)(t_element *self);
}				t_element;

t_element		*ft_element(void);

void			element_del(void);

#endif