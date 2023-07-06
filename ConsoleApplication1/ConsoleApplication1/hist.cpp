#include "histogram.h"
#include <iostream>

using namespace std;

void find_minmax(const vector<double>dogi, double& min, double& max) {
    if (dogi.empty()) {
        return;
    }
    else {
        min = dogi[0];
        max = dogi[0];
        for (double x : dogi) {
            if (x < min) {
                min = x;
            }
            else if (x > max) {
                max = x;
            }
        }
    }
}

vector<double> create_mass(size_t number_count) {
    vector<double> dogi(number_count);
    dogi.resize(number_count);
    cerr << "¬ведите числа: ";
    for (int i = 0; i < number_count; i++) {
        cin >> dogi[i];
    }
    return dogi;
}

vector<size_t> make_hist(const vector<double>& dogi, size_t bin_count, size_t number_count, double min, double max) {

    vector<size_t> bons(bin_count);

    size_t max_count = 0;

    double bin_size = round((static_cast<double>(max - min) / bin_count) * 100.0) / 100.0;

    for (size_t i = 0; i < number_count; i++) {
        bool found = false;
        size_t j;
        for (j = 0; (j < bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= dogi[i]) && (dogi[i] < hi)) {
                bons[j]++;
                found = true;
                if (bons[j] > max_count)
                    max_count = bons[j];
            }
        }
        if (!found) {
            bons[bin_count - 1]++;
            if (bons[bin_count - 1] > max_count)
                max_count = bons[bin_count - 1];
        }
    }

    return bons;

}
