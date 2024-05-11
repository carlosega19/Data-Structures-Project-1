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
#include <sstream>
#include <cctype>
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
	string code;
	string name;
	string city;
	string state;
	string address;
	string tlf;
	/* Pointers */
	product* products = NULL;
    product* lastP = NULL;
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
	string op6 = "1.2.6. MOSTRAR TODAS LAS SUCURSALES";
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
string tolow(string cad){
     for (int i = 0; i < cad.size(); i++)
     {
          cad[i] = tolower(cad[i]);
     }
     return cad;
}

/* PRODUCTS <----------------------------------------------------------------------------------------------------------------------------------------------------------*/
branch* searchBranchByCode(branch* B, string codeB) {
    if (!B) return NULL;
    if (tolow(B->code) == tolow(codeB)) return B;
    return searchBranchByCode(B->next, codeB);
}

bool searchBranchByCodeToF(branch* B, string codeB) {
    if (!B) return false;
    if (tolow(B->code) == tolow(codeB)) return true;
    return searchBranchByCodeToF(B->next, codeB);
}

branch* searchBranchByState(branch* B, string str) {
    if (!B) return NULL;
    if (tolow(B->state).find(tolow(str)) != string::npos) return B;
    return searchBranchByState(B->next, str);
}

branch* searchBranchByCity(branch* B, string str) {
    if (!B) return NULL;
    if (tolow(B->city).find(tolow(str)) != string::npos) return B;
    return searchBranchByState(B->next, str);
}

void addBranch(branch**B , branch**L, string codeB , string name, string city , string state , string address , string tlf) {
	branch* newB = new branch;
	newB->code = codeB;
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
	string name , city , state , address , tlf , code;
    bool invalidCode = true;
    cin.ignore();
    do
    {
        cout << "\n\t- Escribe el CODIGO de la nueva SUCURSAL: ";
        getline(cin, code);
        fflush(stdin);
        invalidCode = searchBranchByCode(*B, code);
        if (invalidCode)
        {
            cout << "\n\t\t -- CODIGO YA EXISTENTE -- \n\n";
        }
    } while (invalidCode);
	
    fflush(stdin);
	cout << "\n\t- Escribe el NOMBRE de la nueva SUCURSAL: "; 
	getline(cin ,name);
	fflush(stdin);
	cout << "\n\t- Escribe el ESTADO de la nueva SUCURSAL: ";  
	getline(cin, state);
	fflush(stdin);
	cout << "\n\t- Escribe la CIUDAD de la nueva SUCURSAL: ";  
	getline(cin, city);
	fflush(stdin);
	cout << "\n\t- Escribe la DIRECCION de la nueva SUCURSAL: ";  
	getline(cin, address);
	fflush(stdin);
	cout << "\n\t- Escribe el NUMERO TELEFONICO de la nueva SUCURSAL - (xxx) xxxxxxx: ";  
	getline(cin, tlf);
	fflush(stdin);

	if (name.empty() || city.empty() || state.empty() || address.empty() || tlf.empty() || code.empty() ) {
		cout << " \n\n!!!Campos no rellenados correctamente!!!\n\n"; //Provisional
	}
	else
	{
		addBranch(B, L, code, name, city, state, address, tlf);
	}
}

void deleteBranch(branch**B , branch**L, string z){
     if (!(*B)) return;
     branch*ax = *B , *temp;
     if (tolow(ax->code) == tolow(z))
     {
          temp = ax;
          (*B) = (*B)->next;
          delete temp;
     }
     else{
          while (ax->next && tolow(ax->next->code) != tolow(z)) ax = ax->next;
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
          }
     }
}

void printBranchs(branch*B) {
	if (!B) return;
	cout << "\n\t - " << B->name << " [" << B->code<<"]\n";
	//cout << "\n\t\t ~ Direccion: "<<B->city<<", "<<B->state<<", "<<B->address;
	//cout << "\n\t\t ~ Telefono: "<<B->tlf<<"\n\n";
	printBranchs(B->next);
}

