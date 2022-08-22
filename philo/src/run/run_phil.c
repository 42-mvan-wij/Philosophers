/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_phil.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:27:16 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/22 12:38:39 by mvan-wij      ########   odam.nl         */
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
		eat_phil(phil);
		if (should_stop(phil->data))
			break ;
		sleep_phil(phil);
		if (should_stop(phil->data))
			break ;
		think_phil(phil);
		if (should_stop(phil->data))
			break ;
	}
	return ;
}

static void	run_lonely_phil(t_phil *phil)
{
	pthread_mutex_lock(phil->left);
	print_msg(phil, "has taken a fork");
	pthread_mutex_unlock(phil->left);
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
	if (phil->data->num_phil == 1)
		run_lonely_phil(phil);
	else
		run_phil(phil);
	return (NULL);
}
