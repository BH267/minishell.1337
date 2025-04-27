/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:35:31 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/22 15:44:58 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	unset(t_env **env, char **args)
{
	t_env	*tmp;
	int		i;

	i = 1;
	while (args[i])
	{
		tmp = *env;
		while (tmp)
		{
			if (tmp->next && hb_strcmp(tmp->next->var, args[i]) == 0)
			{
				tmp->next = tmp->next->next;
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
