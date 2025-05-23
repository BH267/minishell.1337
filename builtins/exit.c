/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:37:46 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/25 16:46:13 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"
#include "../ms.h"

int	bexit(char **args, int rv)
{
	unsigned char	e;

	hb_printerr("exit\n");
	if (!args[1])
		ft_exit(*(estate()));
	if (hb_isalphastr(args[1]))
	{
		hb_printerr("exit: %s: numeric argument required\n", args[1]);
		ft_exit(2);
	}
	if (args[2])
	{
		hb_printerr("exit: too many arguments\n");
		return (1);
	}
	e = hb_atoi(args[1]);
	ft_exit(e);
	return (e);
}
