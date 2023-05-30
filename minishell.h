/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:31:33 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/30 19:45:33 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/history.h>
# include "parser/token.h"
// in
typedef struct t_list
{
	void *content;
	struct t_list *next;

}					t_list;
// out
typedef struct s_red
{
	char			*file_name;
	int				flag; //1 if red out 0 if red append
}					t_red;

typedef struct s_command
{
	char			*cmd;
	char			**args;
	t_list			*redir_in;
	t_list			*redir_out;
}					t_command;

// typedef struct s_data
// {
// 	t_node			*env_vars;
// 	int				total_envs;
// 	int				status;

// }					t_data;

// t_data				g_data;
t_command			*read_cmds(t_command *data, char **av, int ac);
char				*ft_substr(char const *s, unsigned int start, size_t len);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strchr(const char *s, int c);
int					print_cmd_error(char *cmd,char *args,char *msg_err, int status_code);
void				executer(t_list *command, char **envs);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_list				*init_commands();
char				*get_actual_path(char *cmd, t_command *data);
int					ft_atoi(const char *str);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstnew(void *content);
char				*ft_strchr(const char *s, int c);
int					ft_strchr_str(char *str, char *c);
#endif
