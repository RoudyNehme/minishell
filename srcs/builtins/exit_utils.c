#include "../../includes/minishell.h"

void	cleanup(char *line, t_token *tokens, t_cmd *cmds, t_shell *shell)
{
    int	i;

    if (line)
        free(line);
    if (tokens)
        free_tokens(tokens);
    if (cmds)
        free_cmds(cmds);
    if (shell && shell->envp)
    {
        i = 0;
        while (shell->envp[i])
            free(shell->envp[i++]);
        free(shell->envp);
    }
    rl_clear_history();
}
