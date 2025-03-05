/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:15:51 by ybouanan          #+#    #+#             */
/*   Updated: 2025/02/16 21:53:04 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strlen(const char *c)
{
	const char	*tmp;

	tmp = c;
	while (*tmp)
		tmp++;
	return (tmp - c);
}
