#include "tuya_h264.h"


int GetFrameType(char *nal)
{
    int frame_type = 0;

    if (nal[0] == 0x00 && nal[1] == 0x00 && nal[2] ==  0x00 && nal[3] == 0x01) {
        frame_type = nal[4] & 0x1f;
    } else if (nal[0] == 0x00 && nal[1] == 0x00 && nal[2] ==  0x00 && nal[3] == 0x00 && nal[4] == 0x01) {
        frame_type = nal[5] & 0x1f;
    } else {
        return -1;
    }
    return frame_type;
}
