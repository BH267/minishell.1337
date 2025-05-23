/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbins.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:18:22 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/20 00:40:24 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	builtins(char *cmd, t_ms *ms)
{
	if (redirect(ms))
		return (setes(1));
	if (hb_strcmp(cmd, "cd") == 0)
		ms->e = cd(ms->args, ms);
	else if (hb_strcmp(cmd, "echo") == 0)
		ms->e = echo(ms->args);
	else if (hb_strcmp(cmd, "env") == 0)
		ms->e = envi(ms->env);
	else if (hb_strcmp(cmd, "pwd") == 0)
		ms->e = pwd();
	else if (hb_strcmp(cmd, "export") == 0)
		ms->e = ft_export(ms->args, &(ms->env));
	else if (hb_strcmp(cmd, "unset") == 0)
		ms->e = unset(&(ms->env), ms->args);
	else if (hb_strcmp(cmd, "exit") == 0)
		ms->e = bexit(ms->args, ms->e);
	else
	{
		b2o(0);
		return (99);
	}
	b2o(0);
	return (setes(ms->e));
}
