#include "../minishell.h"
t_command	*init_command()
{
	t_command	*data;
	int			redi;

	data = malloc(sizeof(t_command) * 1);
	data->envs = getenv("PATH");
	data->paths = ft_split(data->envs, ':');
	data->cmd = "grep";
	data->args = ft_split("grep h", ' ');
	redi = 0;
	//data->cmd=ft_lstadd_back(&data->commands,ft_lstnew("ls"));
	return (data);
}
char	*get_right_path(char *cmd, t_command *data)
{
	int		i;
	char	*absolute_path;

	i = 0;
	absolute_path = NULL;
	cmd = ft_strjoin("/", cmd);
	while (data->paths[i])
	{
		absolute_path = ft_strjoin(data->paths[i], cmd);
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
void	executer(t_command *command,char **envs)
{	
	command = init_command();
	char *path = get_actual_path(command->cmd, command);
	if (!path)
		printf("error\n");
	int id = execve(path, command->args, envs);
    
}