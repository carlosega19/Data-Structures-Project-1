/*
	V-0.0
	Carlos Galino
	Andres De Quintal
*/
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <string>
using namespace std;
// GLOBAL VARIABLES
int code = 1;

struct product
{
	double code;
	string name;
	string description;
	int amount;
	int minAmount;
	float price;
	/* Pointer */
	product* next;
};

struct branch
{
	int code;
	string name;
	string city;
	string state;
	string direction;
	string tlf;
	/* Pointers */
	product* products = NULL;
	branch* next;
};

/* Functions */

void addBranch(branch**B , int codeP , string name, string city , string state , string direction , string tlf) {
	branch* newB = new branch;
	newB->code = codeP;
	newB->name = name;
	newB->city = city;
	newB->state = state;
	newB->direction = direction;
	newB->tlf = tlf;
	/* Update the head of the list */
	newB->next = *B;
	*B = newB;
}

void createBranch(branch**B) {
	string name;
	string city;
	string state;
	string direction;
	string tlf;
	cin.ignore();
	cout << "\n\t- Escribe el nombre de la nueva sucursal: "; 
	getline(cin ,name);
	fflush(stdin);
	cout << "\n\t- Escribe el estado de la nueva sucursal: ";  
	getline(cin, state);
	fflush(stdin);
	cout << "\n\t- Escribe la ciudad de la nueva sucursal: ";  
	getline(cin, city);
	fflush(stdin);
	cout << "\n\t- Escribe la direccion de la nueva sucursal: ";  
	getline(cin, direction);
	fflush(stdin);
	cout << "\n\t- Escribe el numero telefonico de la nueva sucursal - (xxx) xxxxxxx: ";  
	getline(cin, tlf);
	fflush(stdin);

	if (name.empty() || city.empty() || state.empty() || direction.empty() || tlf.empty()  ) {
		cout << " \n\n!!!Campos no rellenados correctamente!!!\n\n"; //Provisional
	}
	else
	{
		addBranch(B, ++code, name, city, state, direction, tlf);
	}
}

void printBranchs(branch*B) {
	if (!B) {
		cout << "\nFin\n";
		return;
	}
	cout << "\n\t - " << B->name << " [" << B->code<<"]";
	cout << "\n\t\t ~ Direccion: "<<B->city<<", "<<B->state<<", "<<B->direction;
	cout << "\n\t\t ~ Telefono: "<<B->tlf<<"\n\n";
	printBranchs(B->next);
}




















/* ------- Menu Managment  ------- */
int lineWidth = 120;
string line(lineWidth, '-');

void menuHeader() {
	string title = "SISTEMA DE INVENTARIO Y FACTURACION";
	cout << line << endl;
	cout << setw((lineWidth + title.length()) / 2) << title << endl;
	cout << line << endl;
}

void menuMant() {
	system("cls");
	menuHeader();
	string subtitle = "1. MANTENIMIENTO";
	string op1 = "1. PRODUCTOS";
	string op2 = "2. SUCURSALES";
	string op3 = "3. PERSONAS";
	string op0 = "0. VOLVER.";
	string msg = "Su opcion (0-3) : _|";

	cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
	cout << line << endl;
	cout << setw((lineWidth + op1.length()) / 2) << op1 << endl;
	cout << setw((lineWidth + op2.length()) / 2) << op2 << endl;
	cout << setw((lineWidth + op3.length()) / 2) << op3 << endl;
	cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
	cout << setw((lineWidth + msg.length()) / 2) << msg << endl;
	cout << line << endl;
}

void menu() {
	system("cls");
	// Ancho total deseado de la línea
	string subtitle = "MENU PRINCIPAL";
	string op1 = "1. MANTENIMIENTO";
	string op2 = "2. FACTURACION";
	string op3 = "3. REPORTES";
	string op0 = "0. SALIR.";
	string msg = "Su opcion (0-3) : _|";

	menuHeader();
	cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
	cout << line << endl;
	cout << setw((lineWidth + op1.length()) / 2) << op1 << endl;
	cout << setw((lineWidth + op2.length()) / 2) << op2 << endl;
	cout << setw((lineWidth + op3.length()) / 2) << op3 << endl;
	cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
	cout << setw((lineWidth + msg.length()) / 2) << msg << endl;
	cout << line << endl;
}

/* ---------------------------------- MAIN ---------------------------------- */
int main() {
	int op;
    branch* branchs = NULL;
	do
	{
		menu();
		cin >> op;
		switch (op)
		{
			case 1: // Mantenimiento
				do
				{
					menuMant();
					cin >> op;
					switch (op)
					{
						case 1: // Mantenimiento Productos
							createBranch(&branchs);
							system("pause");
							break;
						case 2:
							printBranchs(branchs);
							system("pause");
							break;
					}
					/**/
					
				} while (op != 0);
				op = -1;
				break;
			case 2: 
				// No available
				break;
			case 3:
				// No available
				break;

		}
	} while (op != 0);
	
    return 0;
}
