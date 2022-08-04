/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:30:14 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 12:58:03 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "../structs.h"

// struct timeval	get_time_diff(struct timeval start, struct timeval end)
// {
// 	struct timeval	diff;

// 	diff.tv_usec = end.tv_usec - start.tv_usec;
// 	diff.tv_sec = end.tv_sec - start.tv_sec + diff.tv_sec / 1000000;
// 	diff.tv_usec %= 1000000;
// 	return (diff);
// }

long	get_current_timestamp(t_data *data)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec - data->start_time.tv_sec) * 1000
		+ (tp.tv_usec - data->start_time.tv_usec) / 1000);
}