branch* selectBranchByCode(branch* B) {
     string codeSelect;
     printBranchs(B);
     cin.ignore();
     fflush(stdin);
     cout << "\n\n\n\tIngrese el codigo de la sucursal entre []: ";
     getline(cin, codeSelect);
     return searchBranchByCode(B, codeSelect);
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
     string op6 = "6. CODIGO";
	string op0 = "0. VOLVER A MENÚ ANTERIOR.";
	string msg = "Su opcion (0-5) : _|";

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
     cout << "\n\tSUCURSAL ENCONTRADA: \n";
     cout << "\n\t - " << selected->name << " [" << selected->code << "]";
     cout << "\n\t\t ~ Direccion: " << selected->city << ", " << selected->state << ", " << selected->address;
     cout << "\n\t\t ~ Telefono: " << selected->tlf << "\n\n";
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
                         fflush(stdin);
                         cout<<"Nombre anterior: "<<selected->name<<endl;
                         cin.ignore();
                         cout<<"Nuevo nombre: ";
                         getline(cin , userEntry);
                         cout << "\n\tSeguro que desea modificar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                         cin >> op;
                         if (op == 1)
                         {
                              selected->name = userEntry;
                         }
                         else op = -1;
                         break;
                    case 2:
                         cout<<"Estado anterior: "<<selected->state<<endl;
                         cin.ignore();
                         cout<<"Nuevo estado: ";
                         getline(cin , userEntry);
                         cout << "\n\tSeguro que desea modificar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                         cin >> op;
                         if (op == 1)
                         {
                              selected->state = userEntry;
                         }
                         
                         break;
                    case 3:
                         cout<<"Ciudad anterior: "<<selected->city<<endl;
                         cin.ignore();
                         cout<<"Nueva ciudad: ";
                         getline(cin , userEntry);
                         cout << "\n\tSeguro que desea modificar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                         cin >> op;
                         if (op == 1)
                         {
                              selected->city = userEntry;
                         }
                         break;
                    case 4:
                         cout<<"Direccion anterior: "<<selected->address<<endl;
                         cin.ignore();
                         cout<<"Nueva ciudad: ";
                         getline(cin , userEntry);
                         cout << "\n\tSeguro que desea modificar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                         cin >> op;
                         if (op == 1)
                         {
                              selected->address = userEntry;
                         }
                         break;
                    case 5:
                         cout<<"Telefono anterior: "<<selected->tlf<<endl;
                         cin.ignore();
                         cout<<"Nueva ciudad: ";
                         getline(cin , userEntry);
                         cout << "\n\tSeguro que desea modificar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                         cin >> op;
                         if (op == 1)
                         {
                              selected->tlf = userEntry;
                         }
                         break;
                    case 6:
                         bool ininvalidCode = true;
                         cout << "Codigo anterior: " << selected->code << endl;
                         cin.ignore();
                         do
                         {
                              fflush(stdin);
                              cout << "Nuevo codigo: ";
                              getline(cin, userEntry);
                              ininvalidCode = searchBranchByCode(B, userEntry);
                              if (ininvalidCode)
                              {
                                   cout << "\n\t\t\t-- CODIGO YA EXISTENTE --\n\n";
                              }
                         } while (ininvalidCode);
                         cout << "\n\tSeguro que desea modificar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                         cin >> op;
                         if (op == 1)
                         {
                              selected->code = userEntry;
                         }
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
          cout << "\n\tSUCURSAL ENCONTRADA: \n";
          cout << "\n\t - " << selected->name << " [" << selected->code << "]";
          cout << "\n\t\t ~ Direccion: " << selected->city << ", " << selected->state << ", " << selected->address;
          cout << "\n\t\t ~ Telefono: " << selected->tlf << "\n\n";
          cout << "\n\tSeguro que desea eliminar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
          int op;
          cin >> op;
          if (op == 1) {
               deleteBranch(B, L, selected->code);
               cout << "\n\t-- SUCURSAL ELIMINADA --\n\n";
          }
     }
     else{
          cout << "\n\tSucursal no encontrada\n\n";
     }
     system("pause");
}

void menuConsultBranchByCode(branch*B){
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
          system("pause");
     }
     else{
          cout<<"\n -- Sucursal INEXISTENTE --\n\n\n";
     }
}

void menuConsultByState(branch*B ){
     system("cls");
     menuHeader();
     string userInput;
     string subtitle = "CONSULTAR SUCURSAL POR ESTADO";
     string op0 = "0. VOLVER A MENU ANTERIOR.";
     cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
	cout << line << endl;
     cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
     cout << line <<endl;
     cin.ignore();
     //fflush(stdin);
     cout << "\nIngresa el estado: ";
     getline(cin , userInput);
     if (userInput == "0") return;
     cout << "\n\tSUCURSALES ENCONTRADAS: \n";
     branch* selected = searchBranchByState(B , userInput);
     if (!selected) cout << "\n\n\t\tNINGUNA...\n\n";
     while (selected)
     {
         
         cout << "\n\t - " << selected->name << " [" << selected->code << "]";
         cout << "\n\t\t ~ Direccion: " << selected->city << ", " << selected->state << ", " << selected->address;
         cout << "\n\t\t ~ Telefono: " << selected->tlf << "\n\n";
          selected = searchBranchByState(selected->next , userInput);
     }
     system("pause");
}

void menuConsultByCity(branch* B) {
    system("cls");
    menuHeader();
    string userInput;
    string subtitle = "CONSULTAR SUCURSAL POR CIUDAD";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
    cout << line << endl;
    cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
    cout << line << endl;
    cin.ignore();
    //fflush(stdin);
    cout << "\nIngresa la ciudad: ";
    getline(cin, userInput);
    if (userInput == "0") return;
    cout << "\n\tSUCURSALES ENCONTRADAS: \n";
    branch* selected = searchBranchByCity(B, userInput);
    if (!selected) cout << "\n\n\t\tNINGUNA...\n\n";
    while (selected)
    {

        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Direccion: " << selected->city << ", " << selected->state << ", " << selected->address;
        cout << "\n\t\t ~ Telefono: " << selected->tlf << "\n\n";
        selected = searchBranchByCity(selected->next, userInput);
    }
    system("pause");
}

