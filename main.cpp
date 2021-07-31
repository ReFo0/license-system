#include "misc.h"

void lisanskontrol() {
    string url = "http://0.0.0.0/license.php?license=" + anahtar + "&hwid=" + mixx;
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
        cout << "License Active";
		std::cin.get();
    }
    else {
        cout << "Failed to confirm license key ";
		std::cin.get();
    }
}

int main() {
    hwidcek();
    cout << "Lisans Anahtarı: ";
    cin >> anahtar;
    lisanskontrol();
}
