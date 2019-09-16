#include <iostream>
#include <constants.h>
#include <get_depth_frame_Structure.h>
#include <get_hbb_hbo.h>
#include <pylon_camera_utils.h>
#include <calculate_baseline.h>

int main() {
    try {
//        structure_io_depthframe dpt_frame;
            pylon_camera_utils cmos_camera;
            while(true) {
                if (!cmos_camera.nm685_current_frame.empty() && !cmos_camera.nm830_current_frame.empty()) {
                    cmos_camera.get_center_of_blob(cmos_camera.nm830_current_frame);
                    break;
                }

            }
    } catch(const std::runtime_error& error){
        // Your Data Saving Code goes here
        // So that you don't lose data for stupid run time errors
        // And other Exceptions aren't caught, will include them in future
        std::cout << "Runtime Exception Occurred, Saving all data to disk" << std::endl;

    }
}