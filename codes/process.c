#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int pid;
	int ppid;
	pid = getpid();
	ppid = getppid();
	printf("pid is %d\n",pid);
	printf("ppid is %d\n",ppid);
	return 0;
}
