/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hb_printerr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:58:37 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/26 10:25:16 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhb.h"

int	hb_format(char sp, va_list list)
{
	int	cont;

	cont = 0;
	if (sp == 's')
		cont = hb_cputstr_fd(va_arg(list, char *), 2);
	else if (sp == 'd' || sp == 'i')
		cont = hb_cputnbr_fd(va_arg(list, int), 2);
	else if (sp == 'c')
		cont = hb_cputchar_fd(va_arg(list, int), 2);
	else if (sp == '%')
		cont = hb_cputchar_fd('%', 2);
	else if (sp == 'x' || sp == 'X')
		cont = hb_cputhexa_fd(va_arg(list, unsigned int), sp, 2);
	else if (sp == 'p')
	{
		cont = hb_cputstr_fd("0x", 2);
		cont += hb_cputhexa_fd((va_arg(list, unsigned long)), 'x', 2);
	}
	else if (sp == 'u')
		cont = hb_cputunbr_fd(va_arg(list, unsigned int), 2);
	else
		cont += hb_cputchar_fd(sp, 2);
	return (cont);
}

int	hb_printerr(const char *f, ...)
{
	va_list	list;
	char	*sp;
	int		cont;

	if (!f || write(2, 0, 0) == -1)
		return (-1);
	va_start(list, f);
	cont = 0;
	sp = (char *) f;
	while (*sp)
	{
		if (*sp == '%')
		{
			if (*(sp + 1) == '\0')
				return (cont);
			cont += hb_format(*(++sp), list);
		}
		else
			cont += hb_cputchar_fd(*sp, 2);
		sp++;
	}
	va_end(list);
	return (cont);
}
