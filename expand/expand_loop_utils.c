/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:02:35 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/22 13:17:43 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ms.h"
#include "expand.h"

void	treat_red(t_token *tok, t_env *env)
{
	char	*var;
	int		i;

	i = 0;
	if (!tok->next || tok->next->value[0] == '\0')
	{
		tok->flag = 404;
		return ;
	}
	i = need_expansion(tok->next->value, tok->next->mask);
	while (i != -1)
	{
		var = find_variable_name(tok->next->value, i);
		handle_expansion(tok->next, var, env, i + 1);
		if (check_ambiguous(&tok->next, var) == -1)
			return ;
		i = need_expansion(tok->next->value, tok->next->mask);
	}
}

void	handle_word_token(t_token *tok, t_env *env)
{
	char	*var_name;
	int		i;

	i = need_expansion(tok->value, tok->mask);
	while (i != -1)
	{
		var_name = find_variable_name(tok->value, i);
		handle_expansion(tok, var_name, env, i + 1);
		i = need_expansion(tok->value, tok->mask);
	}
}

void	handle_redirection(t_token **tok, t_env *env)
{
	treat_red(*tok, env);
	if ((*tok)->next)
		*tok = (*tok)->next;
}
