/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trurgot <trurgot@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:48:35 by trurgot           #+#    #+#             */
/*   Updated: 2022/03/16 17:52:04 by trurgot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_print_exit(t_data *data)
{
	printf("\033[Aminishell$ exit\n");
	data->exit_status = 0;
	return (0);
}

static void	my_init_data(t_data *data, int argc, char **argv)
{
	int	i;

	(void) argc;
	(void) argv;
	data->exit_status = 0;
	data->pipe_status = 0;
	data->qty_env = 0;
	data->flag_env = 0;
	data->cmd_line = NULL;
	data->pipes.lpipe[0] = -1;
	data->pipes.rpipe[0] = -1;
	data->pipes.lpipe[1] = -1;
	data->pipes.rpipe[1] = -1;
	i = -1;
	while (++i < 100)
		data->env[i] = NULL;
}

static void	signal_c(int c)
{
	(void) c;
	rl_on_new_line();
	rl_redisplay();
	printf("  \n");
	rl_on_new_line();
	rl_replace_line("\0", 0);
	rl_redisplay();
}

static void	my_init_data_routine(t_data *data)
{
	int	i;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_c);
	signal(SIGTSTP, SIG_IGN);
	data->qty_quotes = 0;
	data->qty_pipes = 0;
	data->qty_cmds = 0;
	data->tmp.firstflagdq = 0;
	data->tmp.firstflagq = 0;
	data->tmp.flagdq = 0;
	data->tmp.flagq = 0;
	data->pipe_status = 0;
	i = -1;
	while (++i < 100)
	{
		data->quotes[i] = NULL;
		data->cmds[i] = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		err;

	my_init_data(&data, argc, argv);
	if (my_fill_env(&data, envp))
		return (my_return_mssg(&data, 10));
	while (1)
	{
		my_init_data_routine(&data);
		data.cmd_line = readline("minishell$ ");
		if (data.cmd_line == NULL)
		{
			my_return_mssg(&data, 11);
			return (my_print_exit(&data));
		}
		if (minishell1(&data))
			return (my_return_mssg(&data, 3));
		if (*data.cmd_line && ft_strlen(data.cmd_line))
			add_history(data.cmd_line);
		err = minishell2(&data);
		if (err)
			return (my_return_mssg(&data, err));
		my_return_mssg(&data, 100);
	}
	return (0);
}
