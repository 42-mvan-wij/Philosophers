/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   think.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 13:09:13 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/09/01 13:10:55 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "../../structs.h"
#include "../../util/utils.h"

bool	think_phil(t_phil *phil)
{
	if (!print_msg(phil, "is thinking"))
		return (false);
	if (phil->data->num_phil % 2 == 1)
		msleep(5, phil->data);
	return (true);
}
