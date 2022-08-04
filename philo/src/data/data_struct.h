/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data_struct.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:38:57 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 12:40:53 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCT_H
# define DATA_STRUCT_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	pthread_mutex_t	*fork_mutexes;
	struct s_phil	*phils;
	pthread_mutex_t	global_mutex;
	bool			pthread_error;
	bool			start;
	bool			stop;
	struct timeval	start_time;
}	t_data;

#endif
