// [ pizza program ]


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <signal.h>
#include <linux/input.h>

#include "order.h"
//#define INPUTPATH "/dev/input/event8"

int main(int argc, char** argv)
{
	int pizzafd = -1,
	    readlen = 0,
	    conffd = open("/etc/pizzad.conf", O_RDONLY);
	struct input_event iev;
	off_t conflen;
	char* confstr;

	signal(SIGCHLD, SIG_IGN);

	if (conffd < 0)
	{
		fprintf(stderr, "Could not open file: %s\n", strerror(errno));
		return 1;
	}

	conflen = lseek(conffd, 0, SEEK_END);
	if(conflen < 0)
	{
		fprintf(stderr, "Could not seek to end: %s\n", strerror(errno));

		close(conffd);
		return 1;
	}
	if(lseek(conffd, 0, SEEK_SET) < 0)
	{
		fprintf(stderr, "Could not seek back from end to the start: %s\n", strerror(errno));

		close(conffd);
		return 1;
	}
	confstr = malloc(conflen+1);
	memset(confstr, 0, conflen+1);
	if(read(conffd, confstr, conflen) != conflen)
	{
		fprintf(stderr, "Could not read conf: %s\n", strerror(errno));

		free(confstr);
		close(conffd);
		return 1;
	}
	confstr[conflen] = 0;

	for (int i = 0; i < conflen; i++)
	{
		if (confstr[i] == '\n' || confstr[i] == '\r') {
			confstr[i] = 0;
			break;
		}
	}

	pizzafd = open(confstr, O_RDONLY);
	if (pizzafd < 0)
	{
		fprintf(stderr, "Could not open input file: %s\n", strerror(errno));

		free(confstr);
		close(conffd);
		return 1;
	}

	while(
		(readlen = read(pizzafd, &iev, sizeof(struct input_event))) == sizeof(struct input_event)
	)
	{
		//printf("type: %d, code: %d, value: %d\n", iev.type, iev.code, iev.value);
		if(iev.type == EV_KEY && iev.code == KEY_CALC)
		{
			if(iev.value == 0)
			{
				printf("Pizza.\n");
				int ret = placePizza();
				if(ret != 0)
				{
					fprintf(stderr, "placePizza failed! ret: %d\n", ret);
				}
				fflush(stdout);
			}
		}
	}

	free(confstr);
	close(conffd);
	close(pizzafd);

	return 0;
}
