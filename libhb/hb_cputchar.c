/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hb_cputchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:02:22 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/23 16:02:25 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhb.h"

int	hb_cputchar(char c)
{
	return (write(1, &c, 1));
}

int	hb_cputchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
