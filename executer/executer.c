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


int  get_outfile_fd(t_command *command)
{
	int fd;
	t_red *tmp;
	t_list *tmp_list=command->redir_out;
	fd=STDOUT_FILENO;
	while(tmp_list)
	{
		tmp = (t_red*) tmp_list->content;
		if(tmp->flag)
			fd=open(tmp->file_name,O_WRONLY | O_CREAT | O_TRUNC ,0644);
		else
			fd=open(tmp->file_name,O_WRONLY | O_CREAT | O_APPEND ,0644);
		if(fd==-1)
			print_cmd_error(tmp->file_name, strerror(errno),1, STDERR_FILENO);
		if(tmp_list->next && fd!=STDOUT_FILENO)
			close(fd);
		tmp_list=tmp_list->next;
	}
	return fd;
}

void get_inputfile_fd(int *last_fd, t_list *redir_in)
{
	t_list *tmp_redir_in=redir_in;

	while(tmp_redir_in)
	{
		*(last_fd)=open(tmp_redir_in->content,O_RDONLY ,0644);
		if(*(last_fd)==-1)
			print_cmd_error(tmp_redir_in->content, strerror(errno),1, STDERR_FILENO);
		if(tmp_redir_in->next && *last_fd)
			close(*last_fd);
		tmp_redir_in=tmp_redir_in->next;
	}
}

// void execute_command(t_command *command,char *path,char **envs)
// {
// 	int infile_fd=get_inputfile_fd(command);
// 	int outfile_fd=get_outfile_fd(command);
// 	dup2(infile_fd,STDIN_FILENO);
//     dup2(outfile_fd,STDOUT_FILENO);
// 	execve(path,command->args,envs);

// }
// void redirection_herdoc(t_command *command)
// {
//     t_list *data=NULL;// herdoc fonction i didn't store the given result of this fonction in the principal struct  
// 	t_list *tmp;
// 	data=tmp;
//     char *line;
//     while(1)
//     {
// 		line=readline("> ");
//         if(!ft_strncmp(command->herdoc_delim,line,ft_strlen(command->herdoc_delim)))
// 			break;
//       	tmp->content=line;
//         tmp->next = ft_lstnew(NULL);
//         tmp = tmp->next;
// 	}
// }

void	executer(t_list *commands,char **envs)
{	
	char *path;
	int fds[2];
	t_list *tmp;
	tmp=commands;
	t_command *tmp_command;
	int pid;
	
	// if (!path)
	// 	return ;
	
	// tmp = commands

	// read from infile if there is one
	int last_fd=STDIN_FILENO;

	while(tmp)
	{
		tmp_command=(t_command*)tmp->content;
		
		if(pipe(fds)==-1)
			print_cmd_error(tmp_command->cmd, strerror(errno),1, STDERR_FILENO);
		
		pid = fork();
		if(!pid)//child process
		{
			get_inputfile_fd(&last_fd,tmp_command->redir_in);


			if(!(tmp_command->cmd))
				exit(0);
			path = get_actual_path(tmp_command->cmd, tmp_command);
			dup2(last_fd,STDIN_FILENO);
			if (tmp->next)
				dup2(fds[1],STDOUT_FILENO);
			close(fds[0]);
			if(execve(path,tmp_command->args,envs)==-1)
				exit(1);
		}
		else
		{
			last_fd = fds[0];
			close(fds[1]);
			tmp=tmp->next;
		}
	}
	if (commands)
	{
		close(fds[1]);
		close(fds[0]);
		waitpid(pid,NULL,0);
	}
	
	//printf("hello");
	exit(0);
}
