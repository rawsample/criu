#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/syscall.h>

#include <compel/log.h>
#include <compel/infect.h>


static void print_vmsg(unsigned int lvl, const char *fmt, va_list parms)
{
	printf("\tLC%u: ", lvl);
	vprintf(fmt, parms);
}


int main(int argc, char **argv)
{
	int pid;
	int state;
	long ret;
	struct parasite_ctl *ctl;


    setvbuf(stdout, NULL, _IONBF, 0);

	pid = vfork();
	if (pid == 0) {
		execl("./victim", "victim", NULL);
        printf("fail to launch victim program\n");
		exit(1);
	}

    printf("Parent pid: %d\n", getpid());
    printf("Child pid:  %d\n", pid);
    printf("Parent sid: %d\n", getsid(0));
    printf("Child sid:  %d\n", getsid(pid));

    sleep(1);

	compel_log_init(print_vmsg, COMPEL_LOG_DEBUG);


	printf("Stopping task\n");
	state = compel_stop_task(pid);
	if (state < 0) {
		printf("Error: Can't stop task");
        kill(pid, 9);
        return -1;
    }

    //getchar();

	printf("Preparing parasite ctl\n");
	ctl = compel_prepare(pid);
	if (!ctl) {
		printf("Can't prepare for infection");
        kill(pid, 9);
        return -1;
    }

    //getchar();

    printf("Remote getpid...\n");
	ret = -1000;
	if (compel_syscall(ctl, __NR_getpid, &ret, 0, 0, 0, 0, 0, 0) < 0) {
		printf("Can't run rgetpid");
        kill(pid, 9);
        return -1;
    }

	printf("Remote getpid returned %ld\n", ret);
	if (ret != pid) {
		printf("Pid mismatch!");
        kill(pid, 9);
        return -1;
    }


    printf("Remote getsid...\n");
	ret = -1000;
	if (compel_syscall(ctl, __NR_setsid, &ret, 0, 0, 0, 0, 0, 0) < 0) {
		printf("Can't run rsetsid");
        kill(pid, 9);
        return -1;
    }
	printf("Remote setsid returned %ld\n", ret);


	printf("Curing\n");
	if (compel_cure(ctl)) {
		printf("Can't cure victim");
        kill(pid, 9);
        return -1;
    }

	if (compel_resume_task(pid, state, state)) {
		printf("Can't unseize task");
        kill(pid, 9);
        return -1;
    }

    kill(pid, 9);

	printf("Done\n");
	return 0;
}
