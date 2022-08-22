/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:32:17 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/22 12:00:01 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <pthread.h>
#include "../structs.h"
#include "../util/utils.h"

static void	stop(t_phil *killed, t_data *data)
{
	pthread_mutex_lock(&data->global_mutex);
	data->stop = true;
	pthread_mutex_unlock(&data->global_mutex);
	if (killed != NULL)
		print_msg_unchecked(killed, "died");
	return ;
}

static void	check_death_and_eats(t_data *data, bool *ok_eats, t_phil **kill)
{
	t_phil	*phil;
	int		i;
	long	timestamp;

	*ok_eats = (data->num_eat > 0);
	*kill = NULL;
	i = 0;
	timestamp = get_current_timestamp(data);
	while (i < data->num_phil)
	{
		phil = &data->phils[i];
		pthread_mutex_lock(&phil->personal_lock);
		if (timestamp - phil->time_of_last_eat >= data->time_to_die)
			*kill = phil;
		if (*ok_eats && phil->times_eaten < data->num_eat)
			*ok_eats = false;
		pthread_mutex_unlock(&phil->personal_lock);
		if (*kill != NULL)
			break ;
		i++;
	}
}

void	monitor_phils(t_data *data)
{
	bool	ok_eats;
	t_phil	*kill;

	kill = NULL;
	while (true)
	{
		check_death_and_eats(data, &ok_eats, &kill);
		if (kill != NULL || ok_eats)
		{
			stop(kill, data);
			break ;
		}
	}
}
