/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:16:34 by ybouanan          #+#    #+#             */
/*   Updated: 2025/04/26 02:09:48 by ybouanan         ###   ########.fr       */
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
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	return (cmd);
}
