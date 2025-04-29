/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:34:55 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/29 09:30:38 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	redirect(t_ms *ms)
{
	t_redirect	*rdct;
	int			fd;
	
	rdct = ms->rdctl;
	while (rdct)
	{
		if (rdct->type == 2)
		{
			fd = open(rdct->value, O_RDONLY);
			if (fd == -1)
				return (hb_printerr("open faild, try again\n"), 1);
			dup2(fd, 0);
			close(fd);
		}
		if (rdct->type == 3)
		{
			fd = open(rdct->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (hb_printerr("open faild, try again\n"), 1);
			dup2(fd, 1);
			close(fd);
		}
		rdct = rdct->next;
	}
	return (0);
}
