#pragma once

bool checkDate(const char* date);
bool getData(const char* server, const char* path, const char* filename);
std::vector<std::vector<double> > parseData(const char* date, const char* filename);
double calcMean(const std::vector<double>& v);
double calcMedian(const std::vector<double>& v);