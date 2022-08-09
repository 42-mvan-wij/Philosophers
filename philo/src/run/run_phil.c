/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_phil.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:27:16 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/09 11:13:14 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include "../structs.h"
#include "../util/utils.h"
#include "./run_int.h"

static bool	should_stop(t_data *data)
{
	bool	stop;

	pthread_mutex_lock(&data->global_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->global_mutex);
	return (stop);
}

static void	run_phil(t_phil *phil)
{
	if (phil->seat % 2 == 0)
		msleep(phil->data->time_to_eat / 2, phil->data);
	while (true)
	{
		think_phil(phil);
		if (should_stop(phil->data))
			break ;
		eat_phil(phil);
		if (should_stop(phil->data))
			break ;
		sleep_phil(phil);
		if (should_stop(phil->data))
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
