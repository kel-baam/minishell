/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:29:18 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/03 10:29:21 by kel-baam         ###   ########.fr       */
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
void	handel2(void)
{
	printf("^C");
	g_data.status_code = 130;
	//rl_on_new_line();
	// rl_replace_line("^C",0);
	//rl_redisplay();
}

void	get_inputfile_fd(int *last_fd, t_list *redir_in)
{
	t_list	*tmp_redir_in;

	tmp_redir_in = redir_in;
	while (tmp_redir_in)
	{
		*(last_fd) = open(tmp_redir_in->content, O_RDONLY, 0644);
		if (*(last_fd) == -1)
			print_cmd_error(tmp_redir_in->content,NULL, strerror(errno), 1);
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

void	execute_command(t_command *tmp_command, char *path, char **envs)
{
	if (!is_bultin(tmp_command->cmd))
	{
		g_data.status_code = execute_bultin(tmp_command, 1);
		return ;
	}
	else
	{
		if (execve(path, tmp_command->args, envs) == -1)
			exit(1);
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
		g_data.status_code = WEXITSTATUS(status);
	}
}

char	*get_my_path(t_command *tmp_command, char **envs)
{
	char	*path;

	if (!(tmp_command->cmd))
		exit(0);
	if (is_bultin(tmp_command->cmd))
	{
		path = get_actual_path(tmp_command->cmd, tmp_command, envs);
		if (!path)
			print_cmd_error(tmp_command->cmd,NULL, " command not found", 127);
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
void	executer(t_list *commands, char **envs)
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
			// tcsetattr(STDIN_FILENO, TCSANOW, &(g_data.oldTerm));
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);

			get_inputfile_fd(&last_fd, tmp_command->redir_in);
			get_outfile_fd(&fds[1], tmp_command->redir_out);
			duplicate_fds(tmp, last_fd, fds);
			execute_command(tmp_command, get_my_path(tmp_command, envs), envs);
			return ;
		}
		else
		{
			//signal(SIGINT, handel2);
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
