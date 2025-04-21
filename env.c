/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:40:27 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/21 19:41:00 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

t_env	*envtolist(char **env)
{
	int	i;
	t_env	*envi;
	t_env	*tmp;
	char	*var;

	i = 0;
	envi = NULL;
	tmp = NULL;
	while (env[i])
	{
		var = hb_substr(env[i], 0, beforequ(env[i]));
		tmp = envnew(var, getenv(var));
		envadd_back(&envi, tmp);
		i++;
	}
	return (envi);
}

void	printenv(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->var, env->value);
		env = env->next;
	}
}

char	*getvalue(t_env *env, char *var)
{
	while (env)
	{
		if (hb_strcmp(env->var, var) == 0)
			return (hb_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

t_env	*asigneavalue(t_env *env, char *var, char *nvalue)
{
	while (env)
	{
		if (hb_strcmp(env->var, var) == 0)
		{
			env->value = hb_strdup(nvalue);
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}
