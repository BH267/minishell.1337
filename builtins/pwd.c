/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:38:32 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/17 14:20:56 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"

int	pwd(t_env *env)
{
	printf("%s\n", getvalue(env, "PWD"));
	return (0);
}
	/*char	cwd[1024];

	if (!getcwd(cwd, 1024))
	{
		hb_printerr("%s\n", strerror(errno));
		return (1);
	}*/
