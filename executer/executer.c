#include "../minishell.h"
t_command	*init_command()
{
	t_command	*command;
	command = malloc(sizeof(t_command) * 1);
	command->cmd = "echo";
	command->args = ft_split("echo hello 1337", ' ');
	command->redi_out=1;
	command->redi_in=1;
	command->append_redi=1;
	command->herdoc_delim="end";
	command->infile=ft_split("test.txt test2.txt test3.txt", ' ');
	command->outfile=ft_split("test.txt test3.txt test2.txt", ' ');
	

	return (command);
}
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
void  redirection_output(t_command *command,char *path,char **envs)
{
	int i;
	int fd;
	
	i=0;
	fd=-1;
	while(command->outfile[i])
	{
		if(fd!=-1)
			close(fd);
		fd=open(command->outfile[i],O_WRONLY | O_CREAT | O_TRUNC ,0644);
		// protection fd==-1
		i++;
	}
		dup2(fd,STDOUT_FILENO);
		execve(path, command->args, envs);
}
void  redirection_input(t_command *command,char *path,char **envs)
{
	int i;
	int fd;

	i=0;
	fd =-1;
	while(command->infile[i])
	{
		if(fd!=-1)
			close(fd);
		fd=open(command->infile[i],O_RDONLY  ,0644);
		// protection fd==-1
		i++;
	}
		dup2(fd,STDIN_FILENO);
		execve(path, command->args, envs);
}
void  redirection_output_append(t_command *command,char *path,char **envs)
{
	int i;
	int fd;

	i=0;
	fd =-1;
	while(command->outfile[i])
	{
		if(fd!=-1)
			close(fd);
		fd=open(command->outfile[i],O_WRONLY,O_APPEND);
		// protection fd==-1
		i++;
	}
		dup2(fd,STDOUT_FILENO);
		execve(path, command->args, envs);
	
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

void	executer(t_command *command,char **envs)
{	
	command = init_command();
	char *path = get_actual_path(command->cmd, command);
	if (!path)
		printf("error\n");
	//if(command->redi_in==1)
		//redirection_input(command,path,envs);
	//if(command->redi_out==1)
		//redirection_output(command,path,envs);
	//if(command->append_redi==1)
		//redirection_output_append(command,path,envs);
	redirection_herdoc(command);
	exit(0);
}