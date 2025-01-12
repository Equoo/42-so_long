#include <libft.h>
#include "classes/element.h"

static void element_draw(t_element *self)
{

}

t_element   *ft_element()
{
    t_element *element;

    element = ft_calloc(1, sizeof(t_element));
    element->draw = &element_draw;
    return (element);
}