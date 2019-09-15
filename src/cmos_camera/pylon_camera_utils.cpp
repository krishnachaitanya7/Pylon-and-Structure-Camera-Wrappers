#include <pylon_camera_utils.h>
#include <pylon/PylonIncludes.h>
#include <constants.h>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/video/video.hpp>
#include <opencv4/opencv2/opencv.hpp>

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
        if ( tlFactory.EnumerateDevices(devices) == 2 )
        {
            throw RUNTIME_EXCEPTION( "All CMOS cameras not detected");
        }
        for (size_t i = 0; i < cameras.GetSize(); ++i) {
            cameras[i].Attach(tlFactory.CreateDevice(devices[i]));
        }

        GenApi::INodeMap &nodemap0 = cameras[CC_Constants.nm685_camera].GetNodeMap();
        GenApi::INodeMap &nodemap1 = cameras[CC_Constants.nm830_camera].GetNodeMap();
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
    this->cmos_cameras_initialization();
}

std::pair<int, int> pylon_camera_utils::get_center_of_blob(cv::Mat input) {
    cv::Mat img;
    SimpleBlobDetector::Params params;
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
    input.convertTo(img, CV_8UC1, 0.5);
    vector<KeyPoint> keypoints;
    detector->detect( img, keypoints);
    // There Would be one Blob detected. So We will directly use that
    size_t x=keypoints.size();
    if (x != 1){
        std::cout << "Participant Moved. No Blob Detected" << std::endl;
    } else{
        Point2f point1=keypoints.at(0).pt;
        float x1=point1.x;
        float y1=point1.y;
        std::cout << "x = " << x1 << "y = " << y1 << std::endl;
    }

}
