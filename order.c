// [ pizza program ]


// handles ordering
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <systemd/sd-login.h>

#include "order.h"

int placePizza()
{
	char *s0a_session = NULL;
	uid_t s0a_uid;
	int s0a = sd_seat_get_active("seat0", &s0a_session, &s0a_uid);

	if (s0a < 0)
	{
		fprintf(stderr, "Could not get session on seat: %s\n", strerror(-s0a));
		return 1;
	}
	printf("UID: %d\n", s0a_uid);

	free(s0a_session);

	pid_t forkPID = fork();
	if (forkPID == 0)
	{
		if(setuid(s0a_uid) != 0)
		{
			fprintf(stderr, "Failed UID change to %d: %s\n", s0a_uid, strerror(errno));
			exit(1);
		}

		printf("Running as child\n");

		char xrd[128] = {0};
		snprintf(xrd, 127, "XDG_RUNTIME_DIR=/run/user/%d", s0a_uid);

		char *env[] = { xrd, "WAYLAND_DISPLAY=wayland-0", "DISPLAY=:0", (char *)NULL };
		execle("/usr/bin/firefox", "firefox", "https://www.google.com/search?q=pizza+near+me", (char *)NULL, env);

		fprintf(stderr, "execle failed?\n");
		exit(0);
	} else if (forkPID == -1)
	{
		fprintf(stderr, "Failed fork.\n");
	}

	return 0;
}

#ifdef ORDERTEST
int main(int argc, char** argv)
{
	placePizza();
}
#endif
