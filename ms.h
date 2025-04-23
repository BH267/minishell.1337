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

# include "builtins/bins.h"
# include "ft_malloc/ft_malloc.h"
# include "header/mini.h"
# include "libhb/libhb.h"

typedef enum e_tockens
{
	cmd,
	file,
	metachar,
}			t_type;

typedef struct s_content
{
	char	*str;
	t_type	type;
}			t_node;

void		ft_exit(int e);
int			varexp(t_ms *ms);
t_list		*lexer(char *cmd);
int			beforequ(char *str);
int			execute(t_ms *ms, char **env);
char		*getpath(char *cmd, char **env);

#endif
