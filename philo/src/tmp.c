#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "./structs.h"

t_status	set_err(t_status err);
void	print_err(void);

__attribute__((constructor))
void tmp_test_errs() {
	int old = dup(STDOUT_FILENO);
	int dev_null = open("/dev/null", O_WRONLY);
	fflush(NULL);
	dup2(dev_null, STDOUT_FILENO);
	for (int i = 0; i < tmp_status_end; i++) {
		if (i == OK)
			continue ;
		set_err(i);
		print_err();
	}
	fflush(NULL);
	dup2(old, STDOUT_FILENO);
	set_err(OK);
}
