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

int	updatenv(t_env **env, char *var, char *value, int exp)
{
	t_env	*tmp;

	if (getvalue(*env, var) != NULL)
		editvar(env, var, value);
	else
	{
		tmp = envnew(var, value, exp);
		envadd_back(env, tmp);
	}
	return (0);
}

int	ft_export(char **args, t_env **env)
{
	char	*var;
	char	*value;
	int		i;

	i = 1;
	if (!args[1])
		printenv(*env, 1);
	if (expars(args))
		return (1);
	while (args[i])
	{
		if (!beforequ(args[i]))
			updatenv(env, args[i], "\0", 1);
		else
		{
			var = hb_substr(args[i], 0, beforequ(args[i]));
			value = args[i] + beforequ(args[i]) + 1;
			updatenv(env, var, value, 0);
		}
		i++;
	}
	return (0);
}
