#include <calculate_baseline.h>
#include <vector>
#include <bits/stdc++.h>

calculate_baseline::calculate_baseline(std::vector<int> &baseline_values) {
    this->private_baseline_values = baseline_values;
}

double calculate_baseline::get_baseline_value(){
    // Function finds and returns median
    // Change this function only if you want to change to mean
    // In the future
    size_t size = calculate_baseline::private_baseline_values.size();

    if (size == 0)
    {
        return 0;  // Undefined, really.
    }
    else
    {
        std::sort(calculate_baseline::private_baseline_values.begin(), calculate_baseline::private_baseline_values.end());
        if (size % 2 == 0)
        {
            return static_cast<double>(calculate_baseline::private_baseline_values[size / 2 - 1] + calculate_baseline::private_baseline_values[size / 2]) / 2;
        }
        else
        {
            return calculate_baseline::private_baseline_values[size / 2];
        }
    }

}

