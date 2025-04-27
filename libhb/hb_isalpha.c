/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hb_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:05:11 by habenydi          #+#    #+#             */
/*   Updated: 2024/11/04 12:35:36 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhb.h"

int	hb_isalpha(int c)
{
	return (('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z'));
}

int	hb_isalphastr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!hb_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}
