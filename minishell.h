/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:31:33 by kel-baam          #+#    #+#             */
/*   Updated: 2023/05/03 10:31:36 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <unistd.h>
# define TABLE_SIZE 1024

typedef struct t_list
{
	void			*content;
	struct t_list	*next;

}					t_list;
// typedef struct s_pair
// {
// 	char			*key;
// 	char			*value;
// }					t_pair;
typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node   *parent;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;
typedef struct t_red
{
	void			*file_name;
	int flag; //1 if red out 0 if red out  append
		// struct t_red *next;
}					t_red;

typedef struct s_command
{
	char			*cmd;
	char			**args;
	t_list			*redir_in;
	t_list			*redir_out;
	int				status;
	//int herdoc;         //flag for exestence of herdoc <<
	//char *herdoc_delim; // delimiter of herdoc
	//int append_redi;    // flag redirection >>
}					t_command;

typedef struct s_data
{
	t_node			*env_vars;
	int				total_envs;
	int				status;

}					t_data;

t_data				g_data;
t_command			*read_cmds(t_command *data, char **av, int ac);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				**ft_split(char const *s, char c);
t_list				*ft_lstlast(t_list *lst);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstnew(void *content);
char				*ft_strchr(const char *s, int c);
void				print_cmd_error(char *cmd, char *msg_err, int status_code,
						int output_fd);
void				executer(t_list *command, char **envs);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_list				*init_commands();
char				*get_actual_path(char *cmd, t_command *data, char **envs);
void				free_double_ptr(char **ptr);
char				*get_env();
void				initilizer(char **envs);
void				init_envs(char **envs);
void				ft_env(void);
int					find_char(char *str, char c);
void				add_node(t_node **head, char *key, char *value,t_node *parent);
void				inorder_traversal(t_node *head);
void			remove_node(t_node **head, char *key);
void free_node(t_node **node);
void ft_free(void *ptr);
void printBST(t_node* root, int isRightChild, int depth);
#endif
