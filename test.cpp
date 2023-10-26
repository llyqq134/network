#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>

int sum(int num) {
    int s = 0;
    while(num != 0) {
        s += num % 10;
        num /= 10;
    }

    return s;
}

int main() {
    std::cout << "enter a name of client: ";
    std::string clientName;
    std::cin >> clientName;

    std::ifstream ifileTXT(clientName + ".txt");
    std::ifstream ifileBIN(clientName + ".bin", std::ios::binary | std::ios::app);

    if (!ifileTXT.is_open()) {
        ifileTXT.open(clientName + ".txt", std::ios::app);
    }
    else if (!ifileBIN.is_open())
        ifileBIN.open(clientName + ".bin", std::ios::binary | std::ios::app);

    if (!ifileTXT.is_open()) {
        std::cerr << "fileTXT isn't open";
        exit(1);
    }
    else if (!ifileBIN.is_open()) {
        std::cerr << "fileBIN isn't open";
        exit(1);
    }

    std::ofstream ofileTXT(clientName + "Answer.txt");
    std::ofstream ofileBIN(clientName + "Answer.bin", std::ios::binary);
    std::ofstream requestFile(clientName + ".txt");

    if(!ofileTXT.is_open())
        ofileTXT.open(clientName + "Answer.txt", std::ios::app);
    else if (!ofileBIN.is_open())
        ofileTXT.open(clientName + "Answer.bin", std::ios::binary | std::ios::app);

    std::string oldData;
    std::getline(ifileTXT, oldData);

    ifileTXT.seekg(0, std::ios::end);

    ifileTXT.close();
    ofileTXT.close();

    ifileBIN.close();
    ofileBIN.close();

    requestFile.close();
    std::cout << "server is working\n";
    std::string request;
    while(true) {
        std::cout.clear();
        std::cin.clear();
        std::cout << "enter your marks: ";
        std::cin >> request;
        request.erase(std::remove_if(request.begin(),request.end(), isspace), request.end());
        requestFile.open(clientName + ".txt");
        requestFile << request;
        requestFile.close();
        ifileTXT.open(clientName + ".txt");
        std::string newData;
        std::getline(ifileTXT, newData);
        ifileTXT.seekg(0, std::ios::end);
        if (oldData != newData) {
            std::cout << "file was changed\n";
            ofileTXT.open(clientName + "Answer.txt", std::ios::app);
            ofileBIN.open(clientName + "Answer.bin", std::ios::binary | std::ios::app);
            time_t seconds = time(NULL);
            tm* timeinfo = localtime(&seconds);
            ofileTXT << asctime(timeinfo) << " - file was changed\n";
            ofileBIN << asctime(timeinfo) << " - file was changed\n";
            if (sum(std::stoi(request)) >= 16) {
                ofileTXT << "you have a scholarship\n\n";
                ofileBIN << "you have a scholarship\n\n";
            }
            else {
                ofileTXT << "you don't have a scholarship\n\n";
                ofileBIN << "you don't have a scholarship\n\n";
            }
        }

        ifileTXT.close();
        ifileBIN.close();
        ofileTXT.close();
        ofileBIN.close();
    }

    return 0;
}
