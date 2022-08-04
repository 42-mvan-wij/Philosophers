/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:22:10 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 13:43:45 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../structs.h"
#include "../util/utils.h"
#include "./data_int.h"

void	free_phils(t_phil **phils, int phils_created)
{
	if (*phils == NULL)
		return ;
	while (phils_created > 0)
	{
		phils_created--;
		pthread_mutex_destroy(&(*phils)[phils_created].personal_lock);
	}
	free(*phils);
	*phils = NULL;
}

t_status	create_phils(t_data *data)
{
	int	i;

	data->phils = malloc(sizeof(t_phil) * data->num_phil);
	if (data->phils == NULL)
	{
		free_fork_mutexes(&data->fork_mutexes, data->num_phil);
		return (set_err(E_MALLOC_FAIL));
	}
	i = 0;
	while (i < data->num_phil)
	{
		data->phils[i].seat = i + 1;
		data->phils[i].times_eaten = 0;
		data->phils[i].right = &data->fork_mutexes[i];
		data->phils[i].left = &data->fork_mutexes[(i + 1) % data->num_phil];
		// data->phils[i].soul = 0;
		data->phils[i].data = data;
		data->phils[i].time_of_last_eat = 0;
		if (pthread_mutex_init(&data->phils[i].personal_lock, NULL) != 0)
		{
			free_fork_mutexes(&data->fork_mutexes, data->num_phil);
			free_phils(&data->phils, i - 1);
			return (set_err(E_MALLOC_FAIL));
		}
		i++;
	}
	return (OK);
}
