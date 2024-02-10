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
            cout << "Номер поезда: " << train.number << " Время отправления: " << train.departureTime << " Станция назначения: " << train.destinationStation << endl;
        }
    }

    void printTrainInfo(int trainNumber) {
        for (const auto& train : trains) {
            if (train.number == trainNumber) {
                cout << "Номер поезда: " << train.number << " Время отправления: " << train.departureTime << " Станция назначения: " << train.destinationStation << endl;
            }
        }
        cout << "Поезд с номером " << trainNumber << " не найден" << endl;
    }

    void readFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            int number;
            string departureTime, destinationStation;
            while (file >> number >> departureTime >> destinationStation) {
                addTrain(number, departureTime, destinationStation);
            }
            cout << "Расписание загружено из файла" << endl;
            file.close();
        }
        else {
            cerr << "Не удалось открыть файл." << filename << endl;
        }
    }

    void writeToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& entry : trains) {
                file << entry.number << " " << entry.departureTime << " " << entry.destinationStation << endl;
            }
            cout << "Расписание записано в файл" << endl;
            file.close();
        }
        else {
            cerr << "Не удалось открыть файл." << filename << endl;
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
        cout << "1. Ввод данных в систему" << endl;
        cout << "2. Вывод информации о всех поездах" << endl;
        cout << "3. Вывод информации о запрашиваемом поезде" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите номер действия: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите информацию о поезде через пробел (номер поезда,время отправления в формате чч:мм, станция назначения): " << endl;
            cin >> number >> departureTime >> destinationStation;
            system.addTrain(number, departureTime, destinationStation);
            break;

        case 2:
            system.printAllTrains();
            break;

        case 3:
            cout << "Введите номер поезда, чтобы получить информацию: ";
            cin >> requestedTrainNumber;
            system.printTrainInfo(requestedTrainNumber);
            break;

        case 0:
            cout << "Выход из программы" << endl;
            break;

        default:
            cout << "Неправильный выбор" << endl;
            break;
        }
    } while (choice != 0);

    system.writeToFile("trains.txt");

    return 0;

}