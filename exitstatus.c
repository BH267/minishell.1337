/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitstatus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habenydi <habenydi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:43:25 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/17 15:48:18 by habenydi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	*estate(void)
{
	static int	exit_status;

	return (&exit_status);
}

int	setes(int e)
{
	*(estate()) = e;
	return (e);
}
