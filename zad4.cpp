#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    vector<pair<int, string>> schedule;

    while (true) {
        int N;
        cout << "Введите число операций: ";
        cin >> N;

        string operation;
        for (int i = 0; i < N; ++i) {
            cout << "Введите операцию: ";
            cin >> operation;

            if (operation == "CLASS") {
                string discipline;
                int day;
                cout << "Введите номер дня и название предмета: ";
                cin >> day >> discipline;
                schedule.push_back(make_pair(day, discipline)); // Добавляем занятие в расписание
            } else if (operation == "NEXT") {
                int lastDay = 29; // Предпоследний день текущего месяца

                for (auto& cls : schedule) {
                    cls.first = lastDay; // Переносим все занятия на предпоследний день текущего месяца
                }
                cout << "Перенос всех занятий на предпоследний день текущего месяца выполнен." << endl;
            } else if (operation == "VIEW") {
                int day;
                cout << "Введите номер дня: ";
                cin >> day;

                // Используем алгоритм find_if для поиска первого занятия на указанный день
                auto it = find_if(schedule.begin(), schedule.end(), [day](const pair<int, string>& cls) {
                    return cls.first == day;
                });

                cout << "В " << day << " день ";
                if (it != schedule.end()) { // Если занятия нашлись на указанный день
                    cout << "1 занятие в университете: " << it->second;
                    ++it;
                    while (it != schedule.end() && it->first == day) { // Выводим все занятия на этот день
                        cout << ", " << it->second;
                        ++it;
                    }
                } else {
                    cout << "У нас свободный день!"; // Если занятий нет на указанный день
                }
                cout << endl;
            } else if (operation == "EXIT") {
                cout << "Программа завершает работу." << endl;
                return 0;
            }
        }
    }

    return 0;
}
