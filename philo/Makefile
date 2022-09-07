# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-wij <mvan-wij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/06/27 15:19:55 by mvan-wij      #+#    #+#                  #
#    Updated: 2022/09/01 13:12:41 by mvan-wij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

################################################################################

BLUE_FG := \e[34m
RESET_COLOR := \e[0m
GREEN_FG := \e[32m
CYAN_FG := \e[36m
CLEAR_REST_OF_LINE := \e[K
print_prefix = printf "$(CYAN_FG)%-$(PROJECT_SPACING)s$(RESET_COLOR) $(GREEN_FG)%-$(RULE_SPACING)s$(RESET_COLOR) : " "[$(1)]" "$(2)"
exec_no_nl = printf "$(1)$(CLEAR_REST_OF_LINE)\n"; $(1); printf "\e[A"

################################################################################

PROJECT		:= Philosophers
NAME		:= philo
NAME_BONUS	:= philo

LIBFT		:=
MINILIBX	:=
MALLOCATOR	:= ../../../Personal/ft_mallocator/libmallocator.a

CC			:= cc
CFLAGS		+= -Wall -Wextra -Werror -Ofast $(if $(DEBUG), -g3) $(if $(SANITIZE), -fsanitize=address -g3)

################################################################################

USER_LIBS +=
SYSTEM_LIBS += pthread
FRAMEWORKS +=
HEADERS += \
	src/data/data_int.h		\
	src/data/data_struct.h	\
	src/data/data.h			\
	src/data/phil_struct.h

HEADERS += \
	src/run/run_int.h		\
	src/run/run.h

HEADERS += \
	src/util/error_struct.h	\
	src/util/utils.h		\

HEADERS += \
	src/structs.h

INCLUDE_HEADERS :=

SOURCES += \
	src/data/args.c		\
	src/data/data.c		\
	src/data/forks.c	\
	src/data/phils.c

SOURCES += \
	src/run/actions/eat.c	\
	src/run/actions/sleep.c	\
	src/run/actions/think.c	\
	src/run/monitor.c		\
	src/run/run_all_phils.c	\
	src/run/run_phil.c

SOURCES += \
	src/util/append.c		\
	src/util/atoi.c			\
	src/util/error.c		\
	src/util/itob.c			\
	src/util/print_msg.c	\
	src/util/sleep.c		\
	src/util/time.c

SOURCES += \
	src/main.c

################################################################################

ifdef BONUS
NAME	:= $(NAME_BONUS)
HEADERS +=
SOURCES	+=
CFLAGS	+= -DBONUS
endif

################################################################################

HEADERS := $(sort $(HEADERS) $(INCLUDE_HEADERS))

OBJDIR := obj
OBJECTS := $(addprefix $(OBJDIR)/, $(SOURCES:c=o))
INCLUDE_FLAGS += $(addprefix -I, $(sort $(dir $(HEADERS))))
LIB_DIRS += $(addprefix -L, $(sort $(dir $(USER_LIBS))))
LIB_LOADS += $(addprefix -l, $(sort $(SYSTEM_LIBS)) $(patsubst lib%,%,$(sort $(basename $(notdir $(USER_LIBS)))))) $(addprefix -framework , $(sort $(FRAMEWORKS)))

export CFLAGS := $(sort $(CFLAGS))
export LIB_FLAGS := $(sort $(LIB_DIRS)) $(sort $(LIB_LOADS))

DATA_FILE := .make_data.txt
MAKE_DATA := $(shell uname) $(CFLAGS) $(LIB_FLAGS) $(INCLUDE_FLAGS) $(sort $(OBJECTS))
ifneq ($(shell echo $(MAKE_DATA)), $(shell cat "$(DATA_FILE)" 2> /dev/null))
PRE_RULES := clean
endif

################################################################################

all: $(PRE_RULES) $(NAME)

$(NAME): $(USER_LIBS) $(OBJECTS)
	@$(call print_prefix,"$(PROJECT)","make")
	$(CC) $(CFLAGS) $(OBJECTS) $(LIB_FLAGS) -o $(NAME)
	@$(call print_prefix,"$(PROJECT)","make")
	@printf "$(BLUE_FG)$(NAME)$(RESET_COLOR) created\n"
	@echo $(MAKE_DATA) > $(DATA_FILE)

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@$(call print_prefix,"$(PROJECT)","make")
	@$(call exec_no_nl,$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(INCLUDES) -c $< -o $@)

debug:
	@$(MAKE) DEBUG=1

clean:
	@$(call print_prefix,"$(PROJECT)","$@")
	rm -rf $(OBJDIR)

fclean: clean
	@$(call print_prefix,"$(PROJECT)","$@")
	rm -f $(NAME)
	@$(call print_prefix,"$(PROJECT)","$@")
	rm -f malloc_test
	@$(call print_prefix,"$(PROJECT)","$@")
	rm -f $(DATA_FILE)

re: fclean all

run: $(NAME)
	@./$(NAME) $(ARGS)

.PHONY: all debug clean fclean re sources

ifdef DEBUG

malloc_test: $(PRE_RULES) $(MALLOCATOR) $(OBJECTS)
	@echo $(MAKE_DATA) > $(DATA_FILE)
	$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic $(OBJECTS) -L../../../Personal/ft_mallocator -lmallocator -ldl $(LIB_FLAGS) -o $@

else

.PHONY: malloc_test
malloc_test:
	$(MAKE) $@ DEBUG=1

endif

$(MALLOCATOR):
	$(MAKE) -C $(dir $(MALLOCATOR))

################################################################################
