/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:29:18 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/03 23:11:15 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	get_outfile_fd(int *fd, t_list *file_list)
{
	t_list	*tmp;
	t_red	*tmp_redir;

	tmp = file_list;
	while (tmp)
	{
		tmp_redir = (t_red *)tmp->content;
		if (tmp_redir->flag)
			*fd = open(tmp_redir->file_name, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		else
			*fd = open(tmp_redir->file_name, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		if (*fd == -1)
			print_cmd_error(tmp_redir->file_name, NULL, strerror(errno), 1);
		if (tmp->next && *(fd) != STDOUT_FILENO)
			close(*fd);
		tmp = tmp->next;
	}
}

//tomorrow complete herdoc and check sttus code and some issues in exit status

void exec_herdoc(char *del,int fd)
{
    char *line;
    while(1)
    {
		line=readline("herdoc>");
        if(!ft_strncmp(del,line,ft_strlen(del)))
			break ;
		//read(fd,line,ft_strlen(line));
		free(line);
	}
}
void	get_inputfile_fd(int *last_fd, t_list *redir_in)
{
	t_list	*tmp_redir_in;

	tmp_redir_in = redir_in;
	t_red	*tmp;

	while (tmp_redir_in)
	{
		tmp = (t_red *)tmp_redir_in->content;
		if(tmp->flag)
			*(last_fd) = open(tmp->file_name, O_RDONLY, 0644);
		if (*(last_fd) == -1)
		{
			g_data.status_code =print_cmd_error(tmp->file_name,NULL, strerror(errno), 1);
			exit(g_data.status_code);
		}
		if(!(tmp->flag))
			exec_herdoc(tmp->file_name,*last_fd);
		if (tmp_redir_in->next && *last_fd)
			close(*last_fd);
		tmp_redir_in = tmp_redir_in->next;
	}
}

void	duplicate_fds(t_list *tmp, int last_fd, int *fds)
{
	t_command	*tmp_command;

	tmp_command = (t_command *)tmp->content;
	if (last_fd != STDIN_FILENO)
	{
		dup2(last_fd, STDIN_FILENO);
		close(last_fd);
	}
	if (tmp->next || tmp_command->redir_out)
		dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	close(fds[0]);
}

void	execute_command(t_command *tmp_command, char *path)
{
	if (!is_bultin(tmp_command->cmd))
	{
		g_data.status_code = execute_bultin(tmp_command, 1);
		return ;
	}
	else
	{ 
		char **envs=convert_tree_to_array();
		if (execve(path, tmp_command->args, envs) == -1)
			exit(127);
	}
}

void	closing_pipe(t_list *commands, int *fd, int *pidd, int i)
{
	int	j;
	int	status;

	j = 0;
	if (commands)
	{
		while (j < i)
		{
			close(fd[j]);
			waitpid(pidd[j], &status, 0);
			j++;
		}
		//128+status  when a process is terminated by a signal
		if(status==SIGINT)
				g_data.status_code=130;
		else if(status==SIGQUIT)
			{
				g_data.status_code=131;
				printf("Quit: 3\n");
			}
		 else
		 	g_data.status_code = WEXITSTATUS(status);
	}
}

char	*get_my_path(t_command *tmp_command)
{
	char	*path;

	if (!(tmp_command->cmd))
		exit(0);
	if (is_bultin(tmp_command->cmd))
	{
		path = get_actual_path(tmp_command->cmd, tmp_command);
		if (!path)
			g_data.status_code=print_cmd_error(tmp_command->cmd,NULL, " command not found", 127);
	}
	return (path);
}

int	run_builtins(t_list *commands)
{
	t_command	*tmp_command;
	int			infile;
	int			outfile;

	tmp_command = (t_command *)commands->content;
	infile = 0;
	outfile = 1;

	if (commands && !commands->next)
	{
		if ((!strcmp(tmp_command->cmd, "unset") || !strcmp(tmp_command->cmd,
					"export") || !strcmp(tmp_command->cmd, "cd")
				|| !strcmp(tmp_command->cmd, "exit")))
		{
			get_inputfile_fd(&infile, tmp_command->redir_in);
			get_outfile_fd(&outfile, tmp_command->redir_out);

			g_data.status_code=execute_bultin(tmp_command, outfile);
		
			return g_data.status_code;

		}
	}
	return (-1);
}

void	executer(t_list *commands)
{
	int			fds[2];
	t_list		*tmp;
	int			fd[1024];
	int			pidd[1000];
	int			i;
	t_command	*tmp_command;
	int			pid;
	int			last_fd;

	tmp = commands;
	i = 0;
	last_fd = STDIN_FILENO;
	if (run_builtins(tmp)>=0)
		return ;
	while (tmp)
	{
		tmp_command = (t_command *)tmp->content;
		if (pipe(fds) == -1)
			print_cmd_error(tmp_command->cmd,tmp_command->args[1], strerror(errno), 1);

		pid = fork();
		if (!pid)
		{
			signals_for_child();
			get_inputfile_fd(&last_fd, tmp_command->redir_in);
			get_outfile_fd(&fds[1], tmp_command->redir_out);
			duplicate_fds(tmp, last_fd, fds);
			execute_command(tmp_command, get_my_path(tmp_command));
			exit(g_data.status_code) ;
		}
		else
		{
			pidd[i] = pid;
			fd[i] = fds[0];
			last_fd = fds[0];
			tmp = tmp->next;
			close(fds[1]);
			i++;
		}
	}
	closing_pipe(commands, fd, pidd, i);
}
