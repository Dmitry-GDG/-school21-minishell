/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_rdr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarg <kmarg@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:53:13 by kmarg             #+#    #+#             */
/*   Updated: 2022/03/15 16:58:38 by kmarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_print_mssg1(char *f_name, t_data *data)
{
	write(2, "minishell: ", 11);
	write(2, f_name, ft_strlen(f_name));
	write(2, ": No such file or directory\n", 28);
	data->exit_status = 1;
	return (data->exit_status);
}

static void	rdl_add(t_data *data, char tmpe[22][22])

{
	int	filein;
	int	i;

	data->tmp.i--;
	i = -1;
	while (++i <= data->tmp.i)
	{		
		filein = open(tmpe[i], O_RDONLY);
		if (filein < 0)
		{
			my_print_mssg1(tmpe[i], data);
			exit (1);
		}
		dup2(filein, STDIN_FILENO);
		close(filein);
	}
}

int	child_rdl(t_data *data)
{
	int		m;
	char	tmpe[22][22];

	data->tmp.i = 0;
	while (data->cmds[data->tmp.h]->redir_l[data->tmp.i])
	{
		m = 0;
		data->tmp.j = 0;
		while (data->cmds[data->tmp.h]->redir_l[data->tmp.i][data->tmp.j] \
		!= '\0')
		{
			if (data->cmds[data->tmp.h]->redir_l[data->tmp.i][data->tmp.j] != \
	'<' && data->cmds[data->tmp.h]->redir_l[data->tmp.i][data->tmp.j] != ' ' && \
	data->cmds[data->tmp.h]->redir_l[data->tmp.i][data->tmp.j] != '\0')
				tmpe[data->tmp.i][m++] = \
				data->cmds[data->tmp.h]->redir_l[data->tmp.i][data->tmp.j++];
			else
				data->tmp.j++;
		}
		tmpe[data->tmp.i][m] = '\0';
		data->tmp.i++;
	}
	rdl_add(data, tmpe);
	return (0);
}

static void	rdr_add(t_data *data, char tmpe[22][22])
{
	int	fileout;
	int	i;

	data->tmp.i--;
	i = 0;
	while (i <= data->tmp.i)
	{
		if (data->cmds[data->tmp.h]->redir_r[i][1] != '>')
			fileout = open(tmpe[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fileout = open(tmpe[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fileout, STDOUT_FILENO);
		close(fileout);
		i++;
	}
}

int	child_rdr(t_data *data)
{
	int		m;
	char	tmpe[22][22];

	data->tmp.i = 0;
	data->tmp.j = 0;
	while (data->cmds[data->tmp.h]->redir_r[data->tmp.i])
	{
		m = 0;
		while (data->cmds[data->tmp.h]->redir_r[data->tmp.i][data->tmp.j] \
				!= '\0')
		{
			if (data->cmds[data->tmp.h]->redir_r[data->tmp.i][data->tmp.j] \
	!= '>' && data->cmds[data->tmp.h]->redir_r[data->tmp.i][data->tmp.j] != ' ' \
	&& data->cmds[data->tmp.h]->redir_r[data->tmp.i][data->tmp.j] != '\0')
				tmpe[data->tmp.i][m++] = \
				data->cmds[data->tmp.h]->redir_r[data->tmp.i][data->tmp.j++];
			else
				data->tmp.j++;
		}
		tmpe[data->tmp.i][m] = '\0';
		data->tmp.i++;
		data->tmp.j = 0;
	}
	rdr_add(data, tmpe);
	return (0);
}
