/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:12:49 by ybouanan          #+#    #+#             */
/*   Updated: 2024/11/17 22:27:12 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex(unsigned long n, char *base, unsigned long lent,
		int *count)
{
	char	*hex;

	hex = base;
	if (n >= lent)
		ft_puthex(n / lent, hex, lent, count);
	*count += write(1, &hex[n % lent], 1);
}

static int	ft_putchar_fd(char c)
{
	return (write(1, &c, 1));
}

static void	ft_putnbr(int n, int *count)
{
	if (n == -2147483648)
	{
		*count += write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		*count += ft_putchar_fd('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, count);
	}
	*count += ft_putchar_fd((n % 10) + '0');
}

void	ft_putbase(int *count, unsigned long n, int number, char base)
{
	if (base == 'x')
		ft_puthex(n, "0123456789abcdef", 16, count);
	else if (base == 'X')
		ft_puthex(n, "0123456789ABCDEF", 16, count);
	else if (base == 'd')
		ft_putnbr(number, count);
	else if (base == 'u')
		ft_puthex(n, "0123456789", 10, count);
	(void)n;
	(void)number;
}
