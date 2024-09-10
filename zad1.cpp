#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <windows.h>
#include <algorithm>

using namespace std;

struct item { // ïðîäóêò
    string name;
    int quantity;
};

class sklad { // ñêëàä
private:
    map<string, item> storage; // õðàíèëèùå
    vector<char> zonees; // ñïèñîê çîí
    
public:
    void add(string address, string name, int quantity) { // ô-èÿ äîáàâëåíèÿ òîâàðà
        if (storage.count(address) != 0) { // ïðîâåðêà åñòü ëè òàêàÿ ÿ÷åéêà
            if (storage[address].name != name && storage[address].name != "") { // ïðîâåðêà, çàíÿòû ëè ÿ÷åéêà äðóãèì ïðîäóêòîì
                cout << "Îøèáêà, ÿ÷åéêà çàíÿòà!" << endl;
            } else {
                if (storage[address].quantity + quantity <= 10) { // ïðîâåðêà, ïðåâûøàåò ëè êîë-âî ïðîäóêòîâ ïðè äîáàâëåíèè ÷èñëî 10
                    storage[address] = {name, storage[address].quantity + quantity};
                } else {
                    cout << "Îøèáêà, íå õâàòàåò ìåñòà â ÿ÷åéêå!" << endl;
                }
            }
        } else { // åñëè íåò ÿ÷åéêè, òî îøèáêà
            cout << "Îøèáêà, íåò òàêîé ÿ÷åéêè!" << endl;
        }
    }

    void remove(string address, int quantity) { // ô-èÿ óäàëåíèÿ òîâàðà
        if (storage.count(address) != 0) { // ïðîâåðêà åñòü ëè òàêàÿ ÿ÷åéêà
            if (storage[address].quantity - quantity == 0) { // ïðîâåðêà, åñëè ïðè óäàëåíèè ïðîäóêòîâ ñòàëî 0, òî îñâîáîäèì ÿ÷åéêó îò ïðîäóêòà
                storage[address] = {"", 0};
            } else if (storage[address].quantity - quantity > 0) { // ïðîâåðêà, åñëè ïðè óäàëåíèè ïðîäóêòîâ èõ áóäåò > 0, òî âûïîëíÿåì
                storage[address].quantity -= quantity;
            } else { // åñëè < 0, òî ïðîäóêòîâ íå õâàòàåò
                cout << "Îøèáêà, íå õâàòàåò ïðîäóêòîâ äëÿ óäàëåíèÿ!" << endl;
            }
        } else {
            cout << "Îøèáêà, íåò òàêîé ÿ÷åéêè!" << endl;
        }
    }

    void info () { // ô-èÿ âûçîâà èíôîðìàöèè
        cout << "Àäðåññ\t" << "Ïðîäóêò\t" << "Êîë-âî" << endl; // èíôîðìàöèÿ ïî çàãðóæåííûì ÿ÷åéêàì
        float countzanyato = 0.0;
        float countzonezanyato;
        for (auto i : storage) {
            if (i.second.quantity != 0) { // âûâîä íåïóñòûõ ÿ÷ååê
                cout << i.first << "\t" << i.second.name << "\t" << i.second.quantity << endl;
                countzanyato++;
            }
        }

        float countvsego = 0.0; // èíôîðìàöèÿ ïî îáùåé çàãðóæåííîñòè ñêëàäà
        cout << "Çàãðóæåííîñòü ñêëàäà: ";
        for (auto i : storage) { // ñ÷èòàåì âñåãî ÿ÷ååê
            countvsego++;
        }
        float zagrsklad = (countzanyato/countvsego)*100; // âûñ÷èòûâàåì çàãðóæåííîñòü ñêëàäà
        cout << zagrsklad << "%" << endl;

        float countvsegozones = countvsego / zonees.size(); // Èíôîðìàöèÿ ïî îáùåé çàãðóæåííîñòè êàæäîé çîíû
        vector<float> countzanyatozones(zonees.size());
        cout << "Çàãðóæåííîñòü êàæäîé çîíû:" << endl;
        for (int i = 0; i < zonees.size(); ++i) {
            for (auto j : storage) {
                if(j.first[0] == zonees[i] && j.second.quantity > 0) { // ñ÷èòàåì çàíÿòûå çîíû
                    countzanyatozones[i]++;
                }
            }
        }
        float zagrzones;
        for (int i = 0; i < countzanyatozones.size(); ++i) {
            cout << "Çîíà " << zonees[i] << ": ";
            zagrzones = (countzanyatozones[i]/countvsegozones) * 100;
            cout << zagrzones << "%" << endl;
        }

        cout << "Ïóñòûå ÿ÷åéêè: "; // èíôîðìàöèÿ ïî ïóñòûì ÿ÷åéêàì
        for (auto i : storage) {
            if (i.second.quantity == 0) {
                cout << i.first << " ";
            }
        }
        cout << endl;
    }

    void GenerationAddress() { // ôîðìèðóåì àäðåññà ñêëàäà
        vector<char> zones = {'A', 'B', 'C'};
        zonees = zones;
        for (auto i : zones) {
            for (int polka = 1; polka <= 5; ++polka) { // ïðîõîäèì ïî êàæäîé ïîëêå
                for (int section = 1; section <= 5; ++section) { // ïðîõîäèì ïî êàæäîé ñåêöèè
                    for (int stelaj = 1; stelaj <= 3; ++stelaj) { // ïðîõîäèì ïî êàæäîìó ñòåëàæó
                        // Ñîçäàåì àäðåññà
                        stringstream s;
                        s << i << stelaj << section << polka;
                        storage[s.str()] = {"", 0};
                        
                    }
                }
            }
        }
    }
};

int main(){
    SetConsoleCP (1251);
    SetConsoleOutputCP (1251);

    sklad warehouse;
    item tovar;
    string address;

    warehouse.GenerationAddress(); // ôîðìèðóåì ñêëàä(çîíû A/B/C, 3 ñòåëàæà, 5 ñåêöèé, 5 ïîëîê)

    cout << "Âûáåðèòå êîìàíäó: ADD, REMOVE, INFO, EXIT äëÿ âûõîäà: "; // ðàáîòà ñ êîìàíäàìè
    string command;
    bool k = true;
    while (k == true) {
        cin >> command;
        if (command == "ADD") {
            cin >> address >> tovar.name >> tovar.quantity;
            warehouse.add(address, tovar.name, tovar.quantity);
        } else if (command == "REMOVE") {
            cin >> address >> tovar.quantity;
            warehouse.remove(address, tovar.quantity);
        } else if (command == "EXIT") {
            cout << "Âûõîä èç ïðîãðàììû..." << endl;
            k = false;
        } else if (command == "INFO") {
            warehouse.info();
        } else {
            cout << "Îøèáêà êîìàíäû" << endl;
        }
    }

    return 0;
}
