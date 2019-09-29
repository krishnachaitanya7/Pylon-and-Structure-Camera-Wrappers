#ifndef CONSTANTS_H
#define CONSTANTS_H

/*
 * Everything here is hard Coded. Dont use any constants in any freaking class
 * It will break your code, and you will whine
 * */
class DepthCamera_Constants{
public:
    const char *face_ref_path {"/home/shine/CLionProjects/Structure-Sensor-ICP/cmake-build-debug/Ref.ply"};
    const char *current_frame_path {"/home/shine/CLionProjects/Structure-Sensor-ICP/cmake-build-debug/Ref1.ply"};
    double fitness_max {10.0};
};

class CMOSCamera_Constants{
public:
    // As there are total 2 CMOS cameras in the lab
    int total_cmos_cameras {2};
    int nm685_camera {0};
    int nm830_camera {1};


};

class BeerLambert_Constants{
    /*
     * Adopted from beer lambert law
     * formula photo in the repo
     * */
public:
    // Deoxy Hb Absorption Values
    double alpha_hbo_685nm {0.09646034};
    double alpha_hbo_830nm {0.2320466};
    // Oxy Hb Absorption Values
    double alpha_hhb_685nm {0.5382837};
    double alpha_hhb_830nm {0.1791653};

};

class DataSaver_Constants{


};

#endif
