/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:21:05 by ybouanan          #+#    #+#             */
/*   Updated: 2025/03/05 06:53:40 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HEADER_MINI_H
#define HEADER_MINI_H

typedef enum x_code
{
	CMD,
	PIPE,
	RED_EN,
	HERDOC,
	OR,
	AND
} e_code;

typedef struct s_tokens
{
	char *val;
	e_code token;
}t_tokens;

typedef struct s_env
{
	char *key;
	char *value;
} t_env;


/*
 ls -a > out | ps
*/
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../libft/libft.h"
int	ft_printf(const char *mstr, ...);

#endif
