/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 04:53:38 by deepseeko         #+#    #+#             */
/*   Updated: 2025/05/12 12:10:29 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
#define EXPAND_H

#include "header/lexer_token.h"
#include "binsutils.h"

char *add_quotes(char *str);
char *get_value_with_mask(char mask, t_env env, char *var);
void replace_variable(char *value, char *var, char *expanded_value);
void start_expand_variable(char *value, char *var, t_env *env, char mask);

#endif
