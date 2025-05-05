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
# include <sys/types.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include "builtins/bins.h"
# include "ft_malloc/ft_malloc.h"
# include "header/lexer_token.h"
# include "libhb/libhb.h"

void		signals(int sig);
int			pip(t_ms *ms, t_cmd *cmd);
int			b2o(int	pfdo, int pfdi, int doit);
int			builtins(char *cmd, t_ms *ms);
int			singlecmd(t_ms *ms, t_cmd *cmd);
int			redirect(t_ms *ms);
int			pars_exec(t_cmd *cmd, t_ms *ms, int bins);
int			varexp(t_ms *ms);
t_token		*lexer(const char *input);
int			beforequ(char *str);
int			execute(t_ms *ms);
char		*getpath(char *cmd, char **env);
t_cmd		*parsing(char *cmdl);
void		parsing2(char *cmdl);

#endif
