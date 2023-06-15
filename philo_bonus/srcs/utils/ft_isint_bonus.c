/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:02:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 11:30:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_isint(char *str)
{
	long	nbr;
	char	*num;

	if (str)
	{
		nbr = ft_atol(str);
		num = ft_itoa(nbr);
		if (ft_strcmp(str, num) == 0
			&& (long) INT_MIN <= nbr && nbr <= (long) INT_MAX)
		{
			free(num);
			return (nbr);
		}
		free(num);
		return (LONG_MAX);
	}
	return (LONG_MAX);
}
