/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hb_putmtr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:12:46 by habenydi          #+#    #+#             */
/*   Updated: 2025/03/09 12:12:57 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhb.h"

void	hb_putmtr(char **mtr)
{
	size_t	i;

	if (!mtr)
		return ;
	i = 0;
	while (mtr[i])
	{
		hb_putstr(mtr[i++]);
		hb_putchar('\n');
	}
}

void	hb_putmtr_fd(char **mtr, int fd)
{
	size_t	i;

	if (!mtr)
		return ;
	i = 0;
	while (mtr[i])
	{
		hb_putstr_fd(mtr[i++], fd);
		hb_putchar('\n');
	}
}
