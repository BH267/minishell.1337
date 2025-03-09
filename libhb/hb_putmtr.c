/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hb_putmtr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 10:47:44 by habenydi          #+#    #+#             */
/*   Updated: 2025/03/09 10:49:32 by habenydi         ###   ########.fr       */
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
		hb_putstr(mtr[i]);
}

void	hb_putmtr_fd(char **mtr, int fd)
{
	size_t	i;

	if (!mtr)
		return ;
	i = 0;
	while (mtr[i])
		hb_putstr_fd(mtr[i], fd);
}
