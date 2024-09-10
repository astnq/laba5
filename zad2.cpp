#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void queuePeoples(vector<pair<int, int>>& visitors, int numWindows) {
    vector<int> windowTimes(numWindows, 0);
    vector<int> windowNumbers(numWindows);
    vector<vector<int>> WINDOWS(numWindows);
    // Работа с номерами окон
    for (int i = 0; i < numWindows; ++i) {
        windowNumbers[i] = i + 1;
    }

    int numNextPeople = 0; // Номер следующего посетителя

    while (!visitors.empty()) {
        // Находим посетителя с самым большим временем посещения
        auto maxPeopleIndex = max_element(visitors.begin(), visitors.end()) - visitors.begin();

        // Находим индекс окна с минимальным временем работы
        auto minWindowIndex = min_element(windowTimes.begin(), windowTimes.end()) - windowTimes.begin();

        WINDOWS[minWindowIndex].push_back(visitors[maxPeopleIndex].second);

        
        windowTimes[minWindowIndex] += visitors[maxPeopleIndex].first; // Увеличиваем время работы окна на время обслуживания посетителя

        visitors.erase(visitors.begin() + maxPeopleIndex); // Удаляем посетителя из очереди

        numNextPeople++;
    }

    for (int i = 0; i < WINDOWS.size(); ++i) {
        cout << "Окно " << i+1 << "(" << windowTimes[i] << " минут): ";
        for (auto elem : WINDOWS[i]) {
            cout << "T" << elem << " ";
        }
        cout << endl;
    }

}

int main(){
    setlocale(LC_ALL, "Rus");

    vector<pair<int, int>> Peoples; // вектор пара, в котором будут хранится время и талоны посетителей
    cout << ">>> Введите кол-во рабочих окон:" << endl;
    cout << "<<< ";
    int NumsWindows;
    cin >> NumsWindows;

    cout << ">>> Для получения талона введите: ENQUEUE и время посещения\n\tДля формирования очереди введите: DISTRIBUTE\n\t\tДля выхода введите: EXIT" << endl;
    string command;
    bool k = true; // условие выхода из while
    int time; // время посетителя
    int talon = 100; // талон посетителя
    while (k == true) {
        cout << "<<< ";
        cin >> command;
        if (command == "ENQUEUE") {
            cin >> time;
            talon += 10;
            cout << ">>> T" << talon << endl;
            Peoples.push_back({time, talon});
        } else if (command == "DISTRIBUTE") {
            queuePeoples(Peoples, NumsWindows); // ф-ия формирования очереди
        } else if (command == "EXIT") {
            cout << ">>> Выход..." << endl;
            k = false;
        } else {
            cout << ">>> Команда введена неверно" << endl;
        }
    }

    return 0;
}
