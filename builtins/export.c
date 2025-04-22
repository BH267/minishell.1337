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

int	ft_export(char **args, t_env **env)
{
	t_env	*tmp;
	char	*var;
	int	i;

	i = 1;
	while (args[i])
	{
		var = hb_substr(args[i], 0, beforequ(args[i]));
		tmp = envnew(var, args[i] + beforequ(args[i]) + 1);
		envadd_back(env, tmp);
		i++;
	}
	return (0);
}
