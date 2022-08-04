/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 12:25:00 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/08/04 13:35:22 by mvan-wij      ########   odam.nl         */
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

// p1  f1  p2 f2
// f5         p3
// p5  f5  p4 f

// 1 3
// 2 4
// 1 3
// 2 5
// 1 3
// 2 4


// 1	eat				eat				eat				eat
// 2			eat				eat				eat				eat
// 3	eat				eat				eat				eat
// 4			eat								eat
// 5							eat								eat

// 1	eat						eat				eat						eat
// 2			eat						eat				eat						eat
// 3	eat				eat						eat				eat
// 4			eat				eat						eat				eat
// 5					eat				eat						eat				eat
