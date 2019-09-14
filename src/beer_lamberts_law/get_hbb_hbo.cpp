#include <get_hbb_hbo.h>
#include <constants.h>
#include <math.h>

get_hbb_hbo::get_hbb_hbo(int &current_intensity_685, int &current_intensity_830, double &baseline_value_830, double &baseline_value_685){
    /*
     * Initializing The private variables
     * */
    curr_intensity_685 = current_intensity_685;
    curr_intensity_830 = current_intensity_830;
    baseline_830 = baseline_value_830;
    baseline_685 = baseline_value_685;
}

std::pair<double, double> get_hbb_hbo::calculate_hbb_hbo(){
    /*
     * Formula Inspired By pic in the same folder. Please let me know if implementation is correct
     * or have any doubts
     * */
    BeerLambert_Constants bl_constants;
    double log_830nm_baseline_by_830nm_intensity = log10(static_cast<double >(curr_intensity_830) / baseline_830 );
    double log_685nm_baseline_by_685nm_intensity = log10(static_cast<double >(curr_intensity_685) / baseline_685 );
    double hb {(bl_constants.alpha_hbo_685nm*log_830nm_baseline_by_830nm_intensity - bl_constants.alpha_hbo_830nm*log_685nm_baseline_by_685nm_intensity) /
                (bl_constants.alpha_hhb_830nm*bl_constants.alpha_hbo_685nm - bl_constants.alpha_hhb_685nm*bl_constants.alpha_hbo_830nm)};

    double hbo {(bl_constants.alpha_hhb_830nm*log_685nm_baseline_by_685nm_intensity - bl_constants.alpha_hhb_685nm*log_830nm_baseline_by_830nm_intensity) /
               (bl_constants.alpha_hhb_830nm*bl_constants.alpha_hbo_685nm - bl_constants.alpha_hhb_685nm*bl_constants.alpha_hbo_830nm)};

    return std::make_pair(hb, hbo);
}

