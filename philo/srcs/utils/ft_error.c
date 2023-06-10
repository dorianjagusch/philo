/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:02:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/10 13:26:00 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(int error)
{
	static const char	*errors[] = {
		"no error\n",
		"Too few arguments\n",
		"Too many arguments\n",
		"All arguments must be positive integral types\n",
		"Malloc failed\n",
		"mutex creation failed\n",
		"mutex destroy failed\n"
		"thread creation failed\n",
		"thread joining failed\n"
	};

	printf("\e[2;31mError\x1b[m: %s", errors[error]);
	if (error == barg_err || error == farg_err)
	{
		printf("\tProvide input as ./philo <n_philo> time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> (n_times_to_eat)\n");
	}
	return (error);
}
