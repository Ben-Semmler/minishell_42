#include "minishell.h"

int	get_arg_size(char *input, bool include_interpret, int returnval)
{
	int		len;
	bool	interpret;
	int		adjust;
	char	quotations;
	char	prev_quotations;
	int		env_len;

	len = 0;
	interpret = true;
	env_len = 0;
	adjust = 0;
	quotations = 0;
	while (input[len] && (quotations != 0 || input[len] != ' '))
	{
		if (input[len] == 39)
			interpret = !interpret;
		if (input[len] == '$' && interpret)
		{
			if (input[len + 1] == '?')
			{
				len += 2;
				env_len += (int)ft_strlen(ft_itoa(returnval)) - 2;
			}
			else
			{
				len++;
				env_len += ft_strlen(search(get_key(&input[len])).data);
				env_len -= ft_strlen(get_key(&input[len])) + 1;
				len += ft_strlen(get_key(&input[len]));
				if (include_interpret)
					env_len -= 2;
			}
		}
		else
		{
			prev_quotations = quotations;
			quotations = check_quotations(input[len], quotations);
			if (prev_quotations != quotations)
				adjust++;
			len++;
		}
	}
	if (include_interpret)
		return (len);
	return (len + env_len - adjust);
}
