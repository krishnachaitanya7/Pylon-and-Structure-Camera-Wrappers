#ifndef REMOTEFNIRS_GET_HBB_HBO_H
#define REMOTEFNIRS_GET_HBB_HBO_H
#include<bits/stdc++.h>

class get_hbb_hbo{
private:
    int curr_intensity_685;
    int curr_intensity_830;
    double baseline_685;
    double baseline_830;
public:
    get_hbb_hbo(int &current_intensity_685, int &current_intensity_830, double &baseline_value_830, double &baseline_value_685);
    std::pair<double , double> calculate_hbb_hbo();
};

#endif //REMOTEFNIRS_GET_HBB_HBO_H
