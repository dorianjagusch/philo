/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:56:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 11:30:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*s2;

	i = 0;
	s2 = s;
	while (i < n)
		s2[i++] = '\0';
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem_arr;

	if (size == 0 || nmemb == 0)
		return (ft_calloc(1, 1));
	if ((nmemb > 0 && (nmemb * size) / nmemb != size)
		|| (size > 0 && (nmemb * size) / size != nmemb))
		return (NULL);
	mem_arr = (void *)malloc(sizeof(*mem_arr) * (nmemb * size));
	if (!mem_arr)
		return (NULL);
	ft_bzero(mem_arr, nmemb * size);
	return (mem_arr);
}
