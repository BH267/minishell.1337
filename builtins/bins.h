/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bins.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:11:09 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/16 11:14:40 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINS_H
# define BINS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include "../libhb/libhb.h"
# include "../binsutils.h"

typedef struct s_stackofvariables
{
	t_env	*env;
	char	*cmd;
	char	**args;
	int		e;
}	t_ms;

int		pwd(void);
int		envi(t_env *env);
int		echo(char **args);
int		bexit(char **args, int	rv);
void	unset(t_env **env, char **args);
int		cd(char **args, t_ms *ms);
int		ft_export(char **args, t_env **evn);

#endif
