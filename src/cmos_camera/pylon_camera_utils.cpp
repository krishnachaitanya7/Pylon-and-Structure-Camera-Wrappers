#include <pylon_camera_utils.h>
#include <pylon/PylonIncludes.h>
#include <constants.h>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/video/video.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <thread>

using namespace Pylon;
using namespace std;
using namespace cv;

void pylon_camera_utils::cmos_cameras_initialization() {
    PylonInitialize();
    CMOSCamera_Constants CC_Constants;
    try {
        CInstantCameraArray cameras(CC_Constants.total_cmos_cameras);
        CTlFactory &tlFactory = CTlFactory::GetInstance();
        DeviceInfoList_t devices;
        tlFactory.EnumerateDevices(devices);
        for (size_t i = 0; i < cameras.GetSize(); ++i) {
            cameras[i].Attach(tlFactory.CreateDevice(devices[i]));
        }
        cameras.Open();
        GenApi::INodeMap& nodemap0 = cameras[CC_Constants.nm685_camera].GetNodeMap();
        GenApi::INodeMap& nodemap1 = cameras[CC_Constants.nm830_camera].GetNodeMap();
        CEnumParameter pixelFormat0(nodemap0, "PixelFormat");
        pixelFormat0.SetValue("Mono12");
        CEnumParameter pixelFormat1(nodemap1, "PixelFormat");
        pixelFormat1.SetValue("Mono12");
        cameras.StartGrabbing();
        CGrabResultPtr ptrGrabResult;
        while (true) {
            cameras.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);
            intptr_t cameraContextValue = ptrGrabResult->GetCameraContext();
            if (cameraContextValue == CC_Constants.nm685_camera) {
                this->nm685_current_frame = Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(),
                                                CV_16UC1, (uint32_t *) ptrGrabResult->GetBuffer());
            } else {
                this->nm830_current_frame = Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(),
                                                CV_16UC1, (uint32_t *) ptrGrabResult->GetBuffer());
            }


        }
    }
    catch (const GenericException &e) {
        // Error handling
        cerr << "An exception occurred." << endl
             << e.GetDescription() << endl;

    }


}
pylon_camera_utils::pylon_camera_utils() {
    std::thread pylon_thread(&pylon_camera_utils::cmos_cameras_initialization, this);
    pylon_thread.detach();

}

std::pair<int, int> pylon_camera_utils::get_center_of_blob(cv::Mat input) {
    cv::Mat img, im_with_keypoints;
    SimpleBlobDetector::Params params;
    params.filterByCircularity = true;
//    params.minCircularity = 0.1;
    params.filterByColor = true;
    params.filterByArea = true;
    params.minArea = 800;
    params.filterByInertia = true;
    params.minInertiaRatio = 0.01;
    params.filterByConvexity = true;
    params.minConvexity = 0.2;
    params.minThreshold = 70;
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
    input.convertTo(img, CV_8UC1, 0.05);
//    imshow("Converted Image", img);
//    waitKey(0);
// Uncomment from below
//    vector<KeyPoint> keypoints;
//    std::cout << img << std::endl;
//    detector->detect( img, keypoints);
//    drawKeypoints( img, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
//    imshow("keypoints", im_with_keypoints );// Show blobs
//    waitKey(0);
//    size_t x=keypoints.size();
//    if (x != 1){
//        std::cout << "Participant Moved. Blobs Detected: " << x << std::endl;
//    } else{
//        Point2f point1=keypoints.at(0).pt;
//        float x1=point1.x;
//        float y1=point1.y;
//        std::cout << "x = " << x1 << " y = " << y1 << std::endl;
//    }
    vector<Vec3f> circles;

    HoughCircles(img, circles, HOUGH_GRADIENT,
                 2,   // accumulator resolution (size of the image / 2)
                 10,  // minimum distance between two circles
                 100, // Canny high threshold
                 100, // minimum number of votes
                 185, 10000); // min and max radius
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );// circle center
        circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );// circle outline
        cout << "center : " << center << "\nradius : " << radius << endl;
    }
    namedWindow( "Hough Circle Transform Demo", WINDOW_AUTOSIZE );
    imshow( "Hough Circle Transform Demo", img );

    waitKey(0);

    std::cout << circles.size() <<std::endl;



}
