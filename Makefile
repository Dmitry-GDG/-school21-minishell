# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/15 10:49:12 by trurgot           #+#    #+#              #
#    Updated: 2022/03/16 21:18:57 by trurgot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
HEAD		=	include/minishell.h 

SRCS		=	src/minishell.c \
				src/minishell1.c \
				src/parcing.c \
				src/return_mssgs.c \
				src/pre_parcing0_env.c \
				src/pre_parcing1_quotes.c \
				src/pre_parcing2_pipes.c \
				src/pre_parcing3_redirs.c \
				src/p1_split_data.c \
				src/p2_chck_env_vars.c \
				src/p3_chck_redirections.c \
				src/p4_fill_redirs.c \
				src/p5_correct_cmds_and_args.c \
				src/p5_correct_cmds_and_args1.c \
				built_fn/cd.c \
				built_fn/echo.c \
				built_fn/env.c \
				built_fn/exit.c \
				built_fn/export.c \
				built_fn/export1.c \
				built_fn/pwd.c \
				built_fn/unset.c \
				core/core1.c \
				core/exec_built.c \
				core/core_rdr.c \
				core/core_hdc.c \
				core/core_cmd_chkr.c \
				core/core_forks.c \
				core/core_join_args.c

LIBFT_DIR	=	libft/
LIBFT		=	$(LIBFT_DIR)libft.a
RL_INCLUDE	=	$(HOME)/.brew/opt/readline/include
RL_LIB		=	$(HOME)/.brew/opt/readline/lib

OBJS		=	$(SRCS:.c=.o)

CC			=	cc
CFLAGS		=	-O2 -Wall -Wextra -Werror
# CFLAGS		=	-fsanitize=address -fsanitize=undefined \
# 				-fno-omit-frame-pointer -g3 \
# 				-Wall -Wextra -Werror -Wpedantic \
# 				-O0 -MMD
# CFLAGS		=	-fsanitize=address -Wall -Wextra -Werror 

RM			=	rm -f

.PHONY		:	all clean fclean re

all			:	$(LIBFT) $(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS)  -lreadline -L $(RL_LIB) -I $(RL_INCLUDE) -L $(LIBFT_DIR) -lft $(OBJS) -o $@

%.o			:	%.c $(HEAD) Makefile
				$(CC) -Wall -Wextra -Werror -g3 -c $< -o $@ -I $(RL_INCLUDE)

$(LIBFT)	:
				@make -C $(LIBFT_DIR)

clean		:
				rm -f $(OBJS)
				@make -C libft clean
	
fclean		:	clean
				$(RM) $(NAME) $(LIBFT_DIR)libft.a

re			:	fclean all
