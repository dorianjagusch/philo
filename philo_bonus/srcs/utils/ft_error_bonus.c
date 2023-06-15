/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:02:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 11:30:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(int error)
{
	static const char	*errors[] = {
		"no error\n",
		"Too few arguments\n",
		"Too many arguments\n",
		"All arguments must be positive integral types\n",
		"Malloc failed\n",
		"mutex creation failed\n",
		"mutex destroy failed\n",
		"semaphore creation failed\n",
		"semaphore joining failed\n"
	};

	printf("\e[2;31mError\x1b[m: %s", errors[error]);
	if (error == barg_err || error == farg_err)
	{
		printf("\tProvide input as ./philo <n_philo> time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> (n_times_to_eat)\n");
	}
	return (error);
}
