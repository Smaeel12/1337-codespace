#include "pipex.h"

int main()
{
	int pipefds[2];
	char buf[100];
	int nb;

	if (pipe(pipefds) == -1)
		return 0;
	read(pipefds[1], buf, 100);
	buf[nb] = '\0';

	// nb = read(pipefds[0], buf, 100);
	// buf[nb] = '\0';
	// printf("%s\n", buf);w
}
