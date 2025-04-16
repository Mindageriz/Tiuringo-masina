#include <iostream>  // Pagrindinė biblioteka;
#include <fstream>   // Skaitymo iš failo biblioteka;
#include <string>    // String naudojimo biblioteka;
#include <vector>    // Vector naudojimo biblioteka;
#include <set>       // Set naudojimo biblioteka;      
#include <time.h>    // Laiko uždelsimo funkcijos biblioteka;
#include <Windows.h> // Klaviaturos input'o biblioteka;

using namespace std; // Naudojamas priešdelis std;

// Duomenų struktura, kuri skirta išsaugoti visus komandos komponentus:
struct command {
    string state; // Pradinė būsena;
    char symbol1, symbol2; // Esamas arba esami simboliai;
    char newSymbol1, newSymbol2; // Naujas arba nauji simboliai;
    char dir1, dir2; // Galvutės kryptis arba kryptys;
    string newState; // Nauja būsena;
};

// Apibrežiama NUSKAITYMO funkcija, čia gražinami (&) dauguma pateiktų argumentų:
void read(int& lineCount, vector<char>& tape1, vector<char>& tape2, int& headPos1, int& headPos2, vector<command>& commands, set<string>& allStates, string fileName) {
    ifstream file;       // Nurodoma, kad duomenys bus įrašomi iš failo;
    file.open(fileName); // Atidaromas nurodytas failas;
    file >> lineCount;   // Įvedamas juostų skaičius;
    // Pirma juosta saugoma Vector'iuje:
    string tempTape;  // Laikinas juostos saugojimui skirtas string'as;
    file >> tempTape; // Juosta iš pradžių įvedama kaip String'as;
    for (int i = 0; i < tempTape.size(); i++) { // Ciklas, kuris eis nuo 0, iki laikinos juostos String'o ilgio vieneto;
        tape1.push_back(tempTape[i]); // Po viena simboli, laikina juosta transformuojama į toliau naudojamą Vector'ių;
    }
    // Nuskaitymo procesas vienos juostos tiuringo mašinai:
    if (lineCount == 1) {
        file >> headPos1; // Nuskaitoma galvutės pozicija;
        headPos1--;       // Iš gavlutės pozicijos atemamas vienetas, tam, kad ji būtų paruošta naudoti Vector'iuje;
        while (!file.eof()) { // Kol failas turi duomenų, nuskaitomos komandos;
            command x; // Apibrežiama nuoroda į komandos duomenų struktūrą;
            file >> x.state;
            file >> x.symbol1;
            file >> x.newSymbol1; // Tokiu formatu įrašomi visi komandos komponentai;
            file >> x.dir1;
            file >> x.newState;
            commands.push_back(x); // Visi komponentai išsaugojami Vector'iuje;
            allStates.insert(x.state); // Pradinė būsena išsaugojama į pradinių būsenų istorijos Set'ą;
        }
        file.close(); // Uždaromas failas;
    }
    // Nuskaitymo procesas dviejų juostų tiuringo mašinai:
    if (lineCount == 2) {
        // Antra juosta saugoma Vector'iuje:
        file >> tempTape; // Juosta iš pradžių įvedama kaip String'as, perdirbamas anksčiau naudotas String'as;
        for (int i = 0; i < tempTape.size(); i++) { // Ciklas, kuris eis nuo 0, iki laikinos juostos String'o ilgio vieneto;
            tape2.push_back(tempTape[i]); // Po viena simboli, laikina juosta transformuojama į toliau naudojamą Vector'ių;
        }
        file >> headPos1 >> headPos2; // Nuskaitomos abiejų galvučių pozicijos;
        headPos1--; // Iš gavlutės pozicijų atemamas vienetas, tam, kad jos būtų paruoštos naudoti Vector'iuje;
        headPos2--; // Pagrindinis skirtumas, jog dabar yra dvi pozicijos
        while (!file.eof()) { // Kol failas turi duomenų, nuskaitomos komandos;
            command x; // Apibrežiama nuoroda į komandos duomenų struktūrą;
            file >> x.state;
            file >> x.symbol1;
            file >> x.symbol2;
            file >> x.newSymbol1; // Tokiu formatu įrašomi visi komandos komponentai;
            file >> x.newSymbol2; // Pagrindinis skirtumas tai, kad yra daugiau duomenų (du simboliai, du nauji simboliai, dvi kryptys);
            file >> x.dir1;
            file >> x.dir2;
            file >> x.newState;
            commands.push_back(x); // Visi komponentai išsaugojami Vector'iuje;
            allStates.insert(x.state); // Pradinė būsena išsaugojama į pradinių būsenų istorijos Set'ą;
        }
        file.close(); // Uždaromas failas;
    }
}

