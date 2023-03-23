#include <unistd.h>
#include <stdio.h>


int main(int argc, char **argv)
{
	int i;

	while (1) {

        i = getsid(0);
        fprintf(stdout, "%d\n", i);
        sleep(1);
	}

	return 0;
}
