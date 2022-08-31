/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_all_phils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:24:37 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/31 16:22:04 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include "../structs.h"
#include "../util/utils.h"
#include "./run_int.h"

static void	phils_set_start(t_data *data)
{
	pthread_mutex_lock(&data->global_mutex);
	gettimeofday(&data->start_time, NULL);
	data->start = true;
	pthread_mutex_unlock(&data->global_mutex);
}

static t_status	detach_phils(int phils_to_join, t_data *data)
{
	while (phils_to_join > 0)
	{
		phils_to_join--;
		pthread_detach(data->phils[phils_to_join].soul);
	}
	if (data->pthread_error)
		return (set_err(E_THREAD_FAIL));
	return (OK);
}

t_status	run_all_phils(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->global_mutex, NULL) != 0)
		return (set_err(E_MALLOC_FAIL));
	data->stop = false;
	data->start = false;
	data->pthread_error = false;
	i = 0;
	while (i < data->num_phil)
	{
		if (pthread_create(&data->phils[i].soul, NULL, &start_phil,
				&data->phils[i]) != 0)
		{
			pthread_mutex_lock(&data->global_mutex);
			data->pthread_error = true;
			pthread_mutex_unlock(&data->global_mutex);
			phils_set_start(data);
			return (detach_phils(i, data));
		}
		i++;
	}
	phils_set_start(data);
	monitor_phils(data);
	return (detach_phils(i, data));
}
