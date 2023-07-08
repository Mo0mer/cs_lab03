#pragma once
#include <vector>
using namespace std;
void find_minmax(const vector<double> numbers, double& min, double& max);
vector<double> create_mass(size_t number_count);
vector<size_t> make_hist(const vector<double>& dogi, size_t bin_count, size_t number_count, double min, double max);
vector <double> make_inter(size_t bin_count, double min, double max);