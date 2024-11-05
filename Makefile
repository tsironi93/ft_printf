# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itsiros <itsiros@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 17:34:19 by itsiros           #+#    #+#              #
#    Updated: 2024/11/05 17:01:36 by itsiros          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# # Variables
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft/include
# LDFLAGS = -Llibft
# LIBS = -lft
# SRC = ft_printf.c
# OBJ = $(SRC:.c=.o)
# NAME = libftprintf.a

# # NAMEs
# all: $(NAME)

# # Build static library libftprintf.a
# $(NAME): $(OBJ) libft/libft.a
# 	ar rcs $(NAME) $(OBJ) libft/libft.a

# # Compile object files
# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Ensure libft is built first
# libft/libft.a:
# 	$(MAKE) -C libft

# # Clean object files only
# clean:
# 	$(MAKE) -C libft clean
# 	rm -f $(OBJ)

# # Clean everything in libftprintf and libft
# fclean: clean
# 	$(MAKE) -C libft fclean
# 	rm -f $(NAME)

# # Rebuild everything in libftprintf and libft
# re: fclean all
# 	$(MAKE) -C libft re

# # Mark phony targets
# .PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror -o -I

NAME = libftprintf.a
SRCS = ft_printf.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(NAME)

# Rule to create the library
$(NAME): $(OBJS)
	$(AR) rcs $(NAME) $(OBJS)

# Rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove object files
clean:
	rm -f $(OBJS)

# Fclean target to remove the library and object files
fclean: clean
	rm -f $(NAME)

# Rebuild target to clean and then build again
re: fclean all

.PHONY: all clean fclean re