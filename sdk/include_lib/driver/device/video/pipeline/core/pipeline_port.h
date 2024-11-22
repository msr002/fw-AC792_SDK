#ifndef __PORT_H
#define __PORT_H


#include "generic/list.h"
#include "spinlock.h"
#include "pipeline_buffer.h"
#include "message_event.h"


typedef struct pipeline_endpoint {
    struct list_head entry;
    char name[10];
    buffer_t *data_buffer;
    void *priv_data;
} pipe_endpoint_t;


typedef struct pipeline_port {
    spinlock_t lock;
    struct list_head in_endpoint;
    int   in_endpoint_num;
    struct list_head out_endpoint;
    int   out_endpoint_num;

} pipe_port_t;



pipe_port_t *port_alloc();

void port_release(pipe_port_t *port);



int port_add_input_endpoint(pipe_port_t *port, const char *prev_name);
pipe_endpoint_t *port_get_input_endpoint(pipe_port_t *port, int num);
char *port_get_input_endpoint_name(pipe_port_t *port, int num);
int port_input_endpoint_num(pipe_port_t *port);
int port_delete_input_endpoint(pipe_port_t *port, const char *prev_name);





int port_add_output_endpoint(pipe_port_t *port, const char *next_name);
pipe_endpoint_t *port_get_output_endpoint(pipe_port_t *port, int num);
char *port_get_output_endpoint_name(pipe_port_t *port, int num);
int port_output_endpoint_num(pipe_port_t *port);
int port_delete_output_endpoint(pipe_port_t *port, const char *next_name);








#endif



