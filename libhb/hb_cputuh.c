/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hb_cputuh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:03:47 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/23 16:03:51 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhb.h"

int	hb_cputhexa(unsigned long n, char x)
{
	char	*lwbase;
	char	*upbase;
	int		cont;

	cont = 0;
	lwbase = "0123456789abcdef";
	upbase = "0123456789ABCDEF";
	if (n < 16)
	{
		if (x == 'x')
			cont += hb_cputchar(*(n + lwbase));
		if (x == 'X')
			cont += hb_cputchar(*(n + upbase));
	}
	if (n >= 16)
	{
		cont += hb_cputhexa(n / 16, x);
		cont += hb_cputhexa(n % 16, x);
	}
	return (cont);
}

int	hb_cputunbr(unsigned int n)
{
	int	cont;

	cont = 0;
	if (n < 10)
		cont += hb_cputchar('0' + n);
	else
	{
		cont += hb_cputunbr(n / 10);
		cont += hb_cputunbr(n % 10);
	}
	return (cont);
}

int	hb_cputhexa_fd(unsigned long n, char x, int fd)
{
	char	*lwbase;
	char	*upbase;
	int		cont;

	cont = 0;
	lwbase = "0123456789abcdef";
	upbase = "0123456789ABCDEF";
	if (n < 16)
	{
		if (x == 'x')
			cont += hb_cputchar_fd(*(n + lwbase), fd);
		if (x == 'X')
			cont += hb_cputchar_fd(*(n + upbase), fd);
	}
	if (n >= 16)
	{
		cont += hb_cputhexa_fd(n / 16, x, fd);
		cont += hb_cputhexa_fd(n % 16, x, fd);
	}
	return (cont);
}

int	hb_cputunbr_fd(unsigned int n, int fd)
{
	int	cont;

	cont = 0;
	if (n < 10)
		cont += hb_cputchar_fd('0' + n, fd);
	else
	{
		cont += hb_cputunbr_fd(n / 10, fd);
		cont += hb_cputunbr_fd(n % 10, fd);
	}
	return (cont);
}
