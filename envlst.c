/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:23 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/21 19:39:58 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

t_env	*envlast(t_env *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	envadd_back(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		envlast(*lst)->next = new;
	else
		*lst = new;
}

t_env	*envnew(char *var, char *value, int exp)
{
	t_env	*n;

	n = ft_malloc(sizeof(t_env));
	if (!n)
		return (NULL);
	n->exp = exp;
	n->var = var;
	n->value = value;
	n->next = NULL;
	return (n);
}
