#include "../minishell.h"


char	*get_right_path(char *cmd, t_command *data)
{
	int		i;
	char	*absolute_path;
	char *envs;
	char **paths;

	i = 0;
	envs=getenv("PATH");
	paths = ft_split(envs, ':');
	absolute_path = NULL;
	cmd = ft_strjoin("/", cmd);
	while (paths[i])
	{
		absolute_path = ft_strjoin(paths[i], cmd);
		if (!access(absolute_path, F_OK | X_OK))
			break ;
		free(absolute_path);
		absolute_path = NULL;
		i++;
	}
	
	return (absolute_path);
}

char	*get_actual_path(char *cmd, t_command *data)
{
	int	status;

	if (ft_strchr(cmd, '/'))
	{
		status = 127;
		if (!access(cmd, F_OK))
		{
			if (!access(cmd, X_OK))
				return (ft_strdup(cmd));
			status = 126;
		}
		print_cmd_error(cmd, strerror(errno), status, STDERR_FILENO);
	}
	
	return (get_right_path(cmd, data));
}

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

int get_inputfile_fd(t_command *command)
{
	int i;
	int fd;
	t_list *tmp;

	fd=STDIN_FILENO;
	tmp=command->redir_in;

	while(tmp)
	{
		fd=open(tmp->content,O_RDONLY ,0644);
		if(fd==-1)
			print_cmd_error(tmp->content, strerror(errno),1, STDERR_FILENO);
		if(tmp->next && fd)
			close(fd);
		tmp=tmp->next;
	}
	return fd;
}

void execute_command(t_command *command,char *path,char **envs)
{
	int infile_fd=get_inputfile_fd(command);
	int outfile_fd=get_outfile_fd(command);
	dup2(infile_fd,STDIN_FILENO);
    dup2(outfile_fd,STDOUT_FILENO);
	execve(path,command->args,envs);

}
void redirection_herdoc(t_command *command)
{
    t_list *data=NULL;// herdoc fonction i didn't store the given result of this fonction in the principal struct  
	t_list *tmp;
	data=tmp;
    char *line;
    while(1)
    {
		line=readline("> ");
        if(!ft_strncmp(command->herdoc_delim,line,ft_strlen(command->herdoc_delim)))
			break;
      	tmp->content=line;
        tmp->next = ft_lstnew(NULL);
        tmp = tmp->next;
	}
}

void	executer(t_command *commands,char **envs)
{	
	
	char *path = get_actual_path(commands->cmd, commands);
	if (!path)
		return ;
	// tmp = commands

	// while(tmp)
	
	//pipe
	// fork
	//
	execute_command(commands,path,envs);

	exit(0);
}