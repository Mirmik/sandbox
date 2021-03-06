#ifndef GENOS_MSGOPS_H
#define GENOS_MSGOPS_H

#include "service.h"

struct iovec {
	void* data;
	size_t size;
};

__BEGIN_DECLS

struct g0_message* g0_alloc_message();
void g0_dealloc_message(struct g0_message* msg);

g0id_t g0_send(g0id_t sender, g0id_t receiver, const void* data, size_t size);
g0id_t g0_sendv(g0id_t sender, g0id_t receiver, struct iovec* vec);

__END_DECLS

#endif