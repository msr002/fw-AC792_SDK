#ifndef _PIPELINE_PLUGINS_H_
#define _PIPELINE_PLUGINS_H_

#include "pipeline_port.h"

#define PLUGIN_SOURCE_ISC_BASE  (0)
#define PLUGIN_SOURCE_CSI_BASE  (2)
#define PLUGIN_SOURCE_UVC_BASE  (3)
#define PLUGIN_SOURCE_MCV_BASE  (5)
#define PLUGIN_SOURCE_VIR_BASE  (9)
#define PLUGIN_SOURCE_FILE_BASE (15)

#define PLUGIN_NAME_MAX  (32)

/* ---> UNINIT ---> INITED ----> READY ----- */
/* |                                       |    */
/* ---------- PAUSED <=======> RUNNING <----    */

enum pipeline_plugin_state {
    PLUGIN_UNINIT = 0,
    PLUGIN_INITED,
    PLUGIN_PAUSED,
    PLUGIN_READY,
    PLUGIN_RUNNING,
};

enum pipeline_plugin_type {
    PLUGIN_SOURCE = 0,
    PLUGIN_FILTER,
    PLUGIN_SINK,
};

typedef struct pipeline_plugin pipe_plugin_t;

typedef struct pipeline_plugin_ops pipe_plugin_ops;

struct pipeline_plugin {
    char name[PLUGIN_NAME_MAX];
    on_event_t on_event;
    void *on_event_arg;
    void *private_data;
    pipe_port_t *port;
    const pipe_plugin_ops *ops;
};


struct pipeline_plugin_ops {
    char *name;
    int type;
    int (*init)(pipe_plugin_t *plugin);
    int (*connect)(pipe_plugin_t *prev_plugin, pipe_plugin_t *plugin);
    int (*prepare)(pipe_plugin_t *plugin);
    int (*start)(pipe_plugin_t *plugin);
    int (*stop)(pipe_plugin_t *plugin);
    int (*reset)(pipe_plugin_t *plugin);
    int (*pause)(pipe_plugin_t *plugin);
    int (*resume)(pipe_plugin_t *plugin);
    int (*get_parameter)(pipe_plugin_t *plugin, int cmd, void *arg);
    int (*set_parameter)(pipe_plugin_t *plugin, int cmd, void *arg);
    int (*msg_cb)(pipe_plugin_t *plugin, int cmd, void *arg);
};

struct plugin_factory_entry {
    struct list_head entry;
    u8 used;
    void *plugin;
    struct pipeline_plugin_ops *ops;
};



#define REGISTER_PLUGIN(ops) \
    const struct pipeline_plugin_ops ops SEC_USED(.pipeline_plugin)

extern const struct pipeline_plugin_ops plugin_begin[];
extern const struct pipeline_plugin_ops plugin_end[];

#define list_for_each_plugin(plugin) \
    for(plugin = plugin_begin; plugin < plugin_end; plugin++)




pipe_plugin_t *plugin_register(const char *name);

void plugin_unregister(pipe_plugin_t *plugin);

int plugin_get_state(pipe_plugin_t *plugin);
//获取plugin输出的端点数量
int plugin_output_port_number(pipe_plugin_t *plugin);
//获取plugin输入的端点数量
int plugin_input_port_number(pipe_plugin_t *plugin);

char *plugin_get_name(pipe_plugin_t *plugin);
//查看plugin 使用情况
int plugin_factory_plugin_status(void);

char *plugin_factory_find(const char *find_name);

pipe_plugin_t *plugin_factory_find_used(const char *find_name);

bool port_check_connected(pipe_plugin_t *prev_plugin, pipe_plugin_t *plugin);

#endif


