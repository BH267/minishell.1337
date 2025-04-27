/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:16:34 by ybouanan          #+#    #+#             */
/*   Updated: 2025/04/27 17:48:44 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../ft_malloc/ft_malloc.h"
#include <stdlib.h>

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->redirect_list = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_redirect(t_redirect **lst, char *value, t_token_type type)
{
	t_redirect	*new;
	t_redirect	*tmp;

	new = (t_redirect *)ft_malloc(sizeof(t_redirect));
	new->value = value;
	new->type = type;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_redirects(t_redirect *lst)
{
	t_redirect	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}
