/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:42:14 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/20 14:44:15 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	expars(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!hb_isalpha(str[i][0])
			&& str[i][0] != '_' && str[i][0] != '?')
		{
			printf("export: `%s': not a valid identifier\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	updatenv(t_env **env, char *var, char *value)
{
	t_env	*tmp;
	
	if (getvalue(*env, var) != NULL)
		editvar(env, var, value);
	else
	{
		tmp = envnew(var, value);
		envadd_back(env, tmp);
	}
	return (0);
}

int	ft_export(char **args, t_env **env)
{
	char	*var;
	char	*value;
	int	i;

	i = 1;
	if (expars(args))
		return (1);
	while (args[i])
	{
		if (!beforequ(args[i]))
			return (0);
		var = hb_substr(args[i], 0, beforequ(args[i]));
		value = args[i] + beforequ(args[i]) + 1;
		//if (!*value)
		//	value = "\0";
		updatenv(env, var, value);
		i++;
	}
	return (0);
}
