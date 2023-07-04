﻿#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'> " << text << "</text>" << '\n';
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='red' fill='#ffeeee'/>" << '\n';
}

void svg_end() {
    cout << "</svg>\n";
}

void show_histogram_svg(const vector<size_t>bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_end();
}

size_t find_max_count(const vector<size_t>& bins, const size_t bin_count) {
    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    return max_count;
}

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

void find_minmax(const vector<double>dogi, double& min, double& max) {
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

vector<double> create_mass(size_t number_count) {
    vector<double> dogi(number_count);
    dogi.resize(number_count);
    cerr << "Введите числа: ";
    for (int i = 0; i < number_count; i++) {
        cin >> dogi[i];
    }
    return dogi;
}

vector<size_t> make_hist(const vector<double>& dogi, size_t bin_count, size_t number_count, double& min, double& max) {

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
    show_histogram_svg(bins);
}