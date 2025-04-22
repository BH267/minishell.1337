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

void	updatepwd(t_env **env, char *var)
{
	char	cwd[1024];

	if (!getcwd(cwd, 1024))
	{
		printf("%s\n", strerror(errno));
		return ;
	}
	editvar(env, var, cwd);
}

int	cd(char **args, t_ms *ms)
{
	char	*path;
	char	*tmp;

	if (!args[1])
		path = getenv("HOME");
	else
		path = args[1];
	tmp = getvalue(ms->env, "OLDPWD");
	updatepwd(&(ms->env), "OLDPWD");
	if (chdir(path) == -1)
	{
		editvar(&(ms->env), "OLDPWD", tmp);
		return (printf("%s\n", strerror(errno)), 1);
	}
	updatepwd(&(ms->env), "PWD");
	return (0);
}
