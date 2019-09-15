#ifndef REMOTEFNIRS_CONSTANTS_H
#define REMOTEFNIRS_CONSTANTS_H

/*
 * Everything here is hard Fucking Coded. Dont Goddamn use any constants in any freaking class
 * other than this for the love of Jesus. It will break your code, and you will whine like a 1 year old.
 * And after that smoke up and get wasted
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

#endif //REMOTEFNIRS_CONSTANTS_H
