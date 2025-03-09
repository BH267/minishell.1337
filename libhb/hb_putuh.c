/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hb_putuh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:36:25 by habenydi          #+#    #+#             */
/*   Updated: 2024/11/15 17:12:04 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhb.h"

void	hb_puthexa(unsigned long n, char x)
{
	char	*lwbase;
	char	*upbase;

	lwbase = "0123456789abcdef";
	upbase = "0123456789ABCDEF";
	if (n < 16)
	{
		if (x == 'x')
			hb_putchar(*(n + lwbase));
		if (x == 'X')
			hb_putchar(*(n + upbase));
	}
	if (n >= 16)
	{
		hb_puthexa(n / 16, x);
		hb_puthexa(n % 16, x);
	}
}

void	hb_putunbr(unsigned int n)
{
	if (n < 10)
		hb_putchar('0' + n);
	else
	{
		hb_putunbr(n / 10);
		hb_putunbr(n % 10);
	}
}
