#include "../minishell.h"
t_command	*init_command()
{
	t_command	*command;
	command = malloc(sizeof(t_command) * 1);
	command->cmd = "grep";
	command->args = ft_split("grep k", ' ');
	command->redi_out=1;
	command->redi_in=1;
	command->infile="infile.txt";
	command->outfile="out";
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
void  redirection_output(t_command *command)
{
	int fd=open(command->outfile,O_CREAT| O_RDWR|O_TRUNC,0644);
	
		dup2(fd,STDOUT_FILENO);
}
void  redirection_input(t_command *command)
{
	int fd=open(command->infile, O_RDONLY,0644);
	if(fd<0)
		 print_cmd_error(command->infile,strerror(errno),127,2);
		dup2(fd,STDIN_FILENO);
}
void	executer(t_command *command,char **envs)
{	
	command = init_command();
	char *path = get_actual_path(command->cmd, command);
	if (!path) 
		printf("error\n");
	if(command->redi_in==1)
		redirection_input(command);
	int id = execve(path, command->args, envs);
}