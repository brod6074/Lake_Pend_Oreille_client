// Created by Roberto Rodriguez

#include <boost/asio.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "mylib.h"

// Checks for a valid date, not comprehensive
bool checkDate(const char* date) {
    if (strlen(date) != 10) {
        return false;
    }

    if (strstr(date, "2012") || strstr(date, "2013") ||
        strstr(date, "2014") || strstr(date, "2015")) {
        return true;
    } else {
        return false;
    }
}

// Virtually all the code in this function was taken from an example 
// for how to use Boost Asio
bool getData(const char* url, const char* path, const char* filename) {
    using namespace boost::asio::ip;

    boost::asio::io_service ioService;
    tcp::resolver resolver(ioService);
    tcp::resolver::query query(url, "http");
    tcp::resolver::iterator endpointIter = resolver.resolve(query);

    tcp::socket socket(ioService);
    boost::asio::connect(socket, endpointIter);

    boost::asio::streambuf request;
    std::ostream requestStream(&request);
    requestStream << "GET " << path << " HTTP/1.0\r\n";
    requestStream << "Host:" << url << "\r\n";
    requestStream << "Accept: */*\r\n";
    requestStream << "Connection: close\r\n\r\n";

    boost::asio::write(socket, request);
    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\r\n");

    std::istream responseStream(&response);
    std::string httpVersion;
    responseStream >> httpVersion;
    unsigned int statusCode;
    responseStream >> statusCode;
    std::string statusMsg;
    std::getline(responseStream, statusMsg);

    // Check for invalid HTTP responses
    if (!responseStream || httpVersion.substr(0, 5) != "HTTP/") {
        std::cout << "Invalid response\n";
        return false;
    }
    if (statusCode != 200) {
        std::cout << "Response returned with status code " << statusCode << "\n";
        return false;
    }

    boost::asio::read_until(socket, response, "\r\n\r\n");

    std::string header;
    while (std::getline(responseStream, header) && header != "\r") {}
    std::cout << std::endl;

    std::ofstream outfile;
    outfile.open(filename);

    if (response.size() > 0) {
        outfile << &response;
    }

    boost::system::error_code error;
    while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error)) {
        outfile << &response;
    }
    if (error != boost::asio::error::eof) {
        throw boost::system::system_error(error);
    }

    outfile.close();

    return true;
}

// Parses the data that is retrieved from the Lake Pend Oreille site
std::vector<std::vector<double> > parseData(const char* date, const char* filename) {
    std::ifstream infile;
    std::vector<std::vector<double> > data(3);
    std::string input;

    infile.open(filename);

    while (infile >> input) {
        if (input.compare(date) == 0) {
            double airTemp;
            double barPres;
            double windSpeed;

            infile >> input; // ignore this field
            infile >> input; // air temperature
            airTemp = atof(input.c_str());

            infile >> input; // barometric pressure
            barPres = atof(input.c_str());

            infile >> input; // ignore this field
            infile >> input; // ignore this field
            infile >> input; // ignore this field
            infile >> input; // ignore this field
            infile >> input; // wind speed
            windSpeed = atof(input.c_str());

            data[0].push_back(airTemp);
            data[1].push_back(barPres);
            data[2].push_back(windSpeed);

        } else {
            getline(infile, input);
        }
    }

    return data;
}

// Calculate the mean of any collection of doubles
double calcMean(const std::vector<double>& v) {
    double mean = 0.0;

    for (const auto& d: v) {
        mean += d;
    }
    mean /= v.size();
    return mean;
}

// Calculate the median of any collection of doubles
double calcMedian(const std::vector<double>& v) {
    int size = v.size();
    double mean = 0.0;

    if (size % 2 == 0) {
        mean += v[size/2 - 1];
        mean += v[size/2];
        mean /= 2;
    } else {
        mean += v[size/2];
    }

    return mean;
}
