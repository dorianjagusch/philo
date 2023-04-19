/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:02:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/19 03:26:18 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static BOOL	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (c);
	return (0);
}

static BOOL	ft_isnbr(char *str)
{
	int	flag;

	flag = 0;
	while (*str)
	{
		if (ft_isdigit(*str) || ((*str == '+' || *str == '-') && str + 1
				&& ft_isdigit(*(str + 1))) && flag == 0)
		{
			str++;
			if (*str == '+' || *str == '-')
				flag = 1;
			continue ;
		}
		return (0);
	}	
	return (1);
}

long	ft_isint(char *str)
{
	long	nbr;

	if (str && ft_isnbr(str))
	{
		nbr = ft_atol(str);
		if ((long) INT_MIN <= nbr && nbr <= (long) INT_MAX)
			return (nbr);
		return (LONG_MAX);
	}
}
