#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>
#include <random>
#include "histogram.h"
#include "pr_hist.h"

using namespace std;

/*
void show_histogram_text(const vector<size_t>bons, size_t bin_count, double min, double max) {
    
    size_t segment, len_segment, max_len = 0; 
    
    double bin_size = round((static_cast<double>(max - min) / bin_count) * 100.0) / 100.0;
    
    for (double j = min; j < max; j += bin_size) {
        segment = static_cast<size_t>(j * 100);
        while (segment % 10 == 0)
            segment = segment / 10;
        len_segment = to_string(segment).length();
        if (j != segment)
            len_segment++;
        if (len_segment > max_len)
            max_len = len_segment;
    }

    double scaling_factor = 1;
    size_t height;
    const size_t screen = 76;
    double val_size = min;
    string sp(max_len, ' ');

    size_t max_count = find_max_count(bons, bin_count);

    if (max_count > screen)
        scaling_factor = screen / static_cast<double>(max_count);
    for (int i = 0; i < bin_count; i++) {
        if (bons[i] < 100) {
            cout << ' ';
        }
        if (bons[i] < 10) {
            cout << ' ';
        }

        cout << sp << bons[i] << '|';

        height = static_cast<int>(scaling_factor * bons[i]);
        for (int j = 0; j < height; j++)
            cout << '*';
        cout << '\n';
        val_size = val_size + bin_size;

        if (i < (bin_count - 1)) {
            cout << val_size << endl;
        }
    }

}
*/

int main()
{
    setlocale(LC_ALL, "Russian");

    size_t number_count, bin_count;
    double min = 0, max = 0;

    cerr << "Введите кол-во чисел: ";
    cin >> number_count;

    const auto dogi = create_mass(number_count);

    find_minmax(dogi, min, max);

    cerr << "Введите кол-во корзин: ";
    cin >> bin_count;
    cerr << '\n';

    const auto bins = make_hist(dogi, bin_count, number_count, min, max);

    //show_histogram_text(bins, bin_count, min, max);
    show_histogram_svg(bins, bin_count, min, max);
}