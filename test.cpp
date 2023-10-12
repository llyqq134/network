#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

int main() {
    std::cout << "enter a name of client: ";
    std::string clientName;
    std::cin >> clientName;

    std::ifstream ifile(clientName + ".txt");
    if (!ifile.is_open()) {
        ifile.open(clientName + ".txt", std::ios::app);
    }

    if (!ifile.is_open())
        exit(1);

    std::ofstream ofile(clientName + "Answer.txt");

    if(!ofile.is_open())
    ofile.open(clientName + ".txt", std::ios::app);

    ifile.seekg(0, std::ios::end);
    int prevSize = ifile.tellg();
    ifile.close();
    ofile.close();
    std::cout << "server is working\n";
    while(true) {
        ifile.open(clientName + ".txt");
        ifile.seekg(0, std::ios::end);
        if (prevSize != ifile.tellg()) {
            //std::cout.clear();
            std::cout << "file was changed\n";
            prevSize = ifile.tellg();            
            ofile.open(clientName + "Answer.txt", std::ios::app);
            time_t seconds = time(NULL);
            tm* timeinfo = localtime(&seconds);
            ofile << asctime(timeinfo) << " - file was changed\n\n";
        }

        ifile.close();
        ofile.close();
    }

    return 0;
}