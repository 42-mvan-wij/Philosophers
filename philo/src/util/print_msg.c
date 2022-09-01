/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_msg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 12:29:42 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 12:57:33 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "../structs.h"
#include "./utils.h"

static bool	print_msg_internal(t_phil *phil, char *msg, bool check)
{
	char		buff[128];
	const long	timestamp = get_current_timestamp(phil->data);
	char		*buff_ptr;

	buff_ptr = buff;
	buff_ptr = ft_itob(timestamp, buff_ptr, 128 - (buff_ptr - buff));
	buff_ptr = append(" ", buff_ptr, 128 - (buff_ptr - buff));
	buff_ptr = ft_itob(phil->seat, buff_ptr, 128 - (buff_ptr - buff));
	buff_ptr = append(" ", buff_ptr, 128 - (buff_ptr - buff));
	buff_ptr = append(msg, buff_ptr, 128 - (buff_ptr - buff));
	buff_ptr = append("\n", buff_ptr, 128 - (buff_ptr - buff));
	if (pthread_mutex_lock(&phil->data->global_mutex) != 0)
		return (false);
	if (!check || !phil->data->stop)
		write(STDOUT_FILENO, buff, buff_ptr - buff);
	if (pthread_mutex_unlock(&phil->data->global_mutex) != 0)
		return (false);
	return (true);
}

bool	print_msg_unchecked(t_phil *phil, char *msg)
{
	return (print_msg_internal(phil, msg, false));
}

bool	print_msg(t_phil *phil, char *msg)
{
	return (print_msg_internal(phil, msg, true));
}
