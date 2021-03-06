#ifndef INPLEMETATIONS_OF_EVENT_QUEUE_WATCHER_H
#define INPLEMETATIONS_OF_EVENT_QUEUE_WATCHER_H

#include "event_queue.h"

/* alarm a signal(with siginfo->value settled) to the process
 * when nr_events exceed limit + toler */
struct equeue_signal_watcher {
	int signo;
	int limit[2];	 /* up to upper, or down to lower; if unwatch, set to -1 */
	int dylimit_inc; /* increase dylimit by dylimit_inc each time */
	int dylimit_max; /* but can't exceed dylimit_max; or unlimited(-1) */
	/* datas */
	/* dynamic added to limit, avoiding alarming again in a short time once over limit */
	int dylimit;
};

#define EQUEUE_FULL_WATCHER(sig, ulimit, inc, max)			\
	{ .signo = sig,	.limit = { -1, ulimit }, .dylimit_inc = inc, .dylimit_max = max, }

#define EQUEUE_EMPTY_WATCHER(sig)					\
	{ .signo = sig,	.limit = { 0, -1 }, .dylimit_inc = 0, .dylimit_max = -1, }
	
void equeue_signal_watcher_cb(void* data, int nr_events, int change);

#endif


