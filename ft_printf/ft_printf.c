/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:36:09 by ybouanan          #+#    #+#             */
/*   Updated: 2024/11/19 15:55:14 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putcharind(char c, int *index)
{
	*index += 1;
	return (write(1, &c, 1));
}

static int	ft_putcharformat(char c)
{
	return (write(1, &c, 1));
}

static int	ft_putchar(char c, const char *str, int *index)
{
	if (str[*index] == '%')
	{
		*index += 1;
		return (0);
	}
	*index += 1;
	(void)str;
	(void)index;
	return (write(1, &c, 1));
}

static int	ft_format(const char *mstr, int *index, va_list args)
{
	int	count;

	count = 0;
	if (mstr[*index + 1] == 'd' || mstr[*index + 1] == 'i')
		ft_putbase(&count, 0, va_arg(args, int), 'd');
	else if (mstr[*index + 1] == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (mstr[*index + 1] == 'c')
		count += ft_putcharformat(va_arg(args, int));
	else if (mstr[*index + 1] == 'u')
		ft_putbase(&count, va_arg(args, unsigned int), 0, 'u');
	else if (mstr[*index + 1] == 'x' || mstr[*index + 1] == 'X')
		ft_putbase(&count, va_arg(args, unsigned int), 0, mstr[*index + 1]);
	else if (mstr[*index + 1] == '%')
		count += write(1, "%", 1);
	else if (mstr[*index + 1] == 'p')
	{
		count += ft_putstr("0x");
		ft_putbase(&count, va_arg(args, unsigned long), 0, 'x');
	}
	if (count == 0 && (mstr[*index] == '%') && (mstr[*index + 1] != 's'))
		return (ft_putchar(mstr[*index], mstr, index));
	*index += 2;
	return (count);
}

int	ft_printf(const char *mstr, ...)
{
	va_list	args;
	int		count;
	int		index;
	int		x;

	index = 0;
	count = 0;
	if (write(1, 0, 0) == -1)
		return (-1);
	va_start(args, mstr);
	while (mstr[index])
	{
		x = 0;
		if (mstr[index] == '%')
		{
			x = ft_format(mstr, &index, args);
			if (x < 0)
				return (va_end(args), -1);
			count += x;
		}
		else
			count += ft_putcharind(mstr[index], &index);
	}
	va_end(args);
	return (count);
}
