/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hb_lstaddin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:13:20 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/13 12:18:20 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhb.h"

void	hb_lstaddin(t_list **node, t_list *new)
{
	if (!new || !node)
		return ;
	new->next = (*node)->next;
	(*node)->next = new;
}
