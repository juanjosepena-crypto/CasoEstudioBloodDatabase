
/*
    Proyecto: BloodDatabase (Adaptado)
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Este es un proyecto del curso FPOO de la Universidad del Valle, 
    desarrollado con fines académicos. Puede ser utilizado con fines 
    académicos dando los créditos de la autoría.

    El código se basó en el proyecto BloodDatabase, fue traducido al español 
    y adaptado a las necesidades del curso.

    Autor: Victor Bucheli
    Correo: victor.bucheli@correounivalle.edu.co
    Fecha: Mayo 2026
*/

#include "BloodDatabase.h"
#include "Donor.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

int main() {
    string donorName;
    BloodDatabase database;
    int choice;

    while (true) {
        BloodDatabase::clearConsole();

        cout <<
             " ░█████╗░██████╗░██╗░░░██╗███████╗  ██████╗░░█████╗░░░░░░██╗░█████╗░\n"
             " ██╔══██╗██╔══██╗██║░░░██║╚════██║  ██╔══██╗██╔══██╗░░░░░██║██╔══██╗\n"
             " ██║░░╚═╝██████╔╝██║░░░██║░░███╔═╝  ██████╔╝██║░░██║░░░░░██║███████║\n"
             " ██║░░██╗██╔══██╗██║░░░██║██╔══╝░░  ██╔══██╗██║░░██║██╗░░██║██╔══██║\n"
             " ╚█████╔╝██║░░██║╚██████╔╝███████╗  ██║░░██║╚█████╔╝╚█████╔╝██║░░██║\n"
             " ░╚════╝░╚═╝░░╚═╝░╚═════╝░╚══════╝  ╚═╝░░╚═╝░╚════╝░░╚════╝░╚═╝░░╚═╝\n";

        cout << "1. Registrar donante\n";
        cout << "2. Buscar donante\n";
        cout << "3. Eliminar donante\n";
        cout << "4. Salir\n";
        cout << "Ingrese su elección: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descartar cualquier entrada extra

        switch (choice) {
        case 1:
            database.getDonorDetails();
            database.writeDataToFile();
            break;
        case 2:
            database.searchAndDisplay();
            break;
        case 3:
            cout << "Ingrese el nombre del donante a eliminar: ";
            getline(cin, donorName);
            database.deleteDonor(donorName);
            BloodDatabase::waitForKeyPress();
            break;
        case 4:
            database.displayBloodTypes();
            cout << "Gracias por usar el Sistema de la Cruz Roja" << endl;
            return 0;
        default:
            cout << "Opción no válida. Inténtalo de nuevo.\n";
            BloodDatabase::waitForKeyPress();
            break;
        }
    }
}

