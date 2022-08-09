/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:22:10 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/09 11:12:20 by mvan-wij      ########   odam.nl         */
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

static t_status	fill_phil(t_phil *phil, int i, t_data *data)
{
	phil->seat = i + 1;
	phil->times_eaten = 0;
	phil->right = &data->fork_mutexes[i];
	phil->left = &data->fork_mutexes[(i + 1) % data->num_phil];
	phil->data = data;
	phil->time_of_last_eat = 0;
	if (pthread_mutex_init(&phil->personal_lock, NULL) != 0)
		return (set_err(E_MALLOC_FAIL));
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
		if (fill_phil(&data->phils[i], i, data) != OK)
		{
			free_fork_mutexes(&data->fork_mutexes, data->num_phil);
			free_phils(&data->phils, i - 1);
			return (set_err(E_MALLOC_FAIL));
		}
		i++;
	}
	return (OK);
}
