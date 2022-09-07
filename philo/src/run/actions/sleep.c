/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 13:09:11 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 13:11:00 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "../../structs.h"
#include "../../util/utils.h"

bool	sleep_phil(t_phil *phil)
{
	if (!print_msg(phil, "is sleeping"))
		return (false);
	msleep(phil->data->time_to_sleep, phil->data);
	return (true);
}
