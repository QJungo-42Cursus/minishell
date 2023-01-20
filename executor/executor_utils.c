#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	fork1()
{
	int pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	close_all_pipes(int *fds, int pipe_count)
{
	int i = 0;
	while (i < pipe_count * 2)
	{
		close(fds[i]);
		i++;
	}
}

int pipe_index(int i, int read)
{
	return (i * 2 + read);
}
