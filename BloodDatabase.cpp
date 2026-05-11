
/*
    Proyecto: BloodDatabase (Adaptado)
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Descripción:
    Este proyecto gestiona una base de datos de donantes de sangre, proporcionando 
    funcionalidades para registrar, buscar y analizar la información de los donantes.

    El código se basó en el proyecto BloodDatabase, fue traducido al español 
    y adaptado a las necesidades del curso.

    

    Autor: Victor Bucheli
    Correo: victor.bucheli@correounivalle.edu.co
    Fecha: Octubre 2024
*/
#include "BloodDatabase.h"
#include <iostream>
#include <fstream>//Dedicado a leer, escribir y editar archivos (:O)
#include <string>
#include <vector>
#include <sstream>//Parcela el text.txt
#include <limits>
#include <stdexcept>//Manejo de excepciones/errores
#include <cctype>//Verifica tipo de string(digitos, letras, etc)
#include <algorithm>//Permite simplificar operaciones (más que todo iterativas)

using namespace std;

void BloodDatabase::displayProvinces() {
    cout << "Elige el departamento:\n";
    cout << "1. Putumayo\n";
    cout << "2. Cauca\n";
    cout << "3. Valle del Cauca\n";
    cout << "4. Amazonas\n";
    cout << "5. Risaralda\n";
    cout << "6. Antioquia\n";
    cout << "7. Norte de Santander\n";
    cout << "8. Chocó\n";
    cout << "9. Arauca\n";
    cout << "10. Guainía\n";
}

void BloodDatabase::displayBloodTypes() {
    cout << "Elige el tipo de Sangre:\n";
    cout << "1. A+\n";
    cout << "2. A-\n";
    cout << "3. B+\n";
    cout << "4. B-\n";
    cout << "5. AB+\n";
    cout << "6. AB-\n";
    cout << "7. O+\n";
    cout << "8. O-\n";
}

void BloodDatabase::clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    //   system("clear");
#endif
}

