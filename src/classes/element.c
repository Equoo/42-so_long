#include "classes/element.h"
#include <libft.h>

static void	element_draw(t_element *self)
{
}

t_element	*ft_element(void)
{
	t_element *element;

	element = ft_calloc(1, sizeof(t_element));
	element->draw = &element_draw;
	return (element);
}