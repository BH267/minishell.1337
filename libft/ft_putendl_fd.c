/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:07:58 by ybouanan          #+#    #+#             */
/*   Updated: 2024/11/09 17:10:07 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, (int)ft_strlen(s));
	write(fd, "\n", 1);
}