void menuConsultBranchByDesc(branch*B){
     string subtitle = "CONSULTAR SUCURSAL POR DESCRIPCION";
     string op1 = "1. ESTADO";
	string op2 = "2. CIUDAD";
     string op0 = "0. VOLVER A MENU ANTERIOR.";
     int op = -1;
     do
     {
          system("cls");
          menuHeader();
          cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
          cout << line << endl;
          cout << setw((lineWidth + op1.length()) / 2) << op1 << endl;
          cout << setw((lineWidth + op2.length()) / 2) << op2 << endl;
          cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
          cout << line <<endl;
          cin >> op;
          switch (op)
          {
               case 1:
                    menuConsultByState(B);
                    op = 0;
                    break;
               case 2:
                    menuConsultByCity(B);
                    break;
          }
     } while (op != 0);
}

/* PRODUCTS <----------------------------------------------------------------------------------------------------------------------------------------------------------*/

// SEARCHS A PRODUCT BY THE CODE
product* searchProductByCode(product*P, string str) {
    if (!P) return NULL;
    if (tolow(P->code) == tolow(str)) return P;
    return searchProductByCode(P->next, str);
}

//
product* searchProductByType(product* P, string des) {
    if (!P) return NULL;
    if (tolow(P->description).find(tolow(des)) != string::npos) return P;
    return searchProductByType(P->next, des);
}

product* searchProductByPrice(product* P, float price) {
    if (!P) return NULL;
    if (P->price == price) return P;
    return searchProductByPrice(P->next, price);
}

// DELETES A PRODUCTS OF LIST
void deleteProduct(product**P , product**L, string str) {
    if (!(*P)) return;
    product* ax = *P, * temp;
    if (tolow(ax->code) == tolow(str))
    {
        temp = ax;
        (*P) = (*P)->next;
        delete temp;
    }
    else
    {
        while (ax->next && ax->next->code != str) ax = ax->next;
        if (ax->next)
        {
            if (ax->next == *L)
            {
                temp = ax->next;
                ax->next = temp->next;
                delete temp;
                *L = ax;
            }
            else
            {
                temp = ax->next;
                ax->next = temp->next;
                delete temp;
            }
        }
    }
    

}

// ADDS A PRODUCT TO LIST
void addProduct(product** P, product** L, string codeP, string name, string description, float price , int amount , int minAmount) {
    product* newP = new product;
    newP->name = name;
    newP->description = description;
    newP->price = price;

    /* Default atributes */
    newP->code = codeP;
    newP->amount = amount;
    newP->minAmount = minAmount;

    /*Pointers*/
    if (!(*P))
    {
        newP->next = *P;
        *P = newP;
        *L = newP;
    }
    else
    {
        newP->next = NULL;
        (*L)->next = newP;
        *L = newP;
    }
}

// CONTROLLER CREATOR OF A PRODUCT
void createProduct(product**P , product**L){
    string code , name , description;
    float price;
    bool invalidCode = true;
    cin.ignore();
    do // IF THE CODE IS ALREADY TAKES, THE USER IS OBLIGATED TO TRY ANOTHER CODE
    {
        fflush(stdin);
        cout << "\n\t- Escribe el CODIGO del nuevo PRODUCTO: ";
        getline(cin, code);
        invalidCode = searchProductByCode(*P , code);
        if (invalidCode) cout << "\n\t\t-- CODIGO YA EXISTENTE --\n\n";
    } while (invalidCode);

    fflush(stdin);
    cout << "\n\t- Escribe el NOMBRE del nuevo PRODUCTO: ";
    getline(cin, name);
    fflush(stdin);
    cout << "\n\t- Escribe la DESCRIPCION del nuevo PRODUCTO: ";
    getline(cin, description);
    fflush(stdin);
    cout << "\n\t- Escribe el PRECIO del nuevo PRODUCTO (x.xx): ";
    cin >> price;
 
    if (name.empty() || description.empty() || price == NULL) {
        cout << " \n\n!!!Campos no rellenados correctamente!!!\n\n"; //Provisional
    }
    else
    {
        addProduct(P , L , code , name , description , price , 0 , 0);
    }
}

void printProduct(product*P) {
    if (!P) return;
    cout << "\n\t - " << P->name << " [" << P->code << "]";
    printProduct(P->next);
}

void showAllProducts(product*P) {
    system("cls");
    menuHeader();
    string subtitle = "LISTA DE PRODUCTOS";
    cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
    cout << line << endl;
    printProduct(P);
    cout << "\n\n";
    system("pause");
}

// RETURNS A SELECTED PRODUCT BY CODE
product* selectProductByCode(product* P) {
     string codeSelect;
     printProduct(P);
     cin.ignore();
     fflush(stdin);
     cout << "\n\n\n\tIngrese el codigo del producto entre []: ";
     getline(cin, codeSelect);
     return searchProductByCode(P, codeSelect);
}

