/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:23:36 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/12 16:21:18 by deepseeko        ###   ########.fr       */
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
# include "header/lexer_token.h"
# include "libhb/libhb.h"

# define NORMAL 1
# define CHILD 2
# define HEREDOC 3

void	print_tokens(t_token *tok);
void		b2o(int doit);
int			signals(int mode);
char		*getenvalue(char **env, char *var);
int			runheredoc(t_cmd *cmd);
int			setvalue(char **env, char *var, char *newv);
int			isbins(t_ms *ms);
int			runcmd(t_ms *ms, t_cmd *cmd);
int			heredoc(t_redirect *rdct);
int			pipeline(t_ms *ms, t_cmd *cmd);
int			builtins(char *cmd, t_ms *ms);
int			singlecmd(t_ms *ms);
int			redirect(t_ms *ms);
int			pars_exec(t_cmd *cmd, t_ms *ms);
int			varexp(t_ms *ms);
t_token		*lexer(const char *input);
int			beforequ(char *str);
int			execute(t_ms *ms);
char		*getpath(char *cmd, char **env);
t_cmd		*parsing(char *cmdl, t_env *env);
void		parsing2(char *cmdl,t_env *env);

#endif
