#ifndef _TUYA_H264_H
#define _TUYA_H264_H

#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

//nal类型
enum nal_unit_type_e {
    NAL_UNKNOWN     = 0,
    NAL_SLICE       = 1,
    NAL_SLICE_DPA   = 2,
    NAL_SLICE_DPB   = 3,
    NAL_SLICE_DPC   = 4,
    NAL_SLICE_IDR   = 5,    /* ref_idc != 0 */
    NAL_SEI         = 6,    /* ref_idc == 0 */
    NAL_SPS         = 7,
    NAL_PPS         = 8
                      /* ref_idc == 0 for 6,9,10,11,12 */
};

int GetFrameType(char *nal);
#ifdef __cplusplus
}
#endif
#endif