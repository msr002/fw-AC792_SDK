#include "system/includes.h"
#include "generic/log.h"
#include "app_config.h"

extern char __VERSION_BEGIN[];
extern char __VERSION_END[];

const char *sdk_version(void)
{
    return "AC792N SDK on branch [wifi_video_master] tag ";
}

static int app_version_check()
{
    char *version;

    printf("================= SDK Version    %s     ===============\n", sdk_version());
#ifdef CONFIG_WIFI_SOUNDBOX_PROJECT_ENABLE
    printf("================= Media SDK Version %s ===============\n", "AC792N_soundbox_V1.0.0_2025-5-10_10-30");
#endif
    for (version = __VERSION_BEGIN; version < __VERSION_END;) {
        printf("%s\n", version);
        version += strlen(version) + 1;
    }
    puts("=======================================\n");

    return 0;
}
early_initcall(app_version_check);

