#define _GNU_SOURCE /*for CPU_SET*/
#include <linux/ethtool.h>
#include <linux/net_tstamp.h>
#include <poll.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

static int running = 1;

static int run_realtime_function()
{
	while (running) {
		//Do your operation
	}
	return 0;
}

static int set_realtime(pthread_t thread, int priority)
{
	struct sched_param sp;
	int err, policy;

	int min = sched_get_priority_min(SCHED_FIFO);
	int max = sched_get_priority_max(SCHED_FIFO);

	fprintf(stderr, "min %d max %d\n", min, max);

	if (priority < 0) {
		return 0;
	}

	err = pthread_getschedparam(thread, &policy, &sp);
	if (err) {
		fprintf(stderr, "pthread_getschedparam: %s\n", strerror(err));
		return -1;
	}

	sp.sched_priority = priority;

	err = pthread_setschedparam(thread, SCHED_FIFO, &sp);
	if (err) {
		fprintf(stderr, "pthread_setschedparam: %s\n", strerror(err));
		return -1;
	}
	return 0;
}

static void program_usage(char *progname)
{
	fprintf(stderr,
		"\n"
		"usage: %s [options]\n"
		"\n"
		" -p [num]   run with RT priorty 'num'\n",
		progname, DEFAULT_DELAY, DEFAULT_PERIOD);
}

int main(int argc, char *argv[])
{
	int c, priority = -1;
	char *progname;

	/* Process the command line arguments. */
	progname = strrchr(argv[0], '/');
	progname = progname ? 1 + progname : argv[0];
	while (EOF != (c = getopt(argc, argv, "p"))) {
		switch (c) {
		case 'p':
			priority = atoi(optarg);
			break;
		case '?':
			program_usage(progname);
			return -1;
		}
	}

	if (set_realtime(pthread_self(), priority)) {
		return -1;
	}

	err = run_realtime_function();

	return err;
}
