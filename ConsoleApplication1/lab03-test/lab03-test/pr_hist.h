#pragma once
#include <vector>
#include <iostream>
using namespace std;

size_t find_max_count(const vector<size_t>& bins);
void svg_begin(double width, double height);
void svg_text(double left, double baseline, double text);
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");
void svg_end();
void show_histogram_svg(const vector<size_t>bins, size_t bin_count, double min, double max);