// Apibrežiama SPAUSDINIMO funkcija, čia niekas negražinama:
void print(int lineCount, vector<char> tape1, vector<char> tape2, int headPos1, int headPos2, int steps) {
    system("cls"); // Išvaloma konsolė;
    // Spausdinama pirma juosta, auto būdu:
    for (auto i : tape1) {
        cout << i;
    }
    cout << endl;
    // Spausdinama  pirma galvutė po  pirma juosta:
    for (int i = 0; i < headPos1; i++) { // Ciklas kuris eis nuo 0 iki pirmos galvutės pozicijos (NEimtinai);
        cout << " "; // Spausdinamas tarpas;
    }
    cout << "^" << endl; // Atspausdinama pirma galvutė, tiksliai jos pozicijoje;
    cout << endl;
    // Papildomas Spausdinimas jei yra antra juosta:
    if (lineCount == 2) { 
        // Spausdinama antra juosta, auto būdu:
        for (auto i : tape2) {
            cout << i;
        }
        cout << endl;
        // Spausdinama antra galvutė po antra juosta:
        for (int i = 0; i < headPos2; i++) { // Ciklas kuris eis nuo 0 iki antros galvutės pozicijos (NEimtinai);
            cout << " "; // Spausdinamas tarpas;
        }
        cout << "^" << endl; // Atspausdinama pirma galvutė, tiksliai jos pozicijoje;
    }
    cout << "Steps: " << steps << endl; // Atspausdinamas atliktų žingsnių skaičius;
    cout << endl << "To manually Halt the machine, press - H" << endl;
}

// Apibrežiama DELSIMO funkcija, kaip argumentą ima milisekundes:
void delay(int ms) {
    clock_t time_end; 
    time_end = clock() + ms * CLOCKS_PER_SEC / 1000; // Copied from StackOverFlow XD;
    while (clock() < time_end) {}
}

// Apibrežiama Mašinos ALGORITMO funkcija, čia vyksta visi skaičiavimai ir realūs pakeitimai juostose:
void searchAndDestroy(vector<char>& tape1, vector<char>& tape2, string& currentState, int& headPos1, int& headPos2, vector<command>& commands, int lineCount, set<string> allStates, int& steps) {
    bool exists; // Kintamasis, nurodo ar ieskoma komanda egzistuoja;
    // Algoritmo žingsniai, jei yra viena mašinos juosta:
    if (lineCount == 1) {
        while (true) { // Begalinis ciklas;
            exists = false; // Nustatoma reikšmė į FALSE, nes komanda yra dar nerasta;
            for (int i = 0; i < commands.size(); i++) { // Ciklas einantis nuo 0 iki komandų skaičiaus (NEimtinai);
                // Jei Tyriamos komandos pradinė būsena sutampa su dabartine būsena,
                // Jei simbolis sutampa su juostos simboliu kuris yra ten kur galvutes pozicija:
                if (commands[i].state == currentState && commands[i].symbol1 == tape1[headPos1]) {
                    tape1[headPos1] = commands[i].newSymbol1; // Juostos simbolis pagal galvutes pozicija, pakeičiamas pagal komandos naują simbolį;
                    if (commands[i].dir1 == 'R') {
                        headPos1++; // Jei komandos kryptis yra R (dešinė), gavlutės pozicija padidinam vienetu;
                    }
                    if (commands[i].dir1 == 'L') {
                        headPos1--; // Jei komandos kryptis yra L (kairė), gavlutės pozicija pamažinam vienetu;
                    }
                    currentState = commands[i].newState; // Atnaujinama dabartinė būsena;
                    exists = true; // Radom komanda, todėl pakeičiama reikšė į TRUE;
                    i = commands.size(); // Nutraukiamas FOR ciklas;
                }
            }
            // Jei perejus visas komandas, nerandama reikiama komanda:
            if (exists == false) { 
                // Jei dabartinės būsenos nera pradinių būsenų istorijoje, reiškia ji yra baigtinė:
                if (allStates.find(currentState) == allStates.end()) {
                    cout << "The machine has reached its end state: " << currentState << endl;
                    break; // Stabdoma programa;
                }
                // Jei tiesiog nerasta tinkama komanda, reiškia jos ir nėra:
                else {
                    cout << "No such command, for symbol " << tape1[headPos1] << " in state " << currentState << endl;
                    break; // Stabdoma porgrama;
                }
            }
            // Jei exists yra TRUE, kitaip, jei komanda buvo sekmingai rasta:
            else {
                steps++; // Pridedam vienetą prie žingsnių skaičiaus;
                print(lineCount, tape1, tape2, headPos1, headPos2, steps); // Vykdom SPAUSDINIMO funkciją;
            }
            delay(50); // Vykdoma UŽDELSIMO funkcija, tam kad matytusi mašinos atliekami veiksmai;

            // Tikrinama ar klaviatūroje nenuspaustas H mygtukas, tai yra rankinis mašinos stabdymas:
            if (GetKeyState('H') & 0x8000)
            {
                cout << endl << "The machine was manually Halted at State: " << currentState << endl;
                break; // Stabdoma programa;
            }
        }
    }
    // Algoritmo žingsniai, jei yra viena mašinos juosta:
    if (lineCount == 2) {
        while (true) { // Begalinis ciklas;
            exists = false; // Nustatoma reikšmė į FALSE, nes komanda yra dar nerasta;
            for (int i = 0; i < commands.size(); i++) { // Ciklas einantis nuo 0 iki komandų skaičiaus (NEimtinai);
                // Jei Tyriamos komandos pradinė būsena sutampa su dabartine būsena,
                // Jei pirmas simbolis sutampa su juostos simboliu kuris yra ten kur pirmos galvutes pozicija:
                // Jei antras simbolis sutampa su juostos simboliu kuris yra ten kur antros galvutes pozicija:
                if (commands[i].state == currentState && commands[i].symbol1 == tape1[headPos1] && commands[i].symbol2 == tape2[headPos2]) {
                    tape1[headPos1] = commands[i].newSymbol1; // Juostos simbolis pagal galvutes pozicija, pakeičiamas pagal komandos naują simbolį;
                    tape2[headPos2] = commands[i].newSymbol2; // Juostos simbolis pagal galvutes pozicija, pakeičiamas pagal komandos naują simbolį;
                    if (commands[i].dir1 == 'R') {
                        headPos1++; // Jei komandos kryptis yra R (dešinė), gavlutės pozicija padidinam vienetu;
                    }
                    if (commands[i].dir1 == 'L') {
                        headPos1--; // Jei komandos kryptis yra L (kairė), gavlutės pozicija pamažinam vienetu;
                    }
                    if (commands[i].dir2 == 'R') {
                        headPos2++; // Jei komandos kryptis yra R (dešinė), gavlutės pozicija padidinam vienetu;
                    }
                    if (commands[i].dir2 == 'L') {
                        headPos2--; // Jei komandos kryptis yra L (kairė), gavlutės pozicija pamažinam vienetu;
                    }
                    currentState = commands[i].newState; // Atnaujinama dabartinė būsena;
                    exists = true; // Radom komanda, todėl pakeičiama reikšė į TRUE;
                    i = commands.size(); // Nutraukiamas FOR ciklas;
                }
            }
            // Jei perejus visas komandas, nerandama reikiama komanda:
            if (exists == false) {
                // Jei dabartinės būsenos nera pradinių būsenų istorijoje, reiškia ji yra baigtinė:
                if (allStates.find(currentState) == allStates.end()) {
                    cout << "The machine has reached its end state: " << currentState << endl;
                    break; // Stabdoma programa;
                }
                // Jei tiesiog nerasta tinkama komanda, reiškia jos ir nėra:
                else {
                    cout << "No such command, for symbol " << tape1[headPos1] << " in state " << currentState << endl;
                    break; // Stabdoma porgrama;
                }
            }
            // Jei exists yra TRUE, kitaip, jei komanda buvo sekmingai rasta:
            else {
                steps++; // Pridedam vienetą prie žingsnių skaičiaus;
                print(lineCount, tape1, tape2, headPos1, headPos2, steps); // Vykdom SPAUSDINIMO funkciją;
            }
            delay(50); // Vykdoma UŽDELSIMO funkcija, tam kad matytusi mašinos atliekami veiksmai;

            // Tikrinama ar klaviatūroje nenuspaustas H mygtukas, tai yra rankinis mašinos stabdymas:
            if (GetKeyState('H') & 0x8000)
            {
                cout << endl << "The machine was manually Halted at State: " << currentState << endl;
                break; // Stabdoma programa;
            }
        }
    }

}

