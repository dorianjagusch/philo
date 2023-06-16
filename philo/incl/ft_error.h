/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:50:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 10:35:27 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

enum e_errors
{
	farg_err = 1,
	barg_err,
	type_err,
	mem_err,
	mutex_create_err,
	mutex_destroy_err,
	thread_err,
	sleep_err,
	join_err,
};

#endif