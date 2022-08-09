/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 12:25:00 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/08 16:21:48 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./structs.h"
#include "./data/data.h"
#include "./run/run.h"
#include "./util/utils.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (create_data(argc, argv, &data) != OK || run_all_phils(&data) != OK)
	{
		free_data(&data);
		print_err();
		return (EXIT_FAILURE);
	}
	free_data(&data);
	return (EXIT_SUCCESS);
}
