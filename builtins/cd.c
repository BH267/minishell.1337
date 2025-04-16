/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:27:52 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/16 11:05:32 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bins.h"
#include <unistd.h>

int	cd(char *cmd)
{
	char	**args;
	char	*path;

	args = hb_split(cmd, ' ');
	if (!args[2] || !args || !*args)
	{
		strerror(errno);
		return (1);
	}
	if (!args[1])
		path = getenv("HOME");
	else if (hb_strcmp(args[1], "-") == 0)
			path = getenv("OLDPWD");
	else
		path = args[1];
	chdir(path);
	return (0);
}
