/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:02:40 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/20 21:04:23 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	eeditvar(t_env **env, char *var, char *newv, int exp)
{
	t_env	*tmp;

	tmp = *env;
	if (!newv)
		return (0);
	while (tmp)
	{
		if (hb_strcmp(tmp->var, var) == 0)
		{
			tmp->value = newv;
			tmp->exp = exp;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	editvar(t_env **env, char *var, char *newv)
{
	t_env	*tmp;

	tmp = *env;
	if (!newv)
		return (0);
	while (tmp)
	{
		if (hb_strcmp(tmp->var, var) == 0)
		{
			tmp->value = newv;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
