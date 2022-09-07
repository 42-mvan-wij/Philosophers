/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_phil.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:27:16 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 13:07:45 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include "../structs.h"
#include "../util/utils.h"
#include "./run_int.h"

static bool	save_stop(t_data *data, bool *res)
{
	if (pthread_mutex_lock(&data->global_mutex) != 0)
		return (false);
	*res = data->stop;
	if (pthread_mutex_unlock(&data->global_mutex) != 0)
		return (false);
	return (true);
}

static void	run_phil(t_phil *phil)
{
	bool	stop;

	stop = false;
	if (phil->seat % 2 == 0)
		msleep(phil->data->time_to_eat / 2, phil->data);
	while (true)
	{
		if (!eat_phil(phil) \
		|| !save_stop(phil->data, &stop) || stop \
		|| !sleep_phil(phil) \
		|| !save_stop(phil->data, &stop) || stop \
		|| !think_phil(phil) \
		|| !save_stop(phil->data, &stop) || stop)
			break ;
	}
	return ;
}

void	*start_phil(void *_phil)
{
	t_phil	*phil;

	phil = _phil;
	while (true)
	{
		pthread_mutex_lock(&phil->data->global_mutex);
		if (phil->data->pthread_error)
		{
			pthread_mutex_unlock(&phil->data->global_mutex);
			return (NULL);
		}
		if (phil->data->start)
			break ;
		pthread_mutex_unlock(&phil->data->global_mutex);
	}
	pthread_mutex_unlock(&phil->data->global_mutex);
	run_phil(phil);
	return (NULL);
}
