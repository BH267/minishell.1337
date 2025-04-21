/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:47:37 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/19 13:49:36 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	beforequ(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

char	*getfromenv(char **env, char *var)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (var[i] == '$')
		i++;
	while (env[j])
	{

		if (hb_strncmp(env[j] , var + i, beforequ(env[j])) == 0)
			return (env[j] + beforequ(env[j]) + 1);
		j++;
	}
	return (NULL);
}

int	varexp(t_ms *ms)
{
	int	i;

	i = 0;
	if (!ms->args[0])
		return (1);
	while (ms->args[i])
	{
		if (hb_strncmp(ms->args[i], "$", 1) == 0)
		{
			if (hb_strcmp(ms->args[i], "$?") == 0)
			{
				i++;
				continue ;
			}
			ms->args[i] = getfromenv(ms->env, ms->args[i]);
		}
		i++;
	}
	return (1);
}
