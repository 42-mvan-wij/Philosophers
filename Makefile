all:
	@$(MAKE) -C philo

%:
	@$(MAKE) -C philo $@
