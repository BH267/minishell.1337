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

typedef struct e_list
{
	char			*var;
	char			*value;
	int				exp;
	struct e_list	*next;
}					t_env;

int					beforequ(char *str);
t_env				*envlast(t_env *lst);
void				printenv(t_env *env, int exp);
t_env				*envtolist(char **env);
t_env				*envnew(char *var, char *value, int exp);
char				*getvalue(t_env *env, char *var);
void				envadd_back(t_env **lst, t_env *n);
int					editvar(t_env **env, char *var, char *newv);
t_env				*asigneavalue(t_env **env, char *var, char *nvalue);

#endif
