/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm256.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:12:45 by dderny            #+#    #+#             */
/*   Updated: 2025/01/17 18:01:11 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MM256_H
# define MM256_H
# include <immintrin.h>

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_slli(__m256i __a, int __n)
{
	return ((__m256i)((__v8si)__a << __n));
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_srli(__m256i __a, int __n)
{
	return ((__m256i)((__v8si)__a >> __n));
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_div(__m256i __a, __m256i __b)
{
	return (__m256i)((__v8si)__a / (__v8si)__b);
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_mullo(__m256i __a, __m256i __b)
{
	return (__m256i)((__v8si)__a * (__v8si)__b);
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_add(__m256i __a, __m256i __b)
{
	return ((__m256i)((__v8si)__a + (__v8si)__b));
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_sub(__m256i __a, __m256i __b)
{
	return ((__m256i)((__v8si)__a - (__v8si)__b));
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_and(__m256i __a, __m256i __b)
{
	return (__a & __b);
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_or(__m256i __a, __m256i __b)
{
	return (__a | __b);
}

static __inline __m256i __attribute__((__always_inline__,
		__nodebug__))	ft_mm256_set1(int __i)
{
	return ((__m256i)(__v8si){__i, __i, __i, __i, __i, __i, __i, __i});
}

#endif