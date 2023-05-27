/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:03:10 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/21 16:03:12 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

int	is_bultin(char *cmd)
{
	if (!strcmp(cmd, "pwd"))
		return (0);
	if (!strcmp(cmd, "env"))
		return (0);
	if (!strcmp(cmd, "echo"))
		return (0);
	if (!strcmp(cmd, "unset"))
		return (0);
	if (!strcmp(cmd, "export"))
		return (0);
	if (!strcmp(cmd, "cd"))
		return (0);
	if (!strcmp(cmd, "exit"))
		return (0);
	return (1);
}

int	execute_bultin(t_command *command,int outfile)
{
	if (!strcmp(command->cmd, "env"))
		return (ft_env(outfile));
	else if (!strcmp(command->cmd, "echo"))
		return (ft_echo(command));
	else if (!strcmp(command->cmd, "unset"))
		return (ft_unset(command));
	else if (!strcmp(command->cmd, "export"))
		return (ft_export(command,outfile));
	else if (!strcmp(command->cmd, "cd"))
		return (ft_cd(command));
	if (!strcmp(command->cmd, "pwd"))
		return (ft_pwd(command->cmd,outfile));
	if (!strcmp(command->cmd, "exit"))
		return ft_exit(command);
	return (0);
}

int is_valid_key(char *key)
{
	int i=0;
	while(key[i])
	{
		if ((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A' && key[i] <= 'Z'))
		i++;
		else
			return (-1);
}
return i;
} 

 int is_num(char *str)
 {
	int i=0;
	while(str[i])
	{
		if((str[i] >='0' && str[i] <= '9'))
			i++;
		else
			return -1;
	}
	return i;
 }