#include "phil.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

t_status	set_err(t_status err);
void	print_err(void);

__attribute__((constructor))
void tmp_test_errs() {
	printf("hello\n");
	int old = dup(STDOUT_FILENO);
	int dev_null = open("/dev/null", O_WRONLY);
	fflush(NULL);
	dup2(dev_null, STDOUT_FILENO);
	for (int i = 0; i < tmp_status_end; i++) {
		if (i == SUCCESS)
			continue ;
		set_err(i);
		print_err();
	}
	fflush(NULL);
	dup2(old, STDOUT_FILENO);
	set_err(SUCCESS);
}
