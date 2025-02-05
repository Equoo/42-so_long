/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:02:23 by dderny            #+#    #+#             */
/*   Updated: 2025/02/05 07:29:48 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm256.h"

t_m256i	__attribute__((__always_inline__))	ft_mm256_sub(t_m256i __a,
		t_m256i __b)
{
	return ((t_m256i)((t_v8si)__a - (t_v8si)__b));
}

t_m256i	__attribute__((__always_inline__))	ft_mm256_add(t_m256i __a,
		t_m256i __b)
{
	return ((t_m256i)((t_v8si)__a + (t_v8si)__b));
}

t_m256i	__attribute__((__always_inline__))	ft_mm256_mullo(t_m256i __a,
		t_m256i __b)
{
	return ((t_m256i)((t_v8si)__a * (t_v8si)__b));
}

t_m256i	__attribute__((__always_inline__))	ft_mm256_div(t_m256i __a,
		t_m256i __b)
{
	return ((t_m256i)((t_v8si)__a / (t_v8si)__b));
}
