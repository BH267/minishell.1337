/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:40:27 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/22 14:46:44 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

t_env	*envtolist(char **env)
{
	int		i;
	t_env	*envi;
	t_env	*tmp;
	char	*var;

	if (!env || !*env)
		return (NULL);
	i = 0;
	envi = NULL;
	tmp = NULL;
	while (env[i])
	{
		var = hb_substr(env[i], 0, beforequ(env[i]));
		tmp = envnew(var, getenv(var), 0);
		envadd_back(&envi, tmp);
		i++;
	}
	return (envi);
}

void	printenv(t_env *env, int exp)
{
	while (env)
	{
		if (env->exp == 0 && exp == 0)
			printf("%s=%s\n", env->var, env->value);
		else if (exp == 1)
			printf("declare -x %s=\"%s\"\n", env->var, env->value);
		env = env->next;
	}
}

char	*getvalue(t_env *env, char *var)
{
	while (env)
	{
		if (hb_strcmp(env->var, var) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
/*
t_env	*asigneavalue(t_env **env, char *var, char *nvalue)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (hb_strcmp(tmp->var, var) == 0)
		{
			tmp->value = nvalue;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}*/
