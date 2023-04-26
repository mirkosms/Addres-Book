#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Person
{
    int id;
    string firstName, lastName, phoneNumber, email, address;
};

string readLine()
{
    string input = "";
    cin.sync();
    getline(cin, input);
    return input;
}

char getChar()
{
    string input = "";
    char character = {0};
    while (true)
    {
        cin.sync();
        getline(cin, input);
        if (input.length() == 1)
        {
            character = input[0];
            break;
        }
        else
            cout << "To nie jest pojedynczy character. Wpisz ponownie." << endl;
    }
    return character;
}

void printPerson (Person person)
{
    cout << "ID: " << person.id << endl;
    cout << person.firstName << " " << person.lastName << endl;
    cout << "Telefon: " << person.phoneNumber << endl;
    cout << "Email: " << person.email << endl;
    cout << "Adres: " << person.address << endl << endl;
}

int getInputsFromFile(vector<Person>& addressBookInputs, int inputsCount)
{
    int lineNumber = 1;
    string line;
    fstream file;
    file.open("AddressBook.txt", ios::in);

    if (file.good() == false)
    {
        cout << "Nie mozna otworzyc pliku. " << endl;
    }

    Person input;
    while (file >> input.id >> input.firstName >> input.lastName >> input.phoneNumber >> input.email >> input.address)
    {
        addressBookInputs.push_back(input);
        inputsCount++;
    }
//    while(getline(file, line))
//    {
//        switch(lineNumber)
//        {
//        case 1:
//            addressBookInputs[inputsCount].id = stoi(line); break;
//        case 2:
//            addressBookInputs[inputsCount].firstName = line; break;
//        case 3:
//            addressBookInputs[inputsCount].lastName = line; break;
//        case 4:
//            addressBookInputs[inputsCount].phoneNumber = line; break;
//        case 5:
//            addressBookInputs[inputsCount].email = line; break;
//        case 6:
//            addressBookInputs[inputsCount].address = line;
//            inputsCount++;
//            lineNumber = 0;
//            break;
//        }
//        lineNumber++;
//    }

    file.close();

    return inputsCount;

}

int addInput (vector<Person>& addressBookInputs, int inputsCount)
{
    Person input;
    cout << "Podaj imie: ";
    input.firstName = readLine();
    cout << "Podaj nazwisko: ";
    input.lastName = readLine();
    cout << "Podaj numer telefonu: ";
    input.phoneNumber = readLine();
    cout << "Podaj email: ";
    input.email = readLine();
    cout << "Podaj address: ";
    input.address = readLine();

    input.id = inputsCount + 1;
    system("pause");

    fstream file;
    file.open("AddressBook.txt", ios::out | ios::app);

    if (file.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych. " << endl;
    }
    else
    {
        addressBookInputs.push_back(input);
        inputsCount++;

        cout << endl << "Osoba zostala dodana do ksiazki adresowej." << endl;
        system("pause");
    }
    return inputsCount;
}

void searchBy(vector<Person>& addressBookInputs, int inputsCount, string field, string value)
{
    bool found = false;
    for (int i = 0; i < inputsCount; i++)
    {
        if ((field == "imie" && addressBookInputs.at(i).firstName == value) ||
                (field == "nazwisko" && addressBookInputs.at(i).lastName == value))
        {
            found = true;
            cout << "Znaleziono osobe,ktora ma " << field << " " << value << endl << endl;
            printPerson(addressBookInputs.at(i));
        }
    }

    if (!found)
    {
        cout << "Nie znaleziono osoby o wskazanym " << field << endl;
    }
    system("pause");
}

void showAllInputs(vector<Person>& addressBookInputs, int inputsCount)
{
    if (inputsCount == 0)
    {
        cout << "Ksiazka adresowa jest pusta." << endl;
    }
    else
    {

        for (int i = 0; i < inputsCount; i++)
        {
            printPerson(addressBookInputs.at(i));
        }

    }

    system("pause");
}

int main()
{
    int inputsCount = 0;
    char selection;
    string searchedFirstName;
    string searchedLastName;
    //Person addressBookInputs[1000];
    vector<Person> addressBookInputs;
    inputsCount = getInputsFromFile(addressBookInputs, inputsCount);

    while(1)
    {
        system("cls");
        cout << "<<<<< KSIAZKA ADRESOWA >>>>>" << endl << endl;
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie osoby" << endl;
        cout << "9. Zakoncz program" << endl;

        selection = getChar();

        switch (selection)
        {
        case '1':
            inputsCount = addInput(addressBookInputs, inputsCount);
            break;
        case '2':
            cout << "Podaj imie osoby do wyszukania: ";
            cin >> searchedFirstName;
            searchBy(addressBookInputs, inputsCount, "imie", searchedFirstName);
            break;
        case '3':
            cout << "Podaj nazwisko osoby do wyszukania: ";
            cin >> searchedLastName;
            searchBy(addressBookInputs, inputsCount, "nazwisko", searchedLastName);
            break;
        case '4':
            showAllInputs(addressBookInputs, inputsCount);
            break;
        case '9':
            exit(0);
            break;
        }
    }

    return 0;
}
