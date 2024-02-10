#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

class Train {
public:
    int number;
    string departureTime;
    string destinationStation;

    Train(int num, string depTime, string destStation) {
        this->number = num;
        this->departureTime = depTime;
        this->destinationStation = destStation;
    }

};

class TrainStationSystem {
private:
    vector<Train> trains;
public:
    void addTrain(int number, const string& departureTime, const string& destinationStation) {
        trains.push_back({ number, departureTime, destinationStation });
    }

    void printAllTrains() {
        for (const auto& train : trains) {
            cout << "����� ������: " << train.number << " ����� �����������: " << train.departureTime << " ������� ����������: " << train.destinationStation << endl;
        }
    }

    void printTrainInfo(int trainNumber) {
        for (const auto& train : trains) {
            if (train.number == trainNumber) {
                cout << "����� ������: " << train.number << " ����� �����������: " << train.departureTime << " ������� ����������: " << train.destinationStation << endl;
            }
        }
        cout << "����� � ������� " << trainNumber << " �� ������" << endl;
    }

    void readFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            int number;
            string departureTime, destinationStation;
            while (file >> number >> departureTime >> destinationStation) {
                addTrain(number, departureTime, destinationStation);
            }
            cout << "���������� ��������� �� �����" << endl;
            file.close();
        }
        else {
            cerr << "�� ������� ������� ����." << filename << endl;
        }
    }

    void writeToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& entry : trains) {
                file << entry.number << " " << entry.departureTime << " " << entry.destinationStation << endl;
            }
            cout << "���������� �������� � ����" << endl;
            file.close();
        }
        else {
            cerr << "�� ������� ������� ����." << filename << endl;
        }
    }

};

int main() {
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);

    int choice;
    int requestedTrainNumber;
    int number;
    string departureTime, destinationStation;

    TrainStationSystem system;

    system.readFromFile("trains.txt");

    do {
        cout << "1. ���� ������ � �������" << endl;
        cout << "2. ����� ���������� � ���� �������" << endl;
        cout << "3. ����� ���������� � ������������� ������" << endl;
        cout << "0. �����" << endl;
        cout << "������� ����� ��������: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "������� ���������� � ������ ����� ������ (����� ������,����� ����������� � ������� ��:��, ������� ����������): " << endl;
            cin >> number >> departureTime >> destinationStation;
            system.addTrain(number, departureTime, destinationStation);
            break;

        case 2:
            system.printAllTrains();
            break;

        case 3:
            cout << "������� ����� ������, ����� �������� ����������: ";
            cin >> requestedTrainNumber;
            system.printTrainInfo(requestedTrainNumber);
            break;

        case 0:
            cout << "����� �� ���������" << endl;
            break;

        default:
            cout << "������������ �����" << endl;
            break;
        }
    } while (choice != 0);

    system.writeToFile("trains.txt");

    return 0;

}