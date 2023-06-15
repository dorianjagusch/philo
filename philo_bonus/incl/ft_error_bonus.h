/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:50:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 11:41:24 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_BONUS_H
# define FT_ERROR_BONUS_H

enum e_errors
{
	farg_err = 1,
	barg_err,
	type_err,
	mem_err,
	sem_create_err,
	sem_destroy_err,
	proc_err,
	sleep_err,
	wait_err,
};

#endif