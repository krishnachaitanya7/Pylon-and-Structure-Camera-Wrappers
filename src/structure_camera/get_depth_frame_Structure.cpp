#include <get_depth_frame_Structure.h>
#include <iostream>
#include <ST/CaptureSession.h>
#include <constants.h>
#include <thread>
#include <chrono>
#include <pcl/io/io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>

ST::DepthFrame structure_io_depthframe::get_depth_frame(){
    return this->current_frame;
}

void structure_io_depthframe::set_depth_frame(ST::DepthFrame &dp_frame){
    this->current_frame = dp_frame;
    this->streaming_started = true;
}

void structure_io_depthframe::icp_detect_movement(){
    DepthCamera_Constants DC_constants;
    double current_fitness_score;
    double max_fitness = DC_constants.fitness_max;
    remove(DC_constants.current_frame_path);
    this->current_frame.saveImageAsPointCloudMesh(DC_constants.current_frame_path);
    pcl::PointCloud<pcl::PointXYZ>::Ptr face_cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr current_frame_from_rgbd (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PLYReader Reader;
    Reader.read(DC_constants.face_ref_path, *face_cloud);
    Reader.read(DC_constants.current_frame_path, *current_frame_from_rgbd);
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
//            icp.setTransformationEpsilon(1e-2);
//            icp.setMaximumIterations(100);
//            icp.setMaxCorrespondenceDistance(0.3);
//            icp.setEuclideanFitnessEpsilon (1e-8); //1e-5, 1e-8
    icp.setInputSource(face_cloud);
    icp.setInputTarget(current_frame_from_rgbd);
    pcl::PointCloud<pcl::PointXYZ> Final;
    icp.align(Final);
    if(icp.hasConverged()){
        current_fitness_score = icp.getFitnessScore();
        if (current_fitness_score > max_fitness){
            std::cout << "Participant Has Moved. Data is Being discarded" << std::endl;
        }

    } else{
        this->participant_moved = true;
        std::cout << "ICP not converged. Probably participant Has Moved?" << std::endl;
    }

}

void structure_io_depthframe::save_reference_frame(){
    DepthCamera_Constants DC_constants;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    ST::DepthFrame reference_frame = get_depth_frame();
    remove(DC_constants.face_ref_path);
    reference_frame.saveImageAsPointCloudMesh(DC_constants.face_ref_path);
    std::cout << "Reference Frame Written, You can move your head now" << std::endl;
}

void structure_io_depthframe::initialise_structure_camera(){
    static structure_io_depthframe* temp = this;
    struct SessionDelegate : ST::CaptureSessionDelegate {
        void captureSessionEventDidOccur(ST::CaptureSession *session, ST::CaptureSessionEventId event) override {
            printf("Received capture session event %d (%s)\n", (int)event, ST::CaptureSessionSample::toString(event));
            switch (event) {
                case ST::CaptureSessionEventId::Booting: break;
                case ST::CaptureSessionEventId::Ready:
                    printf("Starting streams...\n");
                    session->startStreaming();
                    break;
                case ST::CaptureSessionEventId::Disconnected:
                case ST::CaptureSessionEventId::Error:
                    printf("Capture session error\n");
                    exit(1);

            }
        }

        void captureSessionDidOutputSample(ST::CaptureSession *, const ST::CaptureSessionSample& sample) override {
            switch (sample.type) {
                case ST::CaptureSessionSample::Type::SynchronizedFrames:
                    ST::DepthFrame dp_frame = sample.depthFrame;
                    temp->set_depth_frame(dp_frame);

//                std::cout << "TimeStamp is:" << sample.depthFrame.timestamp() << std::endl;
                    break;

            }
        }
    };

    ST::CaptureSessionSettings settings;
    settings.applyExpensiveCorrection = true;
    settings.source = ST::CaptureSessionSourceId::StructureCore;
    settings.structureCore.depthEnabled = true;
    settings.structureCore.visibleEnabled = false;
    settings.structureCore.infraredEnabled = true;
    settings.structureCore.accelerometerEnabled = false;
    settings.structureCore.gyroscopeEnabled = false;
    settings.structureCore.depthResolution = ST::StructureCoreDepthResolution::_320x240;
    settings.structureCore.depthRangeMode = ST::StructureCoreDepthRangeMode::VeryShort;

    SessionDelegate delegate;
    ST::CaptureSession session;
    session.setDelegate(&delegate);
    if (!session.startMonitoring(settings)){
        printf("Failed to initialize capture session!\n");
        exit(1);
    }
}
structure_io_depthframe::structure_io_depthframe() {
    this->streaming_started = false;
    this->initialise_structure_camera();
}

