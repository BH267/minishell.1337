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

int	ifnl(char **args, int *i, int *j)
{
	int	nl;

	nl = 1;
	while (args[*i] && args[*i][*j]
		&& args[*i][0] == '-' && args[*i][*j] == 'n')
	{
		(*j)++;
		if (!args[*i][*j])
		{
			nl = 0;
			(*i)++;
		}
	}
	return (nl);
}

int	echo(char **args)
{
	int	i;
	int	j;
	int	nl;

	i = 1;
	j = 1;
	nl = ifnl(args, &i, &j);
	while (args[i])
	{
		if (printf("%s", args[i]) == -1)
			return (hb_printerr("%s\n", strerror(errno)), errno);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}
