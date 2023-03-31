/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:35:45 by kel-baam          #+#    #+#             */
/*   Updated: 2023/03/26 14:35:48 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini.h"

t_data *init_data()
{
	t_data *data = malloc(sizeof(t_data) * 1);
	data->envs=getenv("PATH");
	data->paths=ft_split(data->envs,':');
	data->cmd="grep";
	data->args = ft_split("grep h",' ');
	int redi=0;
	//data->cmd=ft_lstadd_back(&data->commands,ft_lstnew("ls"));
	return data; 
}
char *get_right_path(char *cmd,t_data *data)
{
	int i;
	i=0;
	char *absolute_path=NULL;
	cmd =ft_strjoin("/",cmd);
	while(data->paths[i])
	{
		absolute_path=ft_strjoin(data->paths[i],cmd);
		if (!access(absolute_path, F_OK | X_OK))
			break;
		free(absolute_path);
		absolute_path=NULL;
		i++;
	}
	return absolute_path;
}

char	*get_actual_path(char *cmd, t_data *data)
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
// void out_put_redirection(t_data *data)
// {
// 	open 
// }
int	main(int ac, char **av,char **envs)
{
	t_data *data;
	data=init_data();
	char *path=get_actual_path(data->cmd,data);
	if(!path)
		printf("error\n");
	int id=execve(path,data->args,envs);
	return (0);
}