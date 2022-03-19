# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/27 17:11:47 by jdecorte          #+#    #+#              #
#    Updated: 2022/03/18 19:13:03 by jdecorte42       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

CC = gcc

CFLAGS = -fsanitize=thread -g

RM = rm -rf

SRCS = 	src/main.c\
		libft/libft.a\
		src/init.c\
		src/philo.c\
		src/utils.c



# SRCS_BONUS = src_bonus/checker_bonus.c\
# 			src_bonus/ope1_bonus.c\
# 			src_bonus/ope2_bonus.c\
# 			src_bonus/ope3_bonus.c\
# 			src_bonus/ope4_bonus.c\
# 			src_bonus/utils_bonus.c\
# 			libft/libft.a\

$(NAME) :
	make bonus -C libft
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C libft

re : fclean all

# bonus : 
# 	make bonus -C libft
# 	gcc $(CFLAGS) $(SRCS_BONUS) -o checker