/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:53:19 by habenydi          #+#    #+#             */
/*   Updated: 2025/03/11 16:09:25 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	**getpaths(char *cmd, char **env)
{
	char	**paths;
	char	*tmp;
	int	i;

	(void)cmd;
	paths = hb_split(hb_mtrfchr(env, "PATH="), ':');
	tmp = paths[0];
	paths[0] = hb_substr(paths[0], 5, hb_strlen(paths[0]));
	free(tmp);
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = hb_strjoin(paths[i], "/");
		free(tmp);
		tmp = paths[i];
		paths[i] = hb_strjoin(paths[i], cmd);
		free(tmp);
		i++;
	}
	return (paths);
}

char	*getpath(char *cmd, char **env)
{
	char	**paths;
	int	i;

	paths = getpaths(cmd, env);
	i = 0;
	while (paths[i])
	{
		if (!access(paths[i], X_OK))
			return (paths[i]);
      		i++;
	}
	return (NULL);
}
