/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:32:17 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 13:25:25 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <pthread.h>
#include "../structs.h"
#include "../util/utils.h"

void	monitor_phils(t_data *data)
{
	t_phil	*phil;
	int		i;
	bool	ok_eats;
	long	timestamp;
	t_phil	*kill;

	kill = NULL;
	while (true)
	{
		timestamp = get_current_timestamp(data);
		ok_eats = (data->num_eat > 0);
		i = 0;
		while (i < data->num_phil)
		{
			phil = &data->phils[i];
			pthread_mutex_lock(&phil->personal_lock);
			if (timestamp - phil->time_of_last_eat >= data->time_to_die)
				kill = phil;
			if (ok_eats && phil->times_eaten < data->num_eat)
				ok_eats = false;
			pthread_mutex_unlock(&phil->personal_lock);
			i++;
		}
		if (kill != NULL || ok_eats)
		{
			pthread_mutex_lock(&data->global_mutex);
			data->stop = true;
			pthread_mutex_unlock(&data->global_mutex);
			if (kill != NULL)
				print_msg_unchecked(kill, "died");
			return ;
		}
	}
}
