# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 11:46:33 by djagusch          #+#    #+#              #
#    Updated: 2023/06/15 18:30:06 by djagusch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS ###

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

### SET UP ###
CC = cc
CFLAGS = -Wall -Werror -Wall -I$I

RM = /bin/rm -f
RMDIR = /bin/rmdir -p

S = srcs
O = objs
I = incl

FILES := main \
data_fnct \
philo_fnct \
sim_set_up \
actions \
sim \
time \
ft_atol \
ft_bzero \
ft_calloc \
ft_error \
ft_free_array \
ft_isint \
ft_itoa \
ft_lmax \
ft_strcmp \

HEADER = philo_bonus.h ft_error_bonus.h
HEADER := $(addprefix $I/,$(HEADER))

SRCS := $(foreach FILE,$(FILES),$(shell find $S -type f -name '$(FILE)_bonus.c'))
OBJS = $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
O_DIRS = $(dir $(OBJS))

NAME = philo_bonus
DEBUG = philo_bonus_debug

### RULES ###
all: $(NAME) $(DEBUG)

print:
	@echo $(SRCS)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)
	@echo "$(COLOUR_GREEN) $(NAME) created$(COLOUR_END)"

$O:
	@mkdir -p $@ $(O_DIRS)

$O/%.o: $S/%.c $(HEADER) | $O
	@$(CC) $(CFLAGS) -c $< -o $@

$(DEBUG): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -g $(OBJS) -lpthread -o $(DEBUG) -fsanitize=address -static-libasan
	@echo "$(COLOUR_GREEN) $(DEBUG) created$(COLOUR_END)"

### CLEANING

clean:
	@$(RM) $(OBJS)
	@if [ -d $O ]; then $(RM) -rf $(O_DIRS) $O; fi

fclean : clean
	@$(RM) $(NAME) $(DEBUG)
	@echo "$(COLOUR_RED) $(NAME) removed$(COLOUR_END)"
	@echo "$(COLOUR_RED) $(DEBUG) removed$(COLOUR_END)"

re: fclean $(NAME) $(DEBUG)

.PHONY: all clean fclean re
