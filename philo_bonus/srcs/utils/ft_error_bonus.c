/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:02:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 20:25:01 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(int error)
{
	static const char	*errors[] = {
		"Too few arguments\n",
		"Too many arguments\n",
		"All arguments must be positive and of type int\n",
		"Malloc failed\n",
		"sem_open() failed\n",
		"sem_close() failed\n",
		"sem_unlink() failed\n",
		"sem_wait() failed\n",
		"sem_post() failed\n",
		"fork() failed\n",
		"usleep() failed\n",
		"waitpid() failed\n"
	};

	printf("\e[2;31mError\x1b[m: %s", errors[error - 150]);
	if (error == barg_err || error == farg_err)
	{
		printf("\tProvide input as ./philo <n_philo> time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> (n_times_to_eat)\n");
	}
	return (error);
}
