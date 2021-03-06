#ifndef G0_SERVICE_H
#define G0_SERVICE_H

#include <gxx/datastruct/dlist_head.h>
#include "id_table.h"

typedef uint32_t g0id_t;
struct g0_message;
struct g0_service;

struct g0_message {
	struct dlist_head qlnk; //к листу входящих сервиса.
	g0id_t qid;				//ид сообщения. хэш таблицы сообщений.
	
	g0id_t sid; 			//ид отправителя.
	g0id_t rid;				//ид получателя.

	void* data;
	size_t size;

	union {
		struct {
			uint8_t repled : 1;
			uint8_t noreply : 1;
		};
		uint8_t stsbyte;
	};
};

struct g0_service_operations {
	void (*on_input)(struct g0_service*, struct g0_message*);
	void (*on_reply)(struct g0_service*, struct g0_message*);
};

struct g0_service {
	struct hlist_node hlnk;		//к таблице сервисов.
	g0id_t id;					//ид. хэш таблицы сервисов.
	const struct g0_service_operations* service_ops;
};

__BEGIN_DECLS

g0id_t g0_init_service(struct g0_service* srv);
g0id_t g0_init_message(struct g0_message* srv);
void g0_init();
void g0_utilize_message(struct g0_message* msg);

uint8_t g0_transport_send(struct g0_message* msg);
uint8_t g0_transport_reply(struct g0_message* msg);

__END_DECLS

#endif