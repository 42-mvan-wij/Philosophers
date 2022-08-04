/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:21:27 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 13:20:45 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "../structs.h"
#include "../util/utils.h"

void	free_fork_mutexes(pthread_mutex_t **fork_mutexes, int forks_created)
{
	if (*fork_mutexes == NULL)
		return ;
	while (forks_created > 0)
	{
		forks_created--;
		pthread_mutex_destroy(&(*fork_mutexes)[forks_created]);
	}
	free(*fork_mutexes);
	*fork_mutexes = NULL;
}

t_status	create_fork_mutexes(t_data *data)
{
	int	i;

	data->fork_mutexes = malloc(sizeof(pthread_mutex_t) * data->num_phil);
	if (data->fork_mutexes == NULL)
		return (set_err(E_MALLOC_FAIL));
	i = 0;
	while (i < data->num_phil)
	{
		if (pthread_mutex_init(&data->fork_mutexes[i], NULL) != 0)
		{
			free_fork_mutexes(&data->fork_mutexes, i - 1);
			return (set_err(E_MALLOC_FAIL));
		}
		i++;
	}
	return (OK);
}
