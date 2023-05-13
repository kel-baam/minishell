#include "../minishell.h"

unsigned int	hash(char *name)
{
	unsigned long int	value;
	unsigned int		i;
	unsigned int		key_len;

	value = 0;
	i = 0;
	key_len = strlen(name);
	while (i < key_len)
	{
		value = value + name[i];
		i++;
	}
	value = value % TABLE_SIZE;
	return (value);
}

t_pair	*new_pair(char *key, char *value)
{
	t_pair	*pair;

	pair = malloc(sizeof(t_pair));
	pair->key = ft_strdup(key);
	pair->value = ft_strdup(value);
	return (pair);
}

void	set_env(char *key, char *value)
{
	t_list			**env_vars;
	unsigned int	index;
	t_pair			*pair;
	t_list			*envs_list;

	env_vars = g_data.env_vars;
	index = hash(key);
	envs_list = env_vars[index];
	while (envs_list)
	{
		pair = (t_pair *)envs_list->content;
		if (!strcmp(pair->key, key))
		{
			free(pair->value);
			pair->value = ft_strdup(value);
			return ;
		}
		envs_list = envs_list->next;
	}
	ft_lstadd_back(&(env_vars[index]), ft_lstnew(new_pair(key, value)));
}

// char	*get_env()
// {
// 	int		i;
// 	t_pair	*hash;

// 	i = 0;
// 	while (i < TABLE_SIZE)
// 	{
// 		hash = (t_pair *)envs->content;
// 		if (!envs)
// 		{
// 			i++;
// 			continue ;
// 		}
// 		while (envs)
// 		{
// 			printf("%s=%s\n", hash->key, hash->value);
// 			if (envs->next)
// 				break ;
// 			envs = envs->next;
// 		}
// 		i++;
// 	}
// }

void	init_envs(char **envs)
{
	t_list **env_vars;
	int i;
	int pos;

	env_vars = g_data.env_vars;
	i = 0;
	while (envs[i])
	{
		pos = find_char(envs[i], '=');
		set_env(ft_substr(envs[i], 0, pos), ft_substr(envs[i], pos + 1,
					ft_strlen(envs[i])));
		i++;
	}
}