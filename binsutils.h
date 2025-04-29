/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binsutils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 21:20:10 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/20 21:22:05 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINSUTILS_H
# define BINSUTILS_H

# include "header/lexer_token.h"

typedef struct e_list
{
	char			*var;
	char			*value;
	int				exp;
	struct e_list	*next;
}					t_env;

typedef struct s_stackofvariables
{
	t_env	*env;
	char	**p2env;
	char	*cmd;
	char	**args;
	int		e;
	t_redirect	*rdctl;
}	t_ms;

void	ft_exit(int e);
t_env	*envlast(t_env *lst);
t_env	*envtolist(char **env);
int		beforequ(char *str);
void	printenv(t_env *env, int exp);
char	*getvalue(t_env *env, char *var);
void	envadd_back(t_env **lst, t_env *n);
t_env	*envnew(char *var, char *value, int exp);
t_env	*asigneavalue(t_env **env, char *var, char *nvalue);
int		editvar(t_env **env, char *var, char *newv);
int		eeditvar(t_env **env, char *var, char *newv, int exp);

#endif
