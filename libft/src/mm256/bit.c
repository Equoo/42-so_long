/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:02:23 by dderny            #+#    #+#             */
/*   Updated: 2025/02/05 07:29:52 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm256.h"

t_m256i	__attribute__((__always_inline__))	ft_mm256_slli(t_m256i __a, int __n)
{
	return ((t_m256i)((t_v8si)__a << __n));
}

t_m256i	__attribute__((__always_inline__))	ft_mm256_srli(t_m256i __a, int __n)
{
	return ((t_m256i)((t_v8si)__a >> __n));
}

t_m256i	__attribute__((__always_inline__))	ft_mm256_and(t_m256i __a,
		t_m256i __b)
{
	return (__a & __b);
}

t_m256i	__attribute__((__always_inline__))	ft_mm256_or(t_m256i __a,
		t_m256i __b)
{
	return (__a | __b);
}

t_m256i	__attribute__((__always_inline__))	ft_mm256_set1(int __i)
{
	return ((t_m256i)(t_v8si){__i, __i, __i, __i, __i, __i, __i, __i});
}
