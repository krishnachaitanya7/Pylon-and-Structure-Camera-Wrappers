#ifndef REMOTEFNIRS_CALCULATE_BASELINE_H
#define REMOTEFNIRS_CALCULATE_BASELINE_H

#include <vector>

class calculate_baseline{
private:
    std::vector<int> private_baseline_values;
public:
    // Instantiate the class with previously done rest period baseline values
    calculate_baseline(std::vector<int> &baseline_values);
    // Return the baseline, which is median of the vector it's instantiated with
    // People Like to use mean, I prefer median. More resistant to outliers
    double get_baseline_value();
};

#endif //REMOTEFNIRS_CALCULATE_BASELINE_H
