/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil_struct.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:39:20 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 12:41:10 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_STRUCT_H
# define PHIL_STRUCT_H

# include <pthread.h>

typedef struct s_phil
{
	int				seat;
	int				times_eaten;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		soul;
	struct s_data	*data;
	int				time_of_last_eat;
	pthread_mutex_t	personal_lock;
}	t_phil;

#endif
