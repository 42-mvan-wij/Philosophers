/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 13:09:07 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 13:11:08 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "../../structs.h"
#include "../../util/utils.h"

static bool	with_mutex(pthread_mutex_t *mutex, bool (*fn)(void *), void *data)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (false);
	if (!fn(data))
	{
		pthread_mutex_unlock(mutex);
		return (false);
	}
	if (pthread_mutex_unlock(mutex) != 0)
		return (false);
	return (true);
}

static bool	update_eats(void *param)
{
	t_phil	*phil;

	phil = param;
	phil->times_eaten++;
	phil->time_of_last_eat = get_current_timestamp(phil->data);
	return (true);
}

static bool	eat(void *param)
{
	t_phil	*phil;

	phil = param;
	if (!print_msg(phil, "has taken a fork") \
	|| !print_msg(phil, "is eating") \
	|| !with_mutex(&phil->personal_lock, &update_eats, phil))
		return (false);
	msleep(phil->data->time_to_eat, phil->data);
	return (true);
}

static bool	grab_other_fork_and_eat(void *param)
{
	t_phil			*phil;
	pthread_mutex_t	*second;

	phil = param;
	second = phil->right;
	if (phil->seat % 2 == 0)
		second = phil->left;
	if (!print_msg(phil, "has taken a fork") \
	|| !with_mutex(second, &eat, phil))
		return (false);
	return (true);
}

bool	eat_phil(t_phil *phil)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = phil->left;
	second = phil->right;
	if (phil->seat % 2 == 0)
	{
		first = phil->right;
		second = phil->left;
	}
	if (!with_mutex(first, &grab_other_fork_and_eat, phil))
		return (false);
	return (true);
}
