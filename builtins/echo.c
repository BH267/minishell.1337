/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 09:27:40 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/18 09:37:33 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	echo(char **args, t_ms *ms)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (hb_strcmp(args[i], "-n") == 0)
	{
		i++;
		nl = 0;
	}
	while (args[i])
	{
		if (hb_strcmp(args[i], "$?") == 0)
		{
			printf("%d", ms->e);
			i++;
			continue ;
		}
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}
