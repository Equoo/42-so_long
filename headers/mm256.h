/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm256.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:12:45 by dderny            #+#    #+#             */
/*   Updated: 2025/01/19 01:13:03 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MM256_H
# define MM256_H
# include <immintrin.h>

extern __m256i /* __attribute__((__always_inline__)) */	ft_mm256_slli(__m256i __a, int __n);

extern __m256i /* __attribute__((__always_inline__)) */	ft_mm256_srli(__m256i __a, int __n);

extern __m256i /* __attribute__((__always_inline__)) */	ft_mm256_div(__m256i __a, __m256i __b);

extern __m256i /* __attribute__((__always_inline__)) */	ft_mm256_mullo(__m256i __a, __m256i __b);

extern __m256i /* __attribute__((__always_inline__)) */	ft_mm256_add(__m256i __a, __m256i __b);

extern __m256i /* __attribute__((__always_inline__)) */	ft_mm256_sub(__m256i __a, __m256i __b);

extern __m256i /* __attribute__((__always_inline__)) */	ft_mm256_and(__m256i __a, __m256i __b);

extern __m256i /* __attribute__((__always_inline__)) */	ft_mm256_or(__m256i __a, __m256i __b);

extern __m256i /* __attribute__((__always_inline__)) */	ft_mm256_set1(int __i);

#endif