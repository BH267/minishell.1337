/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:58:45 by ybouanan          #+#    #+#             */
/*   Updated: 2025/04/28 04:30:42 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"

void	free_tokens(t_token *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst->next;
		// free(lst->value); // Only if value is dynamically allocated and not reused elsewhere!  5ali had l9lawi tanrja3 lih 
		free(lst);
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
