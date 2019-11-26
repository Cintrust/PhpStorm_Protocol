// phpstotm_protocol.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


//#include "iostream"
#include <regex>
#include <Windows.h>


inline unsigned char from_hex(
        unsigned char ch
) {
    if (ch <= '9' && ch >= '0')
        ch -= '0';
    else if (ch <= 'f' && ch >= 'a')
        ch -= 'a' - 10;
    else if (ch <= 'F' && ch >= 'A')
        ch -= 'A' - 10;
    else
        ch = 0;
    return ch;
}

std::string urldecode(
        const std::string &str
) {
    using namespace std;
    string result;
    string::size_type i;
    for (i = 0; i < str.size(); ++i) {
        if (str[i] == '+') {
            result += ' ';
        } else if (str[i] == '%' && str.size() > i + 2) {
            const unsigned char ch1 = from_hex(str[i + 1]);
            const unsigned char ch2 = from_hex(str[i + 2]);
            const unsigned char ch = (ch1 << ) | ch2;
            result += ch;
            i += 2;
        } else {
            result += str[i];
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    HWND window;
    AllocConsole();
    window = FindWindowA("ConsoleWindowClass", nullptr);
    ShowWindow(window, 0);

    for (int i = 1; i < argc; ++i) {
        std::string subject = urldecode(argv[i]);
        try {
//            std::regex re(R"((url=file:\/\/|file=)(.+))");
            std::regex re(R"(^phpstorm:\/\/open\/?\?(url=file:\/\/|file=)(.+)&line=(\d+)$)");
            std::smatch match;
            if (std::regex_search(subject, match, re) && match.size() >= 3) {
//                std::string payload = "phpstorm --line "+match.str(3)+" "+match.str(2);
                std::string payload = "  phpstorm --line " + match.str(3) + " " + match.str(2) + "  2>nul >nul & ";
                system(payload.c_str());
                return 0;
            } else {

            }

        }
        catch (std::regex_error &e) {
            // Syntax error in the regular expression
        }

    }
//    system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
