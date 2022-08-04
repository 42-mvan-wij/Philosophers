/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data_int.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 13:07:48 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 13:42:49 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_INT_H
# define DATA_INT_H

# include <pthread.h>
# include "../structs.h"

void		free_fork_mutexes(pthread_mutex_t **fork_mutexes,
				int forks_created);
t_status	create_fork_mutexes(t_data *data);
void		free_phils(t_phil **phils, int phils_created);
t_status	create_phils(t_data *data);
t_status	parse_args(int argc, char **argv, t_data *data);

#endif
