# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 11:46:33 by djagusch          #+#    #+#              #
#    Updated: 2023/06/16 16:29:45 by djagusch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS ###

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

### SET UP ###
CC = cc
CFLAGS = -Wall -Werror -Wextra -I$I

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

HEADER = philo.h ft_error.h
HEADER := $(addprefix $I/,$(HEADER))

SRCS := $(foreach FILE,$(FILES),$(shell find $S -type f -name '$(FILE).c'))
OBJS = $(patsubst $S/%,$O/%,$(SRCS:.c=.o))
O_DIRS = $(dir $(OBJS))

NAME = philo
#DEBUG = philo_debug

### RULES ###
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME) -O2
	@echo "$(COLOUR_GREEN) $(NAME) created$(COLOUR_END)"

$O:
	@mkdir -p $@ $(O_DIRS)

$O/%.o: $S/%.c $(HEADER) | $O
	@$(CC) $(CFLAGS) -c $< -o $@

#$(DEBUG): $(OBJS) $(LIBFT)
#	@$(CC) $(CFLAGS) -g -fsanitize=address $(OBJS) -lpthread -o $(DEBUG) -static-libsan
#	@echo "$(COLOUR_GREEN) $(DEBUG) created$(COLOUR_END)"

### CLEANING

clean:
	@$(RM) $(OBJS)
	@if [ -d $O ]; then $(RM) -rf $(O_DIRS) $O; fi

fclean : clean
	@$(RM) $(NAME) $(DEBUG)
	@echo "$(COLOUR_RED) $(NAME) removed$(COLOUR_END)"

re: fclean $(NAME)

.PHONY: all clean fclean re
