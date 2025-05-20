/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:19:37 by ybouanan          #+#    #+#             */
/*   Updated: 2025/03/05 08:53:08 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_free(void)
{
	struct s_gc	*current;
	struct s_gc	*temp;

	current = *get_box();
	while (current)
	{
		free(current->p);
		temp = current;
		current = current->next;
		free(temp);
	}
	*get_box() = NULL;
}

struct s_gc	**get_box(void)
{
	static struct s_gc	*head;

	return (&head);
}

void	add_to_box(void *addr)
{
	struct s_gc	*mem_node;

	mem_node = ft_malloc(sizeof(struct s_gc));
	if (!mem_node)
		return (ft_free(), exit(1));
	mem_node->p = addr;
	mem_node->next = *get_box();
	*get_box() = mem_node;
}

void	*ft_malloc(size_t bytes)
{
	void	*p;

	p = ft_malloc(bytes);
	if (!p)
		return (ft_free(), exit(1), NULL);
	add_to_box(p);
	return (p);
}
