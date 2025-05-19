/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 04:53:38 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/19 11:55:50 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
#define EXPAND_H

#include "../header/lexer_token.h"
#include "../binsutils.h"

typedef struct data_splited
{
	char	**args;
	char	**mask_args;
}	t_data_splited;

void expansion_loop(t_token *tokens, t_env *env);
void	field_spliting_with_mask(t_token **tok);
t_data_splited	*split_args(t_token *token);

#endif
