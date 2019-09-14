#ifndef REMOTEFNIRS_GET_DEPTH_FRAME_STRUCTURE_H
#define REMOTEFNIRS_GET_DEPTH_FRAME_STRUCTURE_H
#include <ST/CaptureSession.h>

class structure_io_depthframe{
public:
    bool streaming_started {false};
    bool participant_moved {false};
    ST::DepthFrame get_depth_frame();
    void initialise_structure_camera();
    void save_reference_frame();
    void icp_detect_movement();
    structure_io_depthframe();

};

#endif //REMOTEFNIRS_GET_DEPTH_FRAME_STRUCTURE_H
