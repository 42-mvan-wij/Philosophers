/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil_actions.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:27:05 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/09 11:13:14 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "../structs.h"
#include "../util/utils.h"

void	eat_phil(t_phil *phil)
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
	pthread_mutex_lock(first);
	print_msg(phil, "has taken a fork");
	pthread_mutex_lock(second);
	print_msg(phil, "has taken a fork");
	print_msg(phil, "is eating");
	pthread_mutex_lock(&phil->personal_lock);
	phil->times_eaten++;
	phil->time_of_last_eat = get_current_timestamp(phil->data);
	pthread_mutex_unlock(&phil->personal_lock);
	msleep(phil->data->time_to_eat, phil->data);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

void	think_phil(t_phil *phil)
{
	print_msg(phil, "is thinking");
}

void	sleep_phil(t_phil *phil)
{
	print_msg(phil, "is sleeping");
	msleep(phil->data->time_to_sleep, phil->data);
}