// DISPLAY OPTIONS OF MODIFY PRODUCT
void optionsModProduct(product*selected) {
     system("cls");
     menuHeader();
     string subtitle = "MODIFICAR";
     string op1 = "1. NOMBRE";
     string op2 = "2. DESCRIPCION";
     string op3 = "3. PRECIO";
     string op4 = "4. CODIGO";
     string op0 = "0. VOLVER A MENÚ ANTERIOR.";
     string msg = "Su opcion (0-5) : _|";

     cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
     cout << line << endl;
     cout << setw((lineWidth + op1.length()) / 2) << op1 << endl;
     cout << setw((lineWidth + op2.length()) / 2) << op2 << endl;
     cout << setw((lineWidth + op3.length()) / 2) << op3 << endl;
     cout << setw((lineWidth + op4.length()) / 2) << op4 << endl;
     cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
     cout << setw((lineWidth + msg.length()) / 2) << msg << endl;
     cout << line << endl;
     cout << "\n\tSUCURSAL ENCONTRADA: \n";
     cout << "\n\t - " << selected->name << " [" << selected->code << "]";
     cout << "\n\t\t ~ Descripcion: " << selected->description;
     cout << "\n\t\t ~ Precio: " << selected->price << "$\n\n";
     cout << "\nIngresa la opcion a modificar: ";
}

// MODIFY PRODUCT
void menuModProduct(product* P) {
     system("cls");
     menuHeader();
     string subtitle = "CONSULTAR SUCURSAL POR DESCRIPCION";
     string op0 = "0. VOLVER A MENU ANTERIOR.";
     cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
     cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
     cout << line << endl;
     product* selected = selectProductByCode(P); // THE USER SELECT A PRODUCT
     if (!selected)
     {
          cout << "\n\n\t\t-- Producto no encontrado --\n\n";
          
     }
     else {
          int op;
          string userEntry;
          float userPrice;
          do
          {
               optionsModProduct(selected);
               cin >> op;
               fflush(stdin);
               switch (op)
               {
               case 1:
                    fflush(stdin);
                    cout << "Nombre anterior: " << selected->name << endl;
                    cin.ignore();
                    cout << "Nuevo nombre: ";
                    getline(cin, userEntry);
                    cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                    cin >> op;
                    if (op == 1)
                    {
                         selected->name = userEntry;
                    }
                    else op = -1;
                    break;
               case 2:
                    cout << "Descripcion anterior: " << selected->description << endl;
                    cin.ignore();
                    cout << "Nueva descripcion: ";
                    getline(cin, userEntry);
                    cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                    cin >> op;
                    if (op == 1)
                    {
                         selected->description = userEntry;
                    }
                    else op = -1;
               
                    
                    break;
               case 3:
                    cout << "Precio anterior: " << selected->price << endl;
                    cin.ignore();
                    cout << "Nuevo precio: ";
                    cin >> userPrice;
                    cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                    cin >> op;
                    if (op == 1)
                    {
                         selected->price = userPrice;
                    }
                    else op = -1;
                    break;
               case 4:
                    bool invalidCode = true;
                    cout << "Codigo anterior: " << selected->code << endl;
                    cin.ignore();
                    do
                    {
                         fflush(stdin);
                         cout << "Nuevo codigo: ";
                         getline(cin, userEntry);
                         invalidCode = searchProductByCode(P , userEntry);
                         if (invalidCode)
                         {
                         cout << "\n\t\t\t-- CODIGO YA EXISTENTE --\n\n";
                         }
                    } while (invalidCode);
                    cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                    cin >> op;
                    if (op == 1)
                    {
                         selected->code = userEntry;
                    }
                    else op = -1;
                    break;
               }
               fflush(stdin);
          } while (op != 0);
     }
     system("pause");
}

// DELETE PRODUCT
void menuDelProduct(product**P , product**L) {
     system("cls");
     menuHeader();
     string subtitle = "ELIMINAR PRODUCTO";
     string op0 = "0. VOLVER A MENU ANTERIOR.";
     cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
     cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
     cout << line << endl;
     product* selected = selectProductByCode(*P);
     if (selected)
     {
          cout << "\n\t - " << selected->name << " [" << selected->code << "]";
          cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\t\t ~ Precio: " << selected->price << "$\n\n";
          cout << "\n\tSeguro que desea ELIMINAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
          int op;
          cin >> op;
          if (op == 1)
          {
               deleteProduct(P , L , selected->code);
               cout << "\n\n\t\t-- PRODUCTO ELIMINADO --\n\n";
          }
     }
     system("pause");
}

// CONSULT A PRODUCT BY CODE
void menuConsultProductByCode(product* B) {
    system("cls");
    menuHeader();
    string subtitle = "CONSULTAR PRODUCTO POR CODIGO";
    cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
    cout << line << endl;
    product* selected = selectProductByCode(B);
    if (selected)
    {
        system("cls");
        menuHeader();
        cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
        cout << line << endl;
        cout << "\n\PRODUCTO ENCONTRADO: \n";
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\t\t ~ Precio: " << selected->price << "$\n\n";
        system("pause");
    }
    else {
        cout << "\n -- PRODUCTO INEXISTENTE --\n\n\n";
    }
}

