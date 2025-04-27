/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:08:15 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/26 09:49:03 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	firstchar(char *arg)
{
	if (!hb_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	return (0);
}

int	validvar(char *arg)
{
	int	i;

	i = 1;
	while (arg[i] != '=' && arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (0);
		if (!hb_isalnum(arg[i]) && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	expars(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (firstchar(str[i]) || validvar(str[i]))
		{
			hb_printerr("export: `%s': not a valid identifier\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