// Apibrežiama pagrindinė funkcija, jai paduodami argumentai per konsolę (argc - argumentų skaičius; argv - argumentų vektorius)
int main(int argc, char** argv) {
    // Apibrėžiami kintamieji:
    string fileName = argv[1]; // Antras (argv[1]) paduotas argumentas yra failo pavadinimas (n.txt);
    int lineCount;             // Saugomas tiuringo mašinos juostų skaičius;
    vector<char> tape1, tape2; // Saugoma viena arba abi juostos, simbolių vector'iuje;
    int headPos1, headPos2;    // Saugoma vienos arba abieju galvučių pozicijos;
    vector<command> commands;  // Apibrežiama nuoroda į duomenų struktūrą, skirtą saugoti komandos komponentus;
    int steps = 0;             // Žingsnių skaitiklis;
    set<string> allStates;     // Visų pradinių būsenų istorija, saugoma string'ų set'e (įrašai unikalūs, nesikartoja);
    string currentState = "0"; // Saugoma dabartinė būsena;

    // Tikrinama ar Vartotojas suteikė pakankamą skaičių argumenų:
    if (argc < 2) {
        cout << "Not Enough Arguments Given!" << endl;
        cout << "Example: TuringMachine.exe n.txt" << endl;
        return 0; // Jei nepakanka argumentu, nutraukiama visa programa;
    }

    // Vykdoma NUSKAITYMO funkcija:
    read(lineCount, tape1, tape2, headPos1, headPos2, commands, allStates, fileName);

    // Vykdoma ATSPAUSDINIMO funkcija:
    print(lineCount, tape1, tape2, headPos1, headPos2, steps);

    // Vykdoma Mašinos ALGORITMO funkcija:
    searchAndDestroy(tape1, tape2, currentState, headPos1, headPos2, commands, lineCount, allStates, steps);

    return 0;
}
