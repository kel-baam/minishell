#ifndef MINI_H
# define MINI_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <unistd.h>
#include <readline/readline.h>
typedef struct t_list
{
	void			*content;
	struct t_list	*next;

}					t_list;
typedef struct s_command
{
	char			*cmd; 
	char			**args;
	int				redi_out;// flag > 
	int				redi_in; //flag <
	int 			herdoc; //flag for exestence of herdoc <<
	char            *herdoc_delim ;// delimiter of herdoc
	int				append_redi; // flag redirection >>
	char			**outfile; // 
	char			**infile;

}					t_command;
typedef struct s_executer
{
	t_list *herdoc_content;

}t_executer;
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
void	executer(t_command *command,char **envs);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
#endif