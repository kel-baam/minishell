#include "../minishell.h"

t_red *generatFile(char *file_name,int flag)
{
	t_red *red= malloc(sizeof(t_red));
	red->file_name = ft_strdup(file_name);
	red->flag = flag;
	return red;
}

t_command *generateCommand(char *cmd, char *args, char *inFile,char *outfile,int flag)
{
	t_command	*command;
	command = calloc(sizeof(t_command),1);
	command->cmd = cmd;
	if(args)
		command->args = ft_split(args, ' ');
	if (inFile)
		ft_lstadd_back(&(command->redir_in),ft_lstnew(ft_strdup(inFile)));
	if(outfile)
		ft_lstadd_back(&(command->redir_out),ft_lstnew(generatFile(outfile,flag)));
	return command;

}

t_list	*init_commands()
{
 	t_list *commands = NULL;
	ft_lstadd_back(&commands,ft_lstnew(generateCommand("ls","ls", NULL,NULL,1)));
	ft_lstadd_back(&commands,ft_lstnew(generateCommand("cat","cat",NULL,NULL,0)));
	return commands;
}

void ft_env()
{
	int i=0;
	t_list *tmp;
	t_pair *tmp_pair;
	while(i<TABLE_SIZE)
	{
		tmp=g_data.env_vars[i];
		while(tmp)
		{
			tmp_pair=(t_pair*)tmp->content;
			printf("-----%s=%s\n",tmp_pair->key,tmp_pair->value);
			tmp=tmp->next;
		}
		i++;
	}
}