#include <stdlib.h>
#include <stdio.h>

#include "l2stats.h"

struct stats_struct *stats_struct_new() {
	struct stats_struct *buf;

	if (!(buf = malloc(sizeof(struct stats_struct)))) {
		perror("Can't allocate stats struct.");
		exit(1);
	}

	buf->sample_size = 0;
	buf->mean = 0;
	buf->variance = 0;

	return buf;
}

void stats_struct_feed(struct stats_struct *ss, sample_t sample) {
	if (!ss) {
		perror("Can't feed sample to null pointer.");
		exit(1);
	}

	if (ss->sample_size == 0) {
		ss->sample_size = 1;
		ss->mean = sample;
		ss->variance = 0;
	} else {
		sample_size_t old_size = ss->sample_size;
		sample_t old_mean = ss->mean;
		sample_t old_variance = ss->variance;

		ss->sample_size++;

		/* Incrementally update the mean. */
		ss->mean = (old_mean * old_size + sample) / (old_size + 1);

		/* Incrementally update the variance. */
		ss->variance = (old_size / (sample_t) ss->sample_size) * old_variance * old_variance
			+ (1 / (sample_t) ss->sample_size) * (sample - old_mean) * (sample - old_mean);
	}
}

void stats_struct_destroy(struct stats_struct* ss) {
	if (!ss) {
		perror("Can't free null pointer.");
		exit(1);
	}

	free(ss);
}