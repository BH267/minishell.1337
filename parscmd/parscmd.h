/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parscmd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:37:46 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/20 12:16:29 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSCMD_H
# define PARSCMD_H

# include "../expand/expand.h"
# include "../header/lexer_token.h"
# include "../ms.h"
# include <ctype.h>

void	print_mask(char *mask);
int		has_quotes_mask_zero(t_token *tok);
void	delete_zeromask_quotes(t_token *tok);
int		count_zeromask_quotes(t_token *tok);
void	clear_quotes(t_token *tokens);
void	split_tokens_by_mask(t_token *tokens);

#endif
