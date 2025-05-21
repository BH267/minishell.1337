/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:47:37 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/21 12:51:17 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	beforequ(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
		if (!str[i])
			return (0);
	}
	return (i);
}

char	*getfromenv(t_env *env, char *var)
{
	int	i;

	i = 0;
	if (var && var[i] == '$')
		i++;
	while (env)
	{
		if (hb_strcmp(env->var, var + i) == 0)
			return (env->value);
		env = env->next;
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
				ms->args[i] = hb_itoa(ms->e);
			}
			else
			{
				if (hb_strcmp(ms->args[i], "$") != 0)
				{
					ms->args[i] = getfromenv(ms->env, ms->args[i]);
				}
			}
		}
		i++;
	}
	return (1);
}
