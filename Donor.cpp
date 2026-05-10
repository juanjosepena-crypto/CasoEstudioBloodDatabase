
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
#include "Donor.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

void Donor::donorDetails() const {
    cout << "Nombre del donante: " << name << endl;
    cout << "Distrito del donante: " << district << endl;
    cout << "Tipo de sangre del donante: " << getBloodType(bloodType) << endl;
}

string Donor::getBloodType(int auxBloodType){
	switch(auxBloodType){
        case 1:
            return "A+";
		    break;
	    case 2:
		    return "A-";
		    break;
        case 3:
            return "B+";
		    break;
	    case 4:
		    return "B+";
		    break;
	    case 5:
		    return "AB";
		    break;
	    case 6:
		    return "AB";
		    break;
	    case 7:
		    return "O+";
		    break;
	    case 8:
		    return "O+";
		    break;
	    default:
            return "N/A";
		    cout<<"Dato de Sangre errado. Avisar al Administrador"<<endl;
        }
	}

Donor Donor::parseLine(const string& line) {
    Donor d;
    stringstream ss(line);
    string token;

    getline(ss, token, ','); d.donorId = stoi(trim(token));
    getline(ss, token, ','); d.name = trim(token);
    getline(ss, token, ','); d.address = trim(token);
    getline(ss, token, ','); d.district = stoi(trim(token));
    getline(ss, token, ','); d.bloodType = stoi(trim(token));
    getline(ss, token, ','); d.number = stoi(trim(token));

    return d;
}

string Donor::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
