#ifndef __L2STATS_H
#define __L2STATS_H

typedef sample_size_t unsigned long;
typedef sample_t float;

struct stats_struct {
	sample_size_t sample_size;
	sample_t mean;
	sample_t variance;
};

struct stats_struct *stats_struct_new();
void stats_struct_feed(struct stats_struct *ss, sample_t sample);
void stats_struct_destroy(struct stats_struct* ss);

#endif /* __L2STATS_H */