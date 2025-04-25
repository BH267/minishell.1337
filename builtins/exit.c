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

int	bexit(char **args, int rv)
{
	unsigned char	e;

	printf("exit\n");
	if (!args[1])
		ft_exit(rv);
	if (args[2])
	{
		printf("exit: too many arguments");
		return (1);
	}
	e = hb_atoi(args[1]);
	ft_exit(e);
	return (e);
}