void menuConsultProductByType(product* B) { // CAMBIAR EL "TYPE"
    system("cls");
    menuHeader();
    string userInput;
    string subtitle = "CONSULTAR PRODUCTOS POR DESCRIPCION";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
    cout << line << endl;
    cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
    cout << line << endl;
    fflush(stdin);
    cin.ignore();
    cout << "\nIngresa la descripcion: ";
    getline(cin, userInput);
    if (userInput == "0") return;

    cout << "\n\PRODUCTOS ENCONTRADOS: \n";
    product* selected = searchProductByType(B, userInput);
    if (!selected) cout << "\n\n\t\tNINGUNA...\n\n";
    while (selected)
    {
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\t\t ~ Precio: " << selected->price << "$\n\n";
        selected = searchProductByType(selected->next, userInput);
    }
    system("pause");
}

// CONSULT PRODUCT BY PRICE 
void menuConsultProductByPrice(product* B) { // CAMBIAR EL "TYPE"
    system("cls");
    menuHeader();
    float userInput;
    string subtitle = "CONSULTAR PRODUCTOS POR PRECIO";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
    cout << line << endl;
    cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
    cout << line << endl;
    fflush(stdin);
    cin.ignore();
    cout << "\nINGRESE EL PRECIO: ";
    cin >> userInput;
    if (userInput == 0) return;
    cout << "\n\PRODUCTOS ENCONTRADOS: \n";
    product* selected = searchProductByPrice(B, userInput);
    if (!selected) cout << "\n\n\t\tNINGUNA...\n\n";
    while (selected)
    {
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\t\t ~ Precio: " << selected->price << "$\n\n";
        selected = searchProductByPrice(selected->next, userInput);
    }
    system("pause");
}

// CONSULT A PRODUCT BY DESCRIPTION
void menuConsultProductByDesc(product* B) {
    string subtitle = "CONSULTAR PRODUCTO POR DESCRIPCION";
    string op1 = "1. DESCRIPCION";
    string op2 = "2. PRECIO";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    int op;
    do
    {
        system("cls");
        menuHeader();
        cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
        cout << line << endl;
        cout << setw((lineWidth + op1.length()) / 2) << op1 << endl;
        cout << setw((lineWidth + op2.length()) / 2) << op2 << endl;
        cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
        cout << line << endl;
        cin >> op;
        switch (op)
        {
        case 1:
            menuConsultProductByType(B);
            op = 0;
            break;
        case 2:
            menuConsultProductByPrice(B);
            break;
        }
    } while (op != 0);
}


void addProductToBranch(branch*B , product*P ,int amount , int minAmount) {
     addProduct(&B->products, &B->lastP, P->code, P->name, P->description, P->price , amount , minAmount);
}

void printProductsOfBranch(product*P) {
    if (!P) return;
    cout << "\n\t - " << P->name << " [" << P->code << "]";
    cout << "\n\t\t ~ Descripcion: " << P->description << "\n\t\t ~ Precio: " << P->price << "$";
}

void menuAddProductToBranch(branch*B, product*P) {
     int am, minAm;
     system("cls");
     menuHeader();
     string subtitle = "1.2.7.2 AGREGAR PRODUTO A SUCURSAL";
     string op0 = "0. VOLVER A MENU ANTERIOR.";
     cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
     cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
     cout << line << endl;
     product* selected = selectProductByCode(P);
     if (selected)
     {
          cout << "\n\t - " << selected->name << " [" << selected->code << "]";
          cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\t\t ~ Precio: " << selected->price << "$\n\n";
          cout << "\n\tIngresa la cantidad minima del producto: "; cin >> minAm;
          cout << "\n\tIngresa la cantidad del producto: "; cin >> am;
          if (am < minAm)
          {
              cout << "\n\t-- Cantidad a agregar NO puede ser menor a la minima --\n\n";
          }
          else {
              cout << "\n\tSeguro que desea agregar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
              int op;
              cin >> op;
              if (op == 1)
              {
                  addProductToBranch(B, selected , am , minAm);
                  cout << "\n\n\t\t-- PRODUCTO AGREGADO A SUCURSAL --\n\n";
              }
          }
       
     }
     else
     {
         cout << "\n -- PRODUCTO INEXISTENTE --\n\n\n";
     }
     system("pause");
}

// DELETE PRODUCT IN BRANCH
void menuDelProductOfBranch(product**P , product**L) {
    system("cls");
    menuHeader();
    string subtitle = "1.2.7.2. 3 BORRAR PRODUCTO DE SUCURSAL";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
    cout << setw((lineWidth + op0.length()) / 2) << op0 << endl;
    cout << line << endl;
    product* selected = selectProductByCode(*P);
    if (selected)
    {
        deleteProduct(P, L, selected->code);
        cout << "\n\t-- PRODUCTO ELIMINADO --\n\n";
    }
    else
    {
        cout << "\n -- PRODUCTO INEXISTENTE --\n\n";
    }
    system("pause");
}

void optionsModProductOfBranch(product*selected){
    system("cls");
    menuHeader();
    string subtitle = "MODIFICAR";
    string op1 = "1. NOMBRE";
    string op2 = "2. DESCRIPCION";
    string op3 = "3. PRECIO";
    string op4 = "4. CODIGO";
    string op5 = "5. CANTIDAD";
    string op6 = "6. CANTIDAD MINIMA";
    string op0 = "0. VOLVER A MENÚ ANTERIOR.";
    string msg = "Su opcion (0-5) : _";

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
    cout << "\n\tPRODUCTO ENCONTRADO: \n";
    cout << "\n\t - " << selected->name << " [" << selected->code << "]";
    cout << "\n\t\t ~ Descripcion: " << selected->description;
    cout << "\n\t\t ~ Precio: " << selected->price << "$";
    cout << "\n\t\t ~ Cantidad: " << selected->amount << "";
    cout << "\n\t\t ~ Cantidad MINIMA: " << selected->minAmount << "\n\n";
    cout << "\nIngresa la opcion a modificar: ";
}

