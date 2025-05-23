/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hb_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:46:30 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/23 11:24:41 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhb.h"

void	*hb_memset(void *arr, int c, size_t l)
{
	unsigned char	*p;

	p = (unsigned char *)arr;
	while (l--)
		*(p++) = (unsigned char)c;
	return (arr);
}
