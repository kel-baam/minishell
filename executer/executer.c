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


void  get_outfile_fd(int *fd,t_list *file_list)
{
	t_list *tmp=file_list;
	t_red *tmp_redir;
	while(tmp)
	{
		tmp_redir = (t_red*) tmp->content;
		if(tmp_redir->flag)
			*fd=open(tmp_redir->file_name,O_WRONLY | O_CREAT | O_TRUNC ,0644);
		else
			*fd=open(tmp_redir->file_name,O_WRONLY | O_CREAT | O_APPEND ,0644);
		if(*fd==-1)
			print_cmd_error(tmp_redir->file_name, strerror(errno),1, STDERR_FILENO);
		if(tmp->next && *(fd)!=STDOUT_FILENO)
			close(*fd);
		tmp=tmp->next;
	}
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
void ft_pwd(char *cmd)
{
	char buff[1024];
	if(!getcwd(buff,sizeof(buff)))
		print_cmd_error(cmd,strerror(errno),1,STDERR_FILENO);
}

void store_status_code(int status)
{
	t_list *tmp;
	while(tmp)
	{
		g_data.status=status;
		tmp=tmp->next;
	}

}



void	executer(t_list *commands,char **envs)
{	
	char *path;
	int fds[2];
	t_list *tmp;
	tmp=commands;
	int fd[1024];
	int pidd[1000];
	int i=0;
	t_command *tmp_command;
	int pid;
	//last_fd means where we can read
	int last_fd=STDIN_FILENO;
	while(tmp)
	{
		tmp_command=(t_command*)tmp->content;
		
		if(pipe(fds)==-1)
			print_cmd_error(tmp_command->cmd, strerror(errno),1, STDERR_FILENO);
		
		pid = fork();
		if(!pid)
		{
			get_inputfile_fd(&last_fd,tmp_command->redir_in);
			get_outfile_fd(&fds[1],tmp_command->redir_out);
			//
			if(!(tmp_command->cmd))
				exit(0);
			//get_path
			path = get_actual_path(tmp_command->cmd, tmp_command,envs);
			if(!path)
				print_cmd_error(tmp_command->cmd," command not found",1,STDERR_FILENO);
			// if there a file to read or if there is a pipe
			if(last_fd!=STDIN_FILENO)
			{
				dup2(last_fd,STDIN_FILENO);
				close(last_fd);
			}
			if (tmp->next || tmp_command->redir_out)
				dup2(fds[1],STDOUT_FILENO);
			close(fds[1]);
			close(fds[0]);
			if(execve(path,tmp_command->args,envs)==-1)
				exit(1);
		}
		else
		{
			pidd[i]=pid;
			fd[i]=fds[0];
			last_fd = fds[0];
			tmp=tmp->next;
			close(fds[1]);
			i++;
		}
	}
	int j=0;
	int status;
	if (commands)
	{

		while(j<i)
		{
			close(fd[j]);
			waitpid(pidd[j],&status,0);
			store_status_code(WEXITSTATUS(status));
			j++;
		}
	}
}
