/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:28:19 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/08 13:19:50 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "../structs.h"
#include "./utils.h"

void	msleep(unsigned int ms)
{
	struct timeval	start;
	struct timeval	tp;

	if (ms == 0)
		return ;
	gettimeofday(&start, NULL);
	tp = start;
	while ((tp.tv_sec - start.tv_sec) * 1000
		+ (tp.tv_usec - start.tv_usec) / 1000 < ms)
	{
		usleep(500);
		gettimeofday(&tp, NULL);
	}
}

void	msleep2(unsigned int ms, t_data *data)
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

void	msleep3(unsigned int ms)
{
	struct timeval	start;
	struct timeval	tp;

	if (ms == 0)
		return ;
	gettimeofday(&start, NULL);
	tp = start;
	while ((tp.tv_sec - start.tv_sec) * 1000000
		+ (tp.tv_usec - start.tv_usec) < ms * 1000)
	{
		usleep(500);
		gettimeofday(&tp, NULL);
	}
}
