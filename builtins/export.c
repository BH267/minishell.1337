/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:42:14 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/12 13:24:13 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	updatenv(t_env **env, char *var, char *value, int exp)
{
	t_env	*tmp;

	if (getvalue(*env, var) != NULL)
		eeditvar(env, var, value, exp);
	else
	{
		tmp = envnew(var, value, exp);
		envadd_back(env, tmp);
	}
	return (0);
}

void	assignevalue(char *arg, t_env **env)
{
	char	*var;
	char	*value;
	char	*tmp;
	int		equ;

	equ = beforequ(arg);
	if (arg[equ - 1] == '+')
	{
		var = hb_substr(arg, 0, equ - 1);
		value = getvalue(*env, var);
		if (!value)
			value = "\0";
		tmp = arg + equ + 1;
		value = hb_strjoin(value, tmp);
		updatenv(env, var, value, 0);
	}
	else
	{
		var = hb_substr(arg, 0, equ);
		value = arg + equ + 1;
		updatenv(env, var, value, 0);
	}
}

int	ft_export(char **args, t_env **env)
{
	int	i;

	i = 1;
	if (!args[1])
		printenv(*env, 1);
	if (expars(args))
		return (1);
	while (args[i])
	{
		if (!beforequ(args[i]))
			updatenv(env, args[i], NULL, 1);
		else
			assignevalue(args[i], env);
		i++;
	}
	return (0);
}
