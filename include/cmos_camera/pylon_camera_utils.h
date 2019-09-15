#ifndef REMOTEFNIRS_PYLON_CAMERA_UTILS_H
#define REMOTEFNIRS_PYLON_CAMERA_UTILS_H

#include<bits/stdc++.h>

class pylon_camera_utils{
private:
    cv::Mat 685nm_current_frame;
    cv::Mat 830nm_current_frame;
public:
    void cmos_cameras_initialization();
    void set_685nm_frame(cv::Mat input_frame);
    void set_830nm_frame(cv::Mat input_frame);
    std::pair<int, int> get_center_of_blob(cv::Mat input);
    int get_intensity_xcm_from_blobcenter(cv::Mat input, std::pair<int, int> BlobCenter, float x);
    std::pair<int, float> get_highest_intensity_from_blobcenter(cv::Mat input);
};


#endif //REMOTEFNIRS_PYLON_CAMERA_UTILS_H
