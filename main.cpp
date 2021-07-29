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

using namespace std;

string key, mixing, mixed;

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
    mixing = md5(md5(md5(md5(md5(mix)))));
    string birlestir = stringer(mixing, finalTime, mixing);
    mixed = md5(md5(birlestir));
    return mixed;
}

void lisanskontrol() {
    string url = "http://0.0.0.0/license.php?license=" + key + "&hwid=" + mixing;
    std::wstring url2(url.begin(), url.end());
    IStream* stream;
    HRESULT result = URLOpenBlockingStream(0, (LPCWSTR)url2.c_str(), &stream, 0, 0);
    char buffer[100];
    unsigned long bytesRead;
    stringstream ss;
    stream->Read(buffer, 100, &bytesRead);
    while (bytesRead > 0U)
    {
        ss.write(buffer, (long long)bytesRead);
        stream->Read(buffer, 100, &bytesRead);
    }
    string strResult = ss.str();
    if (strResult == mixed) {
        cout << "Lisans Anahtarı Onaylandı";
		std::cin.get();
    }
    else {
        cout << "Lisans Anahtarı Onaylanamadı";
		std::cin.get();
    }
}

int main() {
    hwidcek();
    cout << "Lisans Anahtarı: ";
    cin >> key;
    lisanskontrol();
}