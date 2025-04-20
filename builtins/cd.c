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

int	cd(char **args)
{
	char	*path;

	if (hb_mtrlen(args) > 2 && hb_strcmp(args[1], "--") != 0)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (hb_strcmp(args[1], "--") == 0)
	{
			args[1] = args[2];
		if (hb_mtrlen(args) > 3)
			return (printf("cd: too many arguments\n"), 1);
	}
	if (!args[1])
		path = getenv("HOME");
	else if (hb_strcmp(args[1], "-") == 0)
			path = getenv("OLDPWD");
	else
		path = args[1];
	if (chdir(path) == -1)
		return (printf("%s\n", strerror(errno)), 1);
	return (0);
}
/*
int	cd(char **args)
{
	char	*path;

	if (!args[0])
	{
		strerror(errno);
		return (1);
	}
	if (!args[1])
		path = getenv("HOME");
	if (args[2])
		return (perror("cd: too many arguments\n"), 1);
	else if (hb_strcmp(args[1], "-") == 0)
			path = getenv("OLDPWD");
	else
		path = args[1];
	chdir(path);
	return (0);
}*/
