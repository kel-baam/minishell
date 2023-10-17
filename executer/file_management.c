/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:36:11 by kel-baam          #+#    #+#             */
/*   Updated: 2023/10/17 18:01:49 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_outfile_fd(t_list *lst_redir, int *fd, int *is_out)
{
	t_red	*tmp_redir;
	int		tmp_fd ;

	*is_out = 1;
	tmp_fd = *fd;
	tmp_redir = (t_red *)(lst_redir->content);
	if (tmp_redir->flag == 3)
	{
		if (((char *)tmp_redir->file_name)[0] == '$')
			return (print_cmd_error(tmp_redir->file_name, NULL,
					"ambiguous redirect", 1));
		*fd = open(tmp_redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (tmp_redir->flag == 2)
		*fd = open(tmp_redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
		return (print_cmd_error(tmp_redir->file_name, NULL, strerror(errno),
				1));
	if (tmp_fd != STDOUT_FILENO)
		close(tmp_fd);
	return (0);
}

int	get_inputfile_fd(t_list *lst_redir, int *last_fd)
{
	t_red	*tmp;
	int		tmp_fd;

	tmp_fd = *last_fd;
	tmp = (t_red *)lst_redir->content;
	if (((char *)tmp->file_name)[0] == '$' && tmp->flag == 1)
		return (print_cmd_error(tmp->file_name, NULL, "ambiguous redirect", 1));
	if (tmp->flag == 1)
		*(last_fd) = open(tmp->file_name, O_RDONLY, 0644);
	if (*(last_fd) == -1)
		return (g_data.status_code = print_cmd_error(tmp->file_name, NULL,
				strerror(errno), 1));
	if (!tmp->flag)
		*last_fd = tmp->fd_herdoc;
	if (tmp_fd != STDIN_FILENO)
		close(tmp_fd);
	return (0);
}

void	get_fds(t_list *lst_files, int *read_fd, int *write_fd, int *is_out)
{
	t_list	*tmp_redir;
	t_red	*tmp;

	tmp_redir = lst_files;
	while (tmp_redir)
	{
		tmp = (t_red *)tmp_redir->content;
		if (!tmp->flag || tmp->flag == 1)
		{
			if (get_inputfile_fd(tmp_redir, read_fd) == 1)
				exit(g_data.status_code);
		}
		if (tmp->flag == 2 || tmp->flag == 3)
		{
			if (get_outfile_fd(tmp_redir, write_fd, is_out) == 1)
				exit(g_data.status_code);
		}
		tmp_redir = tmp_redir->next;
	}
}

void	duplicate_fds(t_list *tmp, int last_fd, int *fds, int is_out)
{
	if (last_fd != STDIN_FILENO)
	{
		dup2(last_fd, STDIN_FILENO);
		close(last_fd);
	}
	if (tmp->next || (fds[1] != STDOUT_FILENO && is_out == 1))
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		close(fds[0]);
	}
}
