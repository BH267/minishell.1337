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

#include "binsutils.h"
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

int	setvalue(char **env, char *var, char *newv)
{
	int	i;
	char	*tmp;

	i = 0;
	if (!newv)
		return (0);
	while (env[i])
	{
		tmp = hb_strdup(env[i]);
		tmp[beforequ(tmp)] = '\0';
		if (hb_strcmp(tmp, var) == 0)
		{
			env[i] = hb_strjoin(tmp, "=");
			env[i] = hb_strjoin(env[i], newv);
			return (0);
		}
		i++;
	}
	return (1);
}

char	*getenvalue(char **env, char *var)
{
	int	i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = hb_strdup(env[i]);
		tmp[beforequ(tmp)] = '\0';
		if (hb_strcmp(tmp, var) == 0)
			return (env[i] + beforequ(env[i]) + 1);
		i++;
	}
	return (NULL);
}
