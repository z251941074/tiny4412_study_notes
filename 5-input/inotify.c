
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/inotify.h>
#include <sys/ioctl.h>
#include <sys/utsname.h>
#include <unistd.h>

int process_inotifyevents (int mInotifyFd) {
	
	int res;
    char devname[PATH_MAX];
    char *filename;
    char event_buf[512];
    int event_size;
    int event_pos = 0;
    struct inotify_event *event;

    //printf("mInotifyFd: %d\n", mInotifyFd);
    res = read(mInotifyFd, event_buf, sizeof(event_buf));
	
    if(res < (int)sizeof(*event)) {
        printf("could not get event\n");
        return -1;
    }
	
    while(res >= (int)sizeof(*event)) {
        event = (struct inotify_event *)(event_buf + event_pos);
        printf("%d: %08x \"%s\"\n", event->wd, event->mask, event->len ? event->name : "");
        if(event->len) {
            if(event->mask & IN_CREATE) {
                printf("event->name:%s Creat\n", event->name);
            } else {
                printf("event->name:%s Delete\n", event->name);
            }
        }
        event_size = sizeof(*event) + event->len;
        res -= event_size;
        event_pos += event_size;
    }
    return 0;
}
int main() {
	
	int mInotifyFd = inotify_init();
	
	int result = inotify_add_watch(mInotifyFd, "/home/dream/samba/code/AndroidL/input/2", IN_DELETE | IN_CREATE);
	
	while(1) {
		process_inotifyevents(mInotifyFd);
	}
}