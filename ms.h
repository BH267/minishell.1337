/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 10:43:06 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/26 02:05:09 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <string.h>
# include "builtins/bins.h"
# include "ft_malloc/ft_malloc.h"
# include "header/lexer_token.h"
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

typedef struct s_token t_token;

void		ft_exit(int e);
int			varexp(t_ms *ms);
t_token		*lexer(const char *input);
int			beforequ(char *str);
int			execute(t_ms *ms, char **env);
char		*getpath(char *cmd, char **env);
void		parsing(char *cmdl);

#endif
