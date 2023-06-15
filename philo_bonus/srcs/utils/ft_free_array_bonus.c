/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:20:20 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 11:30:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_free_array(void ***array, size_t index)
{
	int	i;

	i = 0;
	while (i < (int) index)
	{
		free((*array)[i]);
		(*array)[i++] = NULL;
	}
	free(*array);
	array = NULL;
	return (NULL);
}
