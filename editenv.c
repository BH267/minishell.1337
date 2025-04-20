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

int	editvar(char **env, char *var, char *newv)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (hb_strncmp(env[i], var, beforequ(env[i])) == 0)
		{
			env[i][beforequ(env[i]) + 1] = '\0';
			env[i] = hb_strjoin(env[i], newv);
		}
		i++;
	}
	return (0);
}
