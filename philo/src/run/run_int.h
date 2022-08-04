/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_int.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 13:26:00 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 13:28:05 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_INT_H
# define RUN_INT_H

# include "../structs.h"

void	monitor_phils(t_data *data);

void	eat_phil(t_phil *phil);
void	think_phil(t_phil *phil);
void	sleep_phil(t_phil *phil);

void	*start_phil(void *_phil);

#endif
