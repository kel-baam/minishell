/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:30:15 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/03 10:30:19 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_command* read_cmds(t_command *data,char **av ,int ac)
// {
//     int i;
//     i=1;
//     data->cmds=malloc(sizeof(char)*ac);
//     while(i<ac)
//     {
//         data->cmds[i]=malloc(ft_strlen(av[i]));
//         data->cmds[i]=av[i];
//         i++;
//     }
//     return (data);
// }
void	print_cmd_error(char *cmd, char *msg_err, int status_code,
		int output_fd)
{
	char	*my_shell;

	my_shell = "my_shell";
	write(output_fd, my_shell, ft_strlen(my_shell));
	write(output_fd, ": ", 2);
	write(output_fd, cmd, ft_strlen(cmd));
	write(output_fd, ": ", 2);
	write(output_fd, msg_err, ft_strlen(msg_err));
	write(output_fd, "\n", 1);
	exit(status_code);
} 

void	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
		{
			free(ptr[i]);
			ptr[i] = NULL;
			i++;
		}
		free(ptr);
	}
}
int	find_char(char *str,char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}
