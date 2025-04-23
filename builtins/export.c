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

int	expars(char *str)
{
	if (!hb_isalpha(str[0]) && str[0] != '_' && str[0] != '?')
		return (1);
	return (0);
}

int	ft_export(char **args, t_env **env)
{
	t_env	*tmp;
	char	*var;
	char	*value;
	int	i;

	i = 1;
	while (args[i])
	{
		expars(args[i]);
		var = hb_substr(args[i], 0, beforequ(args[i]));
		value = args[i] + beforequ(args[i]) + 1;
		if (!*value)
			value = "\0";
		if (getvalue(*env, var) != NULL)
			editvar(env, var, value);
		else
		{
			tmp = envnew(var, value);
			envadd_back(env, tmp);
		}
		i++;
	}
	return (0);
}
