/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:18:26 by ybouanan          #+#    #+#             */
/*   Updated: 2024/11/09 20:32:23 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tmp;
	size_t	max_size;

	max_size = (size_t)-1;
	if (size != 0 && nmemb > max_size / size)
		return (NULL);
	tmp = malloc(nmemb * size);
	if (tmp == NULL)
		return (NULL);
	ft_bzero(tmp, nmemb * size);
	return ((void *)tmp);
}
