/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm256.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:12:45 by dderny            #+#    #+#             */
/*   Updated: 2025/02/05 07:29:48 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MM256_H
# define MM256_H
// created from <immintrin.h>

typedef __attribute((vector_size(32))) long long	t_m256i;
typedef __attribute((vector_size(32))) int			t_v8si;
typedef __attribute((vector_size(32))) char			t_v4si;
typedef __attribute((vector_size(32))) long long	t_m256i_u;
typedef __attribute((vector_size(32))) float		t_m256_u;
typedef __attribute((vector_size(32))) double		t_m256d_u;
typedef __attribute((vector_size(32))) double		t_m256d;
typedef __attribute((vector_size(32))) short		t_m256bh;
typedef __attribute((vector_size(32))) float		t_m256;

extern t_m256i	ft_mm256_slli(t_m256i __a, int __n)
				__attribute__((__always_inline__));

extern t_m256i	ft_mm256_srli(t_m256i __a, int __n)
				__attribute__((__always_inline__));

extern t_m256i	ft_mm256_div(t_m256i __a, t_m256i __b)
				__attribute__((__always_inline__));

extern t_m256i	ft_mm256_mullo(t_m256i __a, t_m256i __b)
				__attribute__((__always_inline__));

extern t_m256i	ft_mm256_add(t_m256i __a, t_m256i __b)
				__attribute__((__always_inline__));

extern t_m256i	ft_mm256_sub(t_m256i __a, t_m256i __b)
				__attribute__((__always_inline__));

extern t_m256i	ft_mm256_and(t_m256i __a, t_m256i __b)
				__attribute__((__always_inline__));

extern t_m256i	ft_mm256_or(t_m256i __a, t_m256i __b)
				__attribute__((__always_inline__));

extern t_m256i	ft_mm256_set1(int __i);

#endif