#include <pylon_camera_utils.h>
#include <pylon/PylonIncludes.h>
#include <constants.h>

using namespace Pylon;
using namespace std;

void pylon_camera_utils::cmos_cameras_initialization() {
    PylonInitialize();
    CMOSCamera_Constants CC_Constants;
    try{
        CInstantCameraArray cameras( CC_Constants.total_cmos_cameras);
        CTlFactory& tlFactory = CTlFactory::GetInstance();
        DeviceInfoList_t devices;
        for ( size_t i = 0; i < cameras.GetSize(); ++i){
            cameras[ i ].Attach( tlFactory.CreateDevice( devices[ i ]));
        }

        GenApi::INodeMap& nodemap0 = cameras[0].GetNodeMap();
        GenApi::INodeMap& nodemap1 = cameras[1].GetNodeMap();


    }catch (const GenericException &e){
        // Error handling
        cerr << "An exception occurred." << endl
             << e.GetDescription() << endl;

    }


}
