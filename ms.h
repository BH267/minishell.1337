/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 10:43:06 by habenydi          #+#    #+#             */
/*   Updated: 2025/03/09 10:44:28 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H

#include "header/mini.h"
#include "libhb/libhb.h"
#include "builtins/bins.h"
#include "ft_malloc/ft_malloc.h"

typedef enum e_type {
	cmd,
	file,
	metachar,
}	t_type;

typedef struct s_content {
	char	*str;
	t_type	type;
}	t_node;

t_list	*lexer(char *cmd);
char	*getpath(char *cmd, char **env);
int	execute(char *cmd, char **env);
void	ft_exit(int e, char *cmd);

#endif