void menuModProductOfBranch(product* P) {
    int op , userAm;
    float userPrice;
    string userEntry;
    system("cls");
    menuHeader();
    string subtitle = "MODIFICAR INVENTARIO";
    cout << setw((lineWidth + subtitle.length()) / 2) << subtitle << endl;
    cout << line << endl;
    product* selected = selectProductByCode(P);
    if (selected)
    {
        do
        {
            optionsModProductOfBranch(selected);
            cin >> op;
            fflush(stdin);
            switch (op)
            {
                case 1:
                    fflush(stdin);
                    cout << "Nombre anterior: " << selected->name << endl;
                    cin.ignore();
                    cout << "Nuevo nombre: ";
                    getline(cin, userEntry);
                    cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                    cin >> op;
                    if (op == 1)
                    {
                        selected->name = userEntry;
                    }
                    else op = -1;
                    break;
                case 2:
                    cout << "Descripcion anterior: " << selected->description << endl;
                    cin.ignore();
                    cout << "Nueva descripcion: ";
                    getline(cin, userEntry);
                    cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                    cin >> op;
                    if (op == 1)
                    {
                        selected->description = userEntry;
                    }
                    else op = -1;
                    break;
                case 3:
                    cout << "Precio anterior: " << selected->price << endl;
                    fflush(stdin);
                    cout << "Nuevo precio: ";
                    cin >> userPrice;
                    cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                    cin >> op;
                    if (op == 1)
                    {
                        selected->price = userPrice;
                    }
                    else op = -1;
                    break;
                case 4:
                    /*bool invalidCode = true;
                    cout << "Codigo anterior: " << selected->code << endl;
                    cin.ignore();
                    do
                    {
                        fflush(stdin);
                        cout << "Nuevo codigo: ";
                        getline(cin, userEntry);
                        invalidCode = searchProductByCode(P, userEntry);
                        if (invalidCode)
                        {
                            cout << "\n\t\t\t-- CODIGO YA EXISTENTE --\n\n";
                        }
                    } while (invalidCode);
                    cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                    cin >> op;
                    if (op == 1)
                    {
                        selected->code = userEntry;
                    }
                    else op = -1;*/
                    break;
                 case 5:
                     cout << "Cantidad anterior: "<<selected->amount<<endl;
                     cout << "Nueva cantidad: "; cin >> userAm;
                     cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                     cin >> op;
                     if (op == 1)
                     {
                         if (selected->minAmount > userAm)
                         {
                             cout << "\n\t\t-- Cantidad INVALIDA --\n\n";
                         }
                         else
                         {
                             selected->amount = userAm;
                         }
                     }
                     else op = -1;
                     break;
                 case 6:
                     cout << "Minima cantidad anterior: " << selected->minAmount << endl;
                     cout << "Nueva cantidad: "; cin >> userAm;
                     cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                     cin >> op;
                     if (op == 1)
                     {
                         if (userAm > selected->amount)
                         {
                             cout << "\n\t\t-- Cantidad INVALIDA --\n\n";
                         }
                         else
                         {
                             selected->minAmount = userAm;
                         }
                     }
                     else op = -1;
                     break;
            }
            fflush(stdin);
        } while (op != 0);
    }
}
/*
*/
void menuInventory(branch*B , product*P) {
     int op;
     branch* selected = NULL;
     do
     {
          system("cls");
          menuHeader();

          string subtitle = "SISTEMA DE INVENTARIO Y FACTURACION";
          string op1 = "1.2.7.1. SELECCIONAR SUCURSAL";
          string op2 = "1.2.7.2. AGREGAR PRODUCTOS";
          string op3 = "1.2.7.3. ELIMINAR PRODUCTOS";
          string op4 = "1.2.7.4. MODIFICAR INVENTARIO";
          string op5 = "1.2.7.5. MOSTRAR TODOS LOS PRODUCTOS";
          string op0 = "0. VOLVER A MENÚ ANTERIOR.";
          string msg = "Su opción (0-5) : _";

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
          cout << "\n\tSucursal seleccionada: ";
          if (!selected)
          {
               cout << "NINGUNA\n";
          }
          else
          {
               cout << selected->name << " [" << selected->code << "]\n\n";
          }
          cout << msg;
          cin >> op;
          fflush(stdin);
          switch (op)
          {
               case 1:
                    selected = selectBranchByCode(B);
                    cout << "\n\n";
                    break;
               case 2:
                    if (!selected)
                    {
                         cout << "\n\t\t\t-- SUCURSAL NO SELECCIONADA --\n\n";
                    }
                    else
                    {
                         menuAddProductToBranch(selected, P);
                    }
                    break;
               case 3:
                   menuDelProductOfBranch(&selected->products, &selected->lastP);
                   break;
               case 4:
                   menuModProductOfBranch(selected->products);
                   break;
               case 5:
                   if (!selected)
                   {
                       cout << "\n\t\t\t-- SUCURSAL NO SELECCIONADA --\n\n";
                   }
                   else
                   {
                       cout << "\n\nPRODUCTOS DE " << selected->name;
                       printProductsOfBranch(selected->products);
                       cout << "\n\n";
                       system("pause");
                   }
                   break;
          }
     } while (op != 0);
}

