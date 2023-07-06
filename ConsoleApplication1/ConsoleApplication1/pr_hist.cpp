#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <iomanip>
#include <string>
using namespace std;

size_t find_max_count(const vector<size_t>& bins) {
    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    return max_count;
}

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_text(double left, double baseline, double text) {
    cout << "<text x='" << left << "' y='" << baseline << "'> " << setprecision(3) << text << "</text>" << '\n';
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black") {
    vector<string> colors = { "#FFD1DC", "#77DD77", "#FCE883", "#9ACEEB", "#D8BFD8",
                                "#F0E68C", "#7FC7FF", "#AFEEEE", "#CCCCFF", "#3EB489" };

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 9);
    string color = colors[distr(gen)];

    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << color << "' fill='" << color << "'/>" << '\n';
}

void svg_end() {
    cout << "</svg>\n";
}

void show_histogram_svg(const vector<size_t>bins, size_t bin_count, double min, double max) {
    const auto IMAGE_WIDTH = 1000;
    const auto IMAGE_HEIGHT = 500;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

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

    size_t max_count = find_max_count(bins);

    if (max_count > screen)
        scaling_factor = screen / static_cast<double>(max_count);

    double text_left_mod = TEXT_LEFT + (max_len * 10);
    double text_width_mod = TEXT_WIDTH + (max_len * 10);
    double shift = BIN_HEIGHT * 2;
    double text_baseline_mod = (TEXT_BASELINE + 5) * 2;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (int i = 0; i < bin_count; i++) {

        height = static_cast<int>(scaling_factor * bins[i]);

        const double bin_width = BLOCK_WIDTH * height;
        svg_text(text_left_mod, top + TEXT_BASELINE, bins[i]);
        svg_rect(text_width_mod, top, bin_width, BIN_HEIGHT);

        val_size = val_size + bin_size;

        if (i < (bin_count - 1)) {
            svg_text(TEXT_LEFT, top + text_baseline_mod, val_size);
        }

        top += shift;
    }
    svg_end();
}