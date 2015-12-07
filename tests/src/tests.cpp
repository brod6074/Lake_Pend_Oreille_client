#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "mylib.h"

// This is a very (VERY) simple, non-comprehensive set of unit tests I used
// mainly for learning how to use the Catch testing framework.

TEST_CASE("Testing the checkDate function") {
    // Validate the string length
    REQUIRE( checkDate("") == false );
    REQUIRE( checkDate("1") == false );
    REQUIRE( checkDate("111111111") == false );
    REQUIRE( checkDate("01012015") == false );

    // Validate years
    REQUIRE( checkDate("2012_01_01") == true );
    REQUIRE( checkDate("2013_01_01") == true );
    REQUIRE( checkDate("2014_01_01") == true );
    REQUIRE( checkDate("2015_01_01") == true );
    REQUIRE( checkDate("2011_01_01") == false );
    REQUIRE( checkDate("2016_01_01") == false );

}

//TEST_CASE("Testing getData function") {
//    const char* SERVER = "lpo.dt.navy.mil";
//    const char* GOOD_PATH = "/data/DM/Environmental_Data_Deep_Moor_2012.txt";
//    const char* BAD_PATH = "/data/DM/Environmental_Data_Deep_Moor_2016.txt";
//    const char* TEST_FILE = "test.txt";
//
//    REQUIRE( getData(SERVER, BAD_PATH, TEST_FILE) == false );
//    REQUIRE( getData(SERVER, GOOD_PATH, TEST_FILE) == true );
//}

//TEST_CASE( "Testing parseData function") {
//    const char* GOOD_FILE = "test.txt";
//    const char* BAD_FILE = "noexist.txt";
//    const char* DATE = "2012_01_02";
//
//    SECTION("Testing with a good file") {
//        std::vector<std::vector<double>> temp = parseData(DATE, GOOD_FILE);
//        REQUIRE(temp[0].size() != 0);
//        REQUIRE(temp[1].size() != 0);
//        REQUIRE(temp[2].size() != 0);
//    }
//    SECTION("Testing with a bad file") {
//        std::vector<std::vector<double>> temp = parseData(DATE, BAD_FILE);
//        REQUIRE(temp[0].size() == 0);
//        REQUIRE(temp[1].size() == 0);
//        REQUIRE(temp[2].size() == 0);
//    }
//}

TEST_CASE("Testing calcMean function") {
    std::vector<double> v1{1.1, 2.2, 3.3};
    std::vector<double> v2{1.1, 2.2, 3.3, 4.4};
    const double EPSILON = 0.001;

    REQUIRE(std::abs(calcMean(v1) - 2.2) < EPSILON);
    REQUIRE(std::abs(calcMean(v2) - 2.75) < EPSILON);
}

TEST_CASE("Testing calcMedian function") {
    std::vector<double> v1{1.1, 2.2, 3.3};
    std::vector<double> v2{1.1, 2.2, 3.3, 4.4};
    const double EPSILON = 0.001;

    REQUIRE(std::abs(calcMedian(v1) - 2.2) < EPSILON);
    REQUIRE(std::abs(calcMedian(v2) - 2.75) < EPSILON);
}

