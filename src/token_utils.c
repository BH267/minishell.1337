/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:58:45 by ybouanan          #+#    #+#             */
/*   Updated: 2025/04/26 02:08:16 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ft_malloc/ft_malloc.h"

void	free_tokens(t_token *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst->next;
		lst = tmp;
	}
}

int	count_args(t_token *lst)
{
	int	c;

	c = 0;
	while (lst && lst->type == TOKEN_WORD)
	{
		c++;
		lst = lst->next;
	}
	return (c);
}

char	**tokens_to_args(t_token *lst, int n)
{
	char	**args;
	int		i;

	args = (char **)ft_malloc(sizeof(char *) * (n + 1));
	i = 0;
	while (i < n)
	{
		args[i] = lst->value;
		lst = lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
