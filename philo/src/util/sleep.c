/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:28:19 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/09 11:13:14 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "../structs.h"
#include "./utils.h"

void	msleep(unsigned int ms, t_data *data)
{
	long	start;
	long	tp;

	if (ms == 0)
		return ;
	start = get_current_timestamp(data);
	tp = start;
	while (tp - start < ms)
	{
		usleep(500);
		tp = get_current_timestamp(data);
	}
}