void BloodDatabase::waitForKeyPress() {
    cout << "Presiona cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

long BloodDatabase::getValidatedInput(const string& prompt) {
    long value;
    string input;
    while (true) {
        cout << prompt;//No parece hacer nada, pero es necesario para que el programa sepa qué input validar
        getline(cin, input);
        try {
            if (!all_of(input.begin(), input.end(), ::isdigit)) {
                throw invalid_argument("La entrada contiene caracteres no numéricos");
            }
            else {
                value = stol(input);
                return value;
            }
            break; // si la conversión es exitosa, salir del bucle
        } catch (const invalid_argument& e) {
            cout << "Entrada no válida: " << e.what() << ". Por favor ingrese un número válido." << endl;
        } catch (const out_of_range&) {
            cout << "Entrada fuera de rango. Por favor ingrese un número válido." << endl;
        }
    }
}

void BloodDatabase::getDonorDetails() {
    clearConsole();
    cout << "Ingrese los detalles del donante\n";

    Donor newDonor;
    newDonor.donorId = getValidatedInput("Id: ");
    cout << "Nombre: ";
    getline(cin, newDonor.name);
    cout << "Dirección: ";
    getline(cin, newDonor.address);

    displayProvinces();
    newDonor.district = getValidatedInput("departamento (ingrese el número correspondiente): ");
    displayBloodTypes();
    newDonor.bloodType = getValidatedInput("Tipo de sangre (ingrese el número correspondiente): ");
    newDonor.number = getValidatedInput("Número: ");

    donors.push_back(newDonor);
}

void BloodDatabase::writeDataToFile() {
    ofstream outfile(fileName, ios::app);

    if (!outfile) {
        cout << "Error al abrir el archivo para escribir." << endl;
        return;
    }

    Donor newDonor = donors.back();
    outfile << newDonor.donorId << ",    " << newDonor.name << ",    " << newDonor.address << ",    " << newDonor.district << ",    " << newDonor.bloodType << ",    " << newDonor.number << endl;

    outfile.close();
}

void BloodDatabase::searchAndDisplay() const {
    clearConsole();
    displayProvinces();
    int provinceName = getValidatedInput("Ingrese el número de la departamento: ");

    cout << "Ingrese la dirección (dejar en blanco para omitir): ";
    string addressFilter;
    getline(cin, addressFilter);

    bool choose;
    cerr << "Desea buscar por tipo de sangre? (1=Si, 0=No): ";
    cin >> choose;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descartar cualquier entrada extra
    string bloodTypeFilter;
    int bloodTypeSAD; //blootTypeSAD = BloodType Search And Display. Variable para almacenar el tipo de sangre filtrado como entero
    if (choose==1){
         displayBloodTypes();
        int bloodTypeSAD= getValidatedInput("Ingrese el tipo de sangre: ");
    }
    else {
        int bloodTypeSAD = 0;
    }; //Departamento 0 no existe, así que no afectará los resultados

    ifstream inFile(fileName);

    if (!inFile) {
        cout << "Error al abrir el archivo para leer." << endl;
        return;
    }

    vector<Donor> donors;
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        Donor d = Donor::parseLine(line);
        bool match = d.district == provinceName &&
            (addressFilter.empty() || d.address.find(addressFilter) != string::npos) &&
            (bloodTypeFilter.empty() || d.bloodType == bloodTypeSAD);

        if (match) {
            donors.push_back(d);
            found = true;
        }
    }

    if (!found) {
        cout << "No se encontraron personas de la departamento " << provinceName;
        if (!addressFilter.empty()) {
            cout << " con dirección que contiene '" << addressFilter << "'";
        }
        if (!bloodTypeFilter.empty()) {
            cout << " y tipo de sangre '" << bloodTypeFilter << "'";
        }
        cout << "." << endl;
    } else {
        cout << "Personas de la departamento " << provinceName;
        if (!addressFilter.empty()) {
            cout << " con dirección que contiene '" << addressFilter << "'";
        }
        if (!bloodTypeFilter.empty()) {
            cout << " y tipo de sangre '" << bloodTypeFilter << "'";
        }
        cout << ":" << endl;
        for (const auto& d : donors) {
            cout << "Nombre: " << d.name << endl;
            cout << "Dirección: " << d.address << endl;
            cout << "departamento: " << d.district << endl;
            cout << "Tipo de sangre: " << d.bloodType << endl;
            cout << "Número de móvil: " << fixed <<setprecision(0) << d.number << endl;//setprecision(0) para mostrar el número sin anotación científica
            cout << endl;
        }
    }

    inFile.close();
    waitForKeyPress();
}

void BloodDatabase::deleteDonor(const string& donorName) {
    ifstream inFile(fileName);
    ofstream tempFile("temp.txt");

    if (!inFile) {
        cerr << "Error al abrir el archivo " << fileName << endl;
        return;
    }

    if (!tempFile) {
        cerr << "Error al crear el archivo temporal" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        Donor d = Donor::parseLine(line);
        if (d.name == donorName) {
            found = true;
            cout << endl;
            cout << "- - - - - - - - - - - - - -" << endl;
            cout << "Nombre: " << d.name << endl;
            cout << "Dirección: " << d.address << endl;
            cout << "Departamento: " << Donor::getProvince(d.district) << endl;
            cout << "Tipo de sangre: " << Donor::getBloodType(d.bloodType) << endl;//Cambio a función getBloodType de Donor para mostrar el tipo de sangre en formato legible
            cout << "Número de móvil: " << d.number << endl;
            cout << "- - - - - - - - - - - - - -" << endl;
            cout << endl;
            cout << "¿Está seguro de que desea eliminar al donante? [s/n]: ";
            char sureChoice;
            cin >> sureChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descartar cualquier entrada extra

            if (sureChoice == 's' || sureChoice == 'S') {
                continue;
            }
            else if (sureChoice == 'n' || sureChoice == 'N') {
            }
        }

        tempFile << d.donorId << ",    " << d.name << ",    " << d.address << ",    " << d.district << ",    " << d.bloodType << ",    " << d.number << endl;
    }

    inFile.close();
    tempFile.close();

    if (remove(fileName.c_str()) != 0) {
        cerr << "Error al eliminar el archivo original" << endl;
        return;
    }

    if (rename("temp.txt", fileName.c_str()) != 0) {
        cerr << "Error al renombrar el archivo temporal" << endl;
        return;
    }

    if (!found) {
        cout << "No se encontró ningún donante con el nombre " << donorName << endl;
    }
}

    