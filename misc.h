#include <tchar.h>
#include <random>
#pragma comment(lib, "urlmon.lib")
#include <urlmon.h>
#include <sstream>
#include <iostream>
#include <Lmcons.h>
#include <string>
#include <random>
#include <Windows.h>
#include "md5.h"
#include <ctime>
#include <string.h>
#include <string>
#include <stdio.h> 
#include <fstream>
#include <chrono>
#pragma comment(lib, "user32.lib")
using namespace std;


string anahtar, mixx, mixed;

template< typename ... Args >
std::string stringer(Args const& ... args)
{
    std::ostringstream stream;
    using List = int[];
    (void)List {
        0, ((void)(stream << args), 0) ...
    };
    return stream.str();
}

string hwidcek() {
    time_t now = time(0);
    string time = to_string(now);
    string finalTime = time.substr(0, 7);

    string a, b, c, d, e;
    HW_PROFILE_INFO hwProfileInfo;
    GetCurrentHwProfile(&hwProfileInfo);
    wstring hwidWString = hwProfileInfo.szHwProfileGuid;
    string hwid(hwidWString.begin(), hwidWString.end());

    a = hwid.substr(1, 8);
    b = hwid.substr(10, 4);
    c = hwid.substr(15, 4);
    d = hwid.substr(20, 4);
    e = hwid.substr(25, 12);

    string mix = stringer(a, c, d, e, a, b, e, a, d, c, e, a);
    mixx = md5(md5(md5(md5(md5(mix)))));
    string birlestir = stringer(mixx, finalTime, mixx);
    mixed = md5(md5(birlestir));
    return mixed;
}