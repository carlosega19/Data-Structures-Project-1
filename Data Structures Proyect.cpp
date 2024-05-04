/*
	V-0.0
	Carlos Galino
	Andres De Quintal
*/
#include <iostream>
#include <fstream>
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
	string code;
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
	string address;
	string tlf;
	/* Pointers */
	product* products = NULL;
	branch* next;
};



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

void menuMantProds(){
     system("cls");
	menuHeader();

     string subtitle = "1.1 MANTENIMIENTO PRODUCTOS";
	string op1 = "1.1. 1. AGREGAR";
	string op2 = "1.1. 2. MODIFICAR";
	string op3 = "1.1. 3. ELIMNAR";
	string op4 = "1.1. 4. CONSULTA POR CÓDIGO";
	string op5 = "1.1. 5. CONSULTA POR DESCRIPCION";
	string op6 = "1.1. 6. MOSTRAR TODOS LOS PRODUCTOS";
	string op0 = "0. VOLVER A MENÚ ANTERIOR.";
	string msg = "Su opcion (0-6) : _|";


     cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
	cout << line << endl;
	cout << setw((lineWidth + op1.length()) / 2) << op1 << endl;
	cout << setw((lineWidth + op2.length()) / 2) << op2 << endl;
	cout << setw((lineWidth + op3.length()) / 2) << op3 << endl;
	cout << setw((lineWidth + op4.length()) / 2) << op4 << endl;
	cout << setw((lineWidth + op5.length()) / 2) << op5 << endl;
	cout << setw((lineWidth + op6.length()) / 2) << op6 << endl;
	cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
	cout << setw((lineWidth + msg.length()) / 2) << msg << endl;
	cout << line << endl;
}

void menuMantBranchs(){
     system("cls");
	menuHeader();

     string subtitle = "1.1 MANTENIMIENTO SUCURSALES";
	string op1 = "1.2.1. AGREGAR";
	string op2 = "1.2.2. MODIFICAR";
	string op3 = "1.2.3. ELIMNAR";
	string op4 = "1.2.4. CONSULTA POR CÓDIGO";
	string op5 = "1.2.5. CONSULTA POR DESCRIPCION";
	string op6 = "1.2.6. MOSTRAR TODOS LOS PRODUCTOS";
	string op7 = "1.2.7. INVENTARIO";
	string op0 = "0. VOLVER A MENÚ ANTERIOR.";
	string msg = "Su opcion (0-7) : _|";


     cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
	cout << line << endl;
	cout << setw((lineWidth + op1.length()) / 2) << op1 << endl;
	cout << setw((lineWidth + op2.length()) / 2) << op2 << endl;
	cout << setw((lineWidth + op3.length()) / 2) << op3 << endl;
	cout << setw((lineWidth + op4.length()) / 2) << op4 << endl;
	cout << setw((lineWidth + op5.length()) / 2) << op5 << endl;
	cout << setw((lineWidth + op6.length()) / 2) << op6 << endl;
	cout << setw((lineWidth + op7.length()) / 2) << op7 << endl;
	cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
	cout << setw((lineWidth + msg.length()) / 2) << msg << endl;
	cout << line << endl;
}

void menu() {
	system("cls");
	// Ancho total deseado de la l�nea
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

/* Functions */
void addBranch(branch**B , branch**L, int codeP , string name, string city , string state , string address , string tlf) {
	branch* newB = new branch;
	newB->code = codeP;
	newB->name = name;
	newB->city = city;
	newB->state = state;
	newB->address = address;
	newB->tlf = tlf;
	/* Update the head of the list */
     if (!(*B))
     {
          newB->next = *B;
	     *B = newB;
          *L = newB;
     }
     else{
          newB->next = NULL;
          (*L)->next = newB;
          *L = newB;
     }
}

void createBranch(branch**B , branch**L) {
	string name;
	string city;
	string state;
	string address;
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
	getline(cin, address);
	fflush(stdin);
	cout << "\n\t- Escribe el numero telefonico de la nueva sucursal - (xxx) xxxxxxx: ";  
	getline(cin, tlf);
	fflush(stdin);

	if (name.empty() || city.empty() || state.empty() || address.empty() || tlf.empty()  ) {
		cout << " \n\n!!!Campos no rellenados correctamente!!!\n\n"; //Provisional
	}
	else
	{
		addBranch(B, L, ++code, name, city, state, address, tlf);
	}
}

int deleteBranch(branch**B , branch**L, int z){
     if (!(*B)) return 0;
     branch*ax = *B , *temp;
     if (ax->code == z)
     {
          temp = ax;
          (*B) = (*B)->next;
          delete temp;
          return 1;
     }
     else{
          while (ax->next && ax->next->code != z)
          {
               ax =ax->next;
          }
          if (ax->next)
          {
               if (ax->next == *L)
               {
                    temp = ax->next;
                    ax->next = temp->next;
                    delete temp;
                    *L = ax;
               }
               else{
                    temp = ax->next;
                    ax->next = temp->next;
                    delete temp;
               }
               
               return 1;
          }
     }
     return 0;
}

void printBranchs(branch*B) {
	if (!B) {
		return;
	}
	cout << "\n\t - " << B->name << " [" << B->code<<"]";
	//cout << "\n\t\t ~ Direccion: "<<B->city<<", "<<B->state<<", "<<B->address;
	//cout << "\n\t\t ~ Telefono: "<<B->tlf<<"\n\n";
	printBranchs(B->next);
}

branch* searchBranchByCode(branch*B , int codeB){
     if (!B) return NULL;
     if (B->code == codeB) return B;
     return searchBranchByCode(B->next , codeB);
}

branch *selectBranchByCode(branch *B){
     int codeSelect;
     printBranchs(B);
     cout<<"\n\n\n\tIngrese el codigo de la sucursal entre []: ";
     cin >> codeSelect;
     return searchBranchByCode(B , codeSelect);
}

void optionsModBranch(branch*selected){
     system("cls");

     menuHeader();
     string subtitle = "MODIFICAR";
	string op1 = "1. NOMBRE";
	string op2 = "2. ESTADO";
	string op3 = "3. CIUDAD";
	string op4 = "4. DIRECCION";
	string op5 = "5. TELEFONO";
	string op0 = "0. VOLVER A MENÚ ANTERIOR.";
	string msg = "Su opcion (0-5) : _|";


     cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
	cout << line << endl;
	cout << setw((lineWidth + op1.length()) / 2) << op1 << endl;
	cout << setw((lineWidth + op2.length()) / 2) << op2 << endl;
	cout << setw((lineWidth + op3.length()) / 2) << op3 << endl;
	cout << setw((lineWidth + op4.length()) / 2) << op4 << endl;
	cout << setw((lineWidth + op5.length()) / 2) << op5 << endl;
	cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
	cout << setw((lineWidth + msg.length()) / 2) << msg << endl;
	cout << line << endl;
     cout<<"\nSucursal seleccionada: "<<selected->name<<endl;
     cout << "\nIngresa la opcion a modificar: ";
}

void menuModBranch(branch *B){
     branch* selected = selectBranchByCode(B);
     if (!selected)
     {
          cout << "Sucursal no encontrada\n\n";
          system("pause");
     }
     else{
          int op;
          string userEntry;
          do
          {
               optionsModBranch(selected);
               cin >> op;
               fflush(stdin);
               switch (op)
               {
                    case 1:
                         cout<<"Nombre anterior: "<<selected->name<<endl;
                         cout<<"Nuevo nombre: ";
                         getline(cin , userEntry);
                         selected->name = userEntry;
                         break;
                    case 2:
                         cout<<"Estado anterior: "<<selected->state<<endl;
                         cout<<"Nuevo estado: ";
                         getline(cin , userEntry);
                         selected->state = userEntry;
                         break;
                    case 3:
                         cout<<"Ciudad anterior: "<<selected->city<<endl;
                         cout<<"Nueva ciudad: ";
                         getline(cin , userEntry);
                         selected->city = userEntry;
                         break;
                    case 4:
                         cout<<"Direccion anterior: "<<selected->address<<endl;
                         cout<<"Nueva ciudad: ";
                         getline(cin , userEntry);
                         selected->address = userEntry;
                         break;
                    case 5:
                         cout<<"Telefono anterior: "<<selected->tlf<<endl;
                         cout<<"Nueva ciudad: ";
                         getline(cin , userEntry);
                         selected->tlf = userEntry;
                         break;
               }
               fflush(stdin);
          } while (op != 0);
     }
}

void menuDeleBranch(branch**B,branch**L){
     system("cls");
     menuHeader();
     string subtitle = "ELIMINAR SUCURSAL";
     cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
	cout << line << endl;

     branch*selected = selectBranchByCode(*B);
     if (selected)
     {
          deleteBranch(B , L , selected->code);
     }
     else{
          cout << "\n\tSucursal no encontrada\n\n";
     }
}

void menuConsultByCode(branch*B){
     system("cls");
     menuHeader();
     string subtitle = "CONSULTAR SUCURSAL POR CODIGO";
     cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
	cout << line << endl;
     branch* selected = selectBranchByCode(B);
     if (selected)
     {
          system("cls");
          menuHeader();
          cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
          cout << line << endl;
          cout << "\n\tSUCURSAL ENCONTRADA: \n";
          cout << "\n\t - " << selected->name << " [" << selected->code<<"]";
          cout << "\n\t\t ~ Direccion: "<<selected->city<<", "<<selected->state<<", "<<selected->address;
          cout << "\n\t\t ~ Telefono: "<<selected->tlf<<"\n\n";
     }
     else{
          cout<<"\n -- Sucursal INEXISTENTE --\n\n\n";
     }
     system("pause");
}

/* FILE MANAGMENT */
void readBranchs(branch**B , branch**L){
     ifstream archivo("C:\\Users\\aabre\\OneDrive\\Documents\\UCAB\\SEGUNDO SEMESTRE\\Estructuras de Datos\\Proyecto FASE 1\\Data Structures Proyect\\data\\branchs.txt");
     if (archivo.fail()) return; 
     string n, s , c , d , t , line;
     while (getline(archivo , line))
     {
          istringstream ss(line);
          string dato;
          
          for (int i = 1; i < 6; i++)
          {
               getline(ss , dato , ',');
               switch (i)
               {
                    case 1:
                         n = dato;
                         break;
                    case 2:
                         s = dato;
                         break;
                    case 3:
                         c=dato;
                         break;
                    case 4:
                         d=dato;
                         break;
                    case 5:
                         t=dato;
                         break;
               }
          }
          addBranch(B ,L , ++code, n , c ,s , d ,t);
     }
}

void saveBranchs(branch*B){
     ofstream archivo("C:\\Users\\aabre\\OneDrive\\Documents\\UCAB\\SEGUNDO SEMESTRE\\Estructuras de Datos\\Proyecto FASE 1\\Data Structures Proyect\\data\\branchs.txt");
     if (archivo.is_open())
     {
          while (B)
          {
               archivo << B->name<<","<<B->state<<","<<B->city<<","<<B->address<<","<<B->tlf<<"\n";
               B = B->next;
          }
     }
}

/*void readProducts(){
     
}*/



/* -------------------------------------------------------------------- MAIN -------------------------------------------------------------------- */
int main() {
	int op;
     branch* branchs = NULL;
     branch* last = NULL;
     readBranchs(&branchs , &last);
     if (last)
     {
          code = last->code;
     }
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
                                   do
                                   {
                                        menuMantProds();
                                        cin >> op;
                                        
                                        /* In progress */
                                   } while (op != 0);
                                   op = -1;
							break;
						case 2: // Mantenimiento Sucursales
							do
                                   {
                                        menuMantBranchs();
                                        cin >> op;
                                        switch (op)
                                        {
                                             case 1: // Add Branch
                                                  createBranch(&branchs , &last);
                                                  break;
                                             case 2: // Modify Branch
                                                  menuModBranch(branchs);
                                                  break;
                                             case 3: // Delete Branch
                                                  menuDeleBranch(&branchs , &last);
                                                  break;
                                             case 4: // Consult By Code
                                                  menuConsultByCode(branchs);
                                                  break;
                                        }
                                   } while (op != 0);
                                   op = -1;
							break;
					}
					/*---------- FIN MANTENIMIENTO ----------*/
					
				} while (op != 0);
				op = -1;
				break;
			case 2: 
				// No available
                    printBranchs(branchs);
				break;
			case 3:
				// No available
				break;
		}
	} while (op != 0);
	saveBranchs(branchs);
     return 0;
}