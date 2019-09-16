#ifndef REMOTEFNIRS_PYLON_CAMERA_UTILS_H
#define REMOTEFNIRS_PYLON_CAMERA_UTILS_H

#include<bits/stdc++.h>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/video/video.hpp>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

class pylon_camera_utils{
public:
    Mat nm685_current_frame;
    Mat nm830_current_frame;
    void cmos_cameras_initialization();
    std::pair<int, int> get_center_of_blob(cv::Mat input);
    int get_intensity_xcm_from_blobcenter(cv::Mat input, std::pair<int, int> BlobCenter, float x);
    std::pair<int, float> get_highest_intensity_from_blobcenter(cv::Mat input);
    pylon_camera_utils();
};


#endif //REMOTEFNIRS_PYLON_CAMERA_UTILS_H
