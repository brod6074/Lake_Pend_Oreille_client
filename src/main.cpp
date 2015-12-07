// Created by Roberto Rodriguez

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "mylib.h"

// This is a simple client that retrieves raw weather data compiled by the Navy from Lake Pend Oreille
// in Idaho. The user must provide a valid date both the form of a string (YYYY_MM_DD) and between
// 2012_01_01 to the present date. Weather data recorded at Lake Pend Oreille for that date is then retrieved
// from a website run by the Navy. The data is then used to calculate the average air temperature, barometric
// pressure, and wind speed for the given date.

int main(int argc, char* argv[]) {
    std::string HTTP {"http"};
    std::string SERVER {"lpo.dt.navy.mil"};
    std::string FILENAME {"data.txt"};

    std::string STR_2012 {"2012"};
    std::string STR_2013 {"2013"};
    std::string STR_2014 {"2014"};
    std::string STR_2015 {"2015"};

    std::string PATH_2012 {"/data/DM/Environmental_Data_Deep_Moor_2012.txt"};
    std::string PATH_2013 {"/data/DM/Environmental_Data_Deep_Moor_2013.txt"};
    std::string PATH_2014 {"/data/DM/Environmental_Data_Deep_Moor_2014.txt"};
    std::string PATH_2015 {"/data/DM/Environmental_Data_Deep_Moor_2015.txt"};

    std::unordered_map<std::string, std::string> strToUrl {
        {STR_2012, PATH_2012},
        {STR_2013, PATH_2013},
        {STR_2014, PATH_2014},
        {STR_2015, PATH_2015}
    };

    // The user inputs a valid date as a command-line argument
    if (argc != 2) {
        std::cerr << "USAGE: ./lpo <DATE>" << std::endl;
        return 1;
    }
    if (!(checkDate(argv[1])))   {
        std::cerr << "VALID FORMAT: DDMMYYYY YYYY_MM_DD" << std::endl;
        std::cerr << "VALID YEARS: [2012, 2013, 2014, 2015]" << std::endl;
        return 1;
    }

    // Once the data has been validated, the correct url for the data is set
    std::string year = "";
    if (strstr(argv[1], "2012")) {
        year = STR_2012;
    } else if (strstr(argv[1], "2013")) {
        year = STR_2013;
    } else if (strstr(argv[1], "2014")) {
        year = STR_2014;
    } else if (strstr(argv[1], "2015")) {
        year = STR_2015;
    } else {
        std::cout << "ERROR PARSING YEAR" << std::endl;
        return 1;
    }

    // A connection is made to the url to retrieve the data and save it
    if (!getData(SERVER.c_str(), strToUrl[year].c_str(), FILENAME.c_str())) {
        std::cerr << "ERROR RETRIEVING DATA" << std::endl;
        return false;
    }

    // The data is filtered for the given date
    std::vector<std::vector<double>> data {parseData(argv[1], FILENAME.c_str())};

    // The weather statistics are calculated first by sorting all data
    std::sort(data[0].begin(), data[0].end());
    std::sort(data[1].begin(), data[1].end());
    std::sort(data[2].begin(), data[2].end());

    // The stats are displayed to the user
    double result {calcMean(data[0])};
    std::cout << "The mean air temp was " << result;
    result = calcMedian(data[0]);
    std::cout << ", the median was " << result << std::endl;

    result = calcMean(data[1]);
    std::cout << "The mean barometric pressure was " << result;
    result = calcMedian(data[1]);
    std::cout << ", the median was " << result << std::endl;

    result = calcMean(data[2]);
    std::cout << "The mean wind speed was " << result;
    result = calcMedian(data[2]);
    std::cout << ", the median was " << result << std::endl;
    
    return 0;
}