/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:56:33 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/19 11:58:27 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	signal_for_herdoc(int sig)
{
	(void)sig;
	close(0);
}

void	sighand(int sig)
{
	if (sig == SIGINT)
	{
		write (1, "\n", 1);
		*(estate()) = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	signals(int mode)
{
	if (mode == NORMAL)
	{
		signal(SIGINT, sighand);
		signal(SIGQUIT, SIG_IGN);
		return (1);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		return (1);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, signal_for_herdoc);
		signal(SIGQUIT, SIG_DFL);
		return (1);
	}
	return (0);
}