/* FILE MANAGMENT */
void readBranchs(branch**B , branch**L){ // Update the function to delete the trash in line
     ifstream archivo("C:\\Users\\aabre\\OneDrive\\Documents\\UCAB\\SEGUNDO SEMESTRE\\Estructuras de Datos\\Proyecto FASE 1\\Data Structures Proyect\\data\\branchs.txt");
     if (archivo.fail()) return; 
     string n, s , c , d , t , code ,line;
     while (getline(archivo , line))
     {
          istringstream ss(line);
          string dato;
          
          for (int i = 1; i < 7; i++)
          {
               getline(ss , dato , ',');
               switch (i)
               {
                    case 1:
                         code = dato;
                    case 2:
                         n = dato;
                         break;
                    case 3:
                         s = dato;
                         break;
                    case 4:
                         c=dato;
                         break;
                    case 5:
                         d=dato;
                         break;
                    case 6:
                         t=dato;
                         break;
               }
          }
          addBranch(B ,L , code, n , c ,s , d ,t);
     }
}

void saveBranchs(branch*B){ 
     ofstream archivo("C:\\Users\\aabre\\OneDrive\\Documents\\UCAB\\SEGUNDO SEMESTRE\\Estructuras de Datos\\Proyecto FASE 1\\Data Structures Proyect\\data\\branchs.txt");
     if (archivo.is_open())
     {
          while (B)
          {
               archivo << B->code << "," << B->name << "," << B->state << "," << B->city << "," << B->address << "," << B->tlf << "\n";
               B = B->next;
          }
     }
}

void readProducts(product** P, product** L) { // Update the function to delete the trash in line
     ifstream archivo("C:\\Users\\aabre\\OneDrive\\Documents\\UCAB\\SEGUNDO SEMESTRE\\Estructuras de Datos\\Proyecto FASE 1\\Data Structures Proyect\\data\\products.txt");
     if (archivo.fail()) return;
     string code, n, d,line;
     float price;
     while (getline(archivo, line))
     {
          istringstream ss(line);
          string dato;

          for (int i = 1; i < 5; i++)
          {
               getline(ss, dato, ',');
               switch (i)
               {
                    case 1:
                         code = dato;
                    case 2:
                         n = dato;
                         break;
                    case 3:
                         d = dato;
                         break;
                    case 4:
                         price = stof(dato);
                         break;
               }
          }
          addProduct(P, L, code, n, d, price, 0 , 0);
     }
}

void saveProducts(product* P) {
     ofstream file("C:\\Users\\aabre\\OneDrive\\Documents\\UCAB\\SEGUNDO SEMESTRE\\Estructuras de Datos\\Proyecto FASE 1\\Data Structures Proyect\\data\\products.txt");
     if (file.is_open())
     {
          while (P)
          {
               file << P->code << "," << P->name << "," << P->description << "," << P->price << "\n";
               P = P->next;
          }
     }
}

/* -------------------------------------------------------------------- MAIN -------------------------------------------------------------------- */
int main() {
	int op;
     branch* branchs = NULL;
     branch* lastB = NULL;

     product* products = NULL;
     product* lastP = NULL;
     // READ PRODUCTS
     readProducts(&products, &lastP);
     // READ BRANCHS
     readBranchs(&branchs , &lastB);
	do
	{
		menu();
		cin >> op;
          fflush(stdin);
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
                                        switch (op)
                                        {
                                             case 1: // Add Product
                                                  createProduct(&products, &lastP);
                                                  break;
                                            case 2: // MODIFY A PRODUCT
                                                  menuModProduct(products);
                                                  break;
                                            case 3: // DELETE A PRODUCT
                                                  menuDelProduct(&products , &lastP);
                                                  break;
                                            case 4:
                                                menuConsultProductByCode(products);
                                                break;
                                            case 5:
                                                menuConsultProductByDesc(products);
                                                break;
                                            case 6:
                                                showAllProducts(products);
                                                break;
                                        }
                                        /* In progress */
                                   } while (op != 0);
                                   op = -1;
							break;
						case 2: // Mantenimiento Sucursales
							do
                                   {
                                        fflush(stdin);
                                        menuMantBranchs();
                                        cin >> op;
                                        switch (op)
                                        {
                                             case 1: // Add Branch
                                                  createBranch(&branchs , &lastB);
                                                  break;
                                             case 2: // Modify Branch
                                                  menuModBranch(branchs);
                                                  break;
                                             case 3: // Delete Branch
                                                  menuDeleBranch(&branchs , &lastB);
                                                  break;
                                             case 4: // Consult By Code
                                                  menuConsultBranchByCode(branchs);
                                                  break;
                                             case 5: // Consult By Description
                                                  menuConsultBranchByDesc(branchs);
                                                  break;
                                             case 6: // Show All Branchs  
                                                  printBranchs(branchs);
                                                  system("pause");
                                                  break;
                                             case 7: // INVENTORY          (NOT FINISHED YET)
                                                  menuInventory(branchs , products);
                                                  break;
                                        }
                              } while (op != 0);
                                   op = -1;
							break;
					}
					/* ---------- FIN MANTENIMIENTO ---------- */
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
     saveProducts(products);
	saveBranchs(branchs);
     return 0;
}

