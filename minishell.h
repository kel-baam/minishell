/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:31:33 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/03 18:13:32 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/history.h>
# include "parser/token.h"
// in
# define TABLE_SIZE 1024

typedef struct t_list
{
	void *content;
	struct t_list *next;

}					t_list;
// out

typedef struct t_red
{
	void			*file_name;
	int flag; //herdoc flag 0
}					t_red;

typedef struct s_command
{
	char			*cmd;
	char			**args;
	t_list			*redir_in;
	t_list			*redir_out;

}					t_command;



typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;


typedef struct s_data
{
	t_node			*env_vars;
	int				total_envs;
	int				status_code;
	int				count_envs;
	struct termios	newTerm;
	struct termios	oldTerm;

}					t_data;

t_data				g_data;

t_command			*read_cmds(t_command *data, char **av, int ac);
char				*ft_substr(char const *s, unsigned int start, size_t len);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);
void				executer(t_list *command, char **envs);
t_list				*init_commands();
int					ft_atoi(const char *str);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstnew(void *content);
char				*ft_strchr(const char *s, int c);
int					ft_strchr_str(char *str, char *c);
int					print_cmd_error(char *cmd,char *args, char *msg_err, int status_code);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_list				*init_commands(void);
char				*get_actual_path(char *cmd, t_command *data, char **envs);
void				free_double_ptr(char **ptr);
void				initilizer(char **envs);
void 				init_envs(char **envs);
int					ft_env(int fd);
int					find_char(char *str, char c);
void				add_node(t_node **head, char *key, char *value,
						t_node *parent);
void				inorder_traversal(t_node *head, int fd);
void				remove_node(t_node **head, char *key);
void				free_node(t_node **node);
void				ft_free(void *ptr);
int					ft_pwd(char *cmd, int fd);
int					ft_cd(t_command *command);
int					ft_echo(t_command *command);
int					ft_export(t_command *command, int fd);
int					ft_unset(t_command *command);
int					is_bultin(char *cmd);
int					execute_bultin(t_command *command, int fd);
t_node				*get_node(t_node *head, char *key);
char				*get_env(char *key);
char				*ft_itoa(int n);
int					is_valid_key(char *key);
int					ft_exit(t_command *command);
int					is_num(char *str);
char				**store_envs(t_node *head, char **tmp, int *i);
void				prompt(int sig);
void				signals_for_child(void);
void				signals_for_parent();
t_node				*get_most_left(t_node *node);
#endif