/*
002357,Manzanas,Frutas,3.49
003489,Uvas,Frutas,5.99
004621,Naranjas,Frutas,2.79
005753,Piñas,Frutas,6.49
006885,Sandías,Frutas,7.99
007917,Melones,Frutas,4.29
008049,Fresas,Frutas,3.99
009181,Arándanos,Frutas,8.49
010313,Kiwis,Frutas,2.89
011445,Mangos,Frutas,5.79
012577,Peras,Frutas,3.69
013709,Duraznos,Frutas,4.59
014841,Cerezas,Frutas,6.99
015973,Limones,Frutas,1.99
017105,Plátanos,Frutas,3.29
018237,Papayas,Frutas,4.79
019369,Ciruelas,Frutas,2.49
020501,Granadas,Frutas,5.29
021633,Guayabas,Frutas,4.19
022765,Cocos,Frutas,6.79
023897,Tomates,Verduras,2.19
025029,Pepinos,Verduras,1.49
026161,Lechugas,Verduras,0.99
027293,Zanahorias,Verduras,1.79
028425,Pimientos,Verduras,3.09
029557,Brócoli,Verduras,2.39
030689,Coliflor,Verduras,2.69
031821,Espinacas,Verduras,1.89
032953,Calabacines,Verduras,2.09


A14,Farmatodo,  Distrito Capital ,Caracas, El Hatillo , 0424 2087154
B27, Supermercado Plaza ,  Distrito Capital , Caracas , Chacao , 0212 5558899
C42, Tienda Economica ,  Distrito Capital , Caracas , Sucre , 0212 3334477
D55, Mercado Popular ,  Distrito Capital , Caracas , Baruta , 0212 7776611
E68, Farmacia Los Dos ,  Distrito Capital , Caracas , El Cafetal , 0212 4447722
F81, Ferreteria El Martillo ,  Distrito Capital , Caracas , La Trinidad , 0212 6668833
G94,Centro Comercial Oasis ,  Distrito Capital , Caracas , Santa Fe , 0212 9991155
H107,Panaderia La Dulzura ,  Distrito Capital , Caracas , Los Palos Grandes , 0212 8889944
I120,Carniceria San Jose ,  Distrito Capital , Caracas , Los Dos Caminos , 0212 2228811
J133,Fruteria El Paraiso ,  Distrito Capital , Caracas , Las Mercedes , 0212 7773377
K146,Zapateria La Moda ,  Distrito Capital , Caracas , Altamira , 0212 3337722
L159,Libreria Los Libros ,  Distrito Capital , Caracas , Los Chorros , 0212 4441133
M172,Tienda de Ropa Fashion ,  Distrito Capital , Caracas , El Paraiso , 0212 5552266
N185,Mercado de Abastos ,  Distrito Capital , Caracas , Macarao , 0212 6665500
O198,Farmacia San Francisco ,  Distrito Capital , Caracas , La Candelaria , 0212 9998844
P211,Supermercado Caribe ,  Distrito Capital , Caracas , Catia , 0212 8886611
Q224,Ferreteria La Herradura ,  Distrito Capital , Caracas , Caricuao , 0212 7772200
R237,Centro Comercial Las Palmas ,  Distrito Capital , Caracas , Antimano , 0212 3334499
S250,Panaderia La Union ,  Distrito Capital , Caracas , La Vega , 0212 4441166
T263,Carniceria La Esquina ,  Distrito Capital , Caracas , La Pastora , 0212 5550033
U276,Ferreteria La Nacional ,  Distrito Capital , Caracas , El Valle , 0212 6666611
V289,Tienda de Muebles El Hogar ,  Distrito Capital , Caracas , El Junquito , 0212 9992200
W302,Supermercado La Economia ,  Distrito Capital , Caracas , Coche , 0212 8888844
X315,Farmacia Popular ,  Distrito Capital , Caracas , La Urbina , 0212 7771133
Y328,Centro Comercial El Centro ,  Distrito Capital , Caracas , La Yaguara , 0212 3335500
Z341,Panaderia La Estrella ,  Distrito Capital , Caracas , El Recreo , 0212 4446611
AA354,Tienda de Electronicos Electrica ,  Distrito Capital , Caracas , Petare , 0212 5554400
AB367,Ferreteria El Constructor ,  Distrito Capital , Caracas , El Cementerio , 0212 6668844
AC380,Centro Comercial El Dorado ,  Distrito Capital , Caracas , El Valle , 0212 9991133
AD393,Panaderia La Alegria ,  Distrito Capital , Caracas , La Paz , 0212 8885500
AE406,Carniceria La Reina ,  Distrito Capital , Caracas , El Paraiso , 0212 7778844
*/