// Pila_Cola.cpp: define el punto de entrada de la aplicaci�n de consola.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

//******************************************
typedef struct TArticulo
{
	int Codigo;
	char Nombre[20];
	int Disponible;
	float Precio;
	TArticulo* Siguiente;
}*PtrTArticulo;

//******************************************
int i;  //parametro global

void InicializarInventario(PtrTArticulo& Lista) {
	Lista = NULL;
}

void DestruirInventario(PtrTArticulo& Lista) {
	PtrTArticulo Aux;
	Aux = Lista;
	while (Aux != NULL) {
		Lista = Lista->Siguiente;
		delete(Aux);
		Aux = Lista;
	}
}

PtrTArticulo CrearArticulo(int NCodigo, int NDisponible, float NPrecio) {
	PtrTArticulo Pieza = new(TArticulo);
	char buffer[5];

	Pieza->Codigo = NCodigo;
	Pieza->Disponible = NDisponible;
	Pieza->Precio = NPrecio;

	strcpy_s(Pieza->Nombre, "Pieza");
	_itoa_s(NCodigo, buffer, 10);
	strcat_s(Pieza->Nombre, buffer);

	Pieza->Siguiente = NULL;
	return Pieza;
}

void AgregarInicioInventario(PtrTArticulo& Lista, PtrTArticulo& Nuevo) {
	Nuevo->Siguiente = Lista;
	Lista = Nuevo;
}

void AgregarFinalInventario(PtrTArticulo& Lista, PtrTArticulo& Nuevo) {
	PtrTArticulo Aux;
	Aux = Lista;
	if (Aux != NULL) {
		while (Aux->Siguiente != NULL) {
			Aux = Aux->Siguiente;
		}
		Aux->Siguiente = Nuevo;
	}
	else {
		Lista = Nuevo;
	}
}

void ListarInventario(PtrTArticulo& Lista) {
	int Contador = 1;
	PtrTArticulo Aux;
	Aux = Lista;
	while (Aux != NULL) {
		printf(" %d ", Contador);
		printf("%d ", Aux->Codigo);
		printf("%s ", Aux->Nombre);
		printf(" %d ", Aux->Disponible);
		printf(" %f\n ", Aux->Precio);
		Aux = Aux->Siguiente;
		Contador++;
	}
}

PtrTArticulo BuscarArticulo(PtrTArticulo& Lista, int cual) {
	return Lista;
}

void GuardarInventario(PtrTArticulo Lista) {
	FILE* archivo;
	fopen_s(&archivo, "ARCHIVO.txt", "w+");
	if (NULL == archivo) {
		printf("No se pudo abrir el archivo.");
	}
	else {
		PtrTArticulo AUX = Lista;
		while (AUX != NULL) {
			fprintf(archivo, "%i\n", AUX->Codigo);
			fprintf(archivo, "%s\n", AUX->Nombre);
			fprintf(archivo, "%i\n", AUX->Disponible);
			fprintf(archivo, "%f\n", AUX->Precio);
			AUX = AUX->Siguiente;
		}
	}
	fclose(archivo);
}

void CargarInventario(PtrTArticulo& Lista) {
	PtrTArticulo Nuevo;
	FILE* archivo;
	fopen_s(&archivo, "ARCHIVO.txt", "r");
	if (NULL == archivo) {
		printf("No se pudo abrir el archivo");
	}
	else {
		while (!feof(archivo)) {
			Nuevo = new(TArticulo);
			char Cadena[20];
			fscanf_s(archivo, "%i\n", &Nuevo->Codigo);
			fscanf_s(archivo, "%s\n", Cadena, 20);
			fscanf_s(archivo, "%i\n", &Nuevo->Disponible);
			fscanf_s(archivo, "%f\n", &Nuevo->Precio);
			strcpy_s(Nuevo->Nombre, Cadena);
			Nuevo->Siguiente = NULL;
			AgregarFinalInventario(Lista, Nuevo);

		}
	}
	fclose(archivo);
}

void Push(PtrTArticulo& Lista, PtrTArticulo Nuevo) {
	AgregarInicioInventario(Lista, Nuevo);
}

PtrTArticulo Top(PtrTArticulo& Lista) {
	return Lista;
}

PtrTArticulo Pop(PtrTArticulo& Lista) {
	PtrTArticulo Aux = Lista;
	Lista = Lista->Siguiente;
	Aux->Siguiente = NULL;
	return Aux;
}

void Encolar(PtrTArticulo& Lista, PtrTArticulo Nuevo) {
	AgregarFinalInventario(Lista, Nuevo);
}

PtrTArticulo Primero(PtrTArticulo& Lista) {
	return Lista;
}

PtrTArticulo Descolar(PtrTArticulo& Lista) {
	PtrTArticulo Aux = Lista;
	Lista = Lista->Siguiente;
	Aux->Siguiente = NULL;
	return Aux;
}

void main(int argc, char* argv[]) {
	//************************************************************************
	PtrTArticulo Pila_Llantas;
	PtrTArticulo Cola_Pasajeros; // de Bus
	PtrTArticulo Nuevo;
	int i;

	//************************************************************************
	InicializarInventario(Pila_Llantas);
	InicializarInventario(Cola_Pasajeros);
	int opc;
	bool menu = true;
	while (menu) {
		system("CLS");
		cout << " ********* Menu de pila *********" << endl << endl;
		cout << "  1. Usar Pila" << endl;
		cout << "  2. Usar cola" << endl;
		cout << "  3. Salir" << endl;
		cout << endl << "	Digite la opcion: ";
		cin >> opc;
		switch (opc) {
		case 1: {
			int opc;
			bool menu = true;
			while (menu) {
				system("CLS");
				cout << " ********* Submenu de pila *********" << endl << endl;
				cout << "  1. Push de 100 elementos" << endl;
				cout << "  2. Top" << endl;
				cout << "  3. Pop" << endl;
				cout << "  4. Salir" << endl;
				cout << endl << "	Digite la opcion: ";
				cin >> opc;
				switch (opc) {
				case 1: {// INSERTANDO CON PUSH
					system("CLS");
					cout << "Haciendo Push de 100 elementos" << endl;
					for (i = 1; i <= 100; i++) {
						Nuevo = CrearArticulo(i, i, i);
						Push(Pila_Llantas, Nuevo);
						cout << "Se acaba de hacer PUSH, el Top de la Pila ahora es: " << endl << Top(Pila_Llantas)->Codigo << endl;
					}
					system("pause");
					break;
				}
				case 2: {// PREGUNTANDO POR EL TOP
					system("CLS");
					if (Top(Pila_Llantas) != NULL) {
						cout << "El Top de la Pila es: " << endl << Top(Pila_Llantas)->Codigo << endl;
					}
					else {
						cout << "El Top de la Pila es: NULO " << endl;
					}
					system("pause");
					break;
				}
				case 3: { //SACANDO CON POP
					system("CLS");
					PtrTArticulo Aux = Pop(Pila_Llantas);
					if (Top(Pila_Llantas) != NULL) {
						cout << "Se acaba de hacer POP, el Top de la Pila ahora es: " << endl << Top(Pila_Llantas)->Codigo << endl;
					}
					else {
						cout << "Se acaba de hacer POP, el Top de la Pila ahora es:  NULO " << endl;
					}
					system("pause");
					break;
				}
				case 4: {// SALIENDO Y DEVOLVIENDO MEMORIA DINAMICA
					system("CLS");
					menu = false;
					system("CLS");
					cout << "Liberando memoria ... " << endl << endl << endl;
					DestruirInventario(Pila_Llantas);
					system("Pause");
					break;
				}
				}
			}
			system("pause");
			break;
		}
		case 2: {
			int opc;
			bool menu = true;
			while (menu) {
				system("CLS");
				cout << " ********* Submenu de cola *********" << endl << endl;
				cout << "  1. Encolar" << endl;
				cout << "  2. Primero" << endl;
				cout << "  3. Descolar" << endl;
				cout << "  4. Salir" << endl;
				cout << endl << "	Digite la opcion: ";
				cin >> opc;
				switch (opc) {
				case 1: {// ENCOLAR
					system("CLS");
					cout << "Haciendo Encolar de 50 elementos" << endl;

					for (i = 1; i <= 50; i++) {
						Nuevo = CrearArticulo(i, i, i);
						Encolar(Cola_Pasajeros, Nuevo);
						cout << "Se acaba de hacer ENCOLAR al final de la Cola de : " << Nuevo->Codigo << endl;
					}

					system("pause");
					break;
				}
				case 2: {// PRIMERO
					system("CLS");
					cout << "El primero que va a ser atendido de la cola es : " << Primero(Cola_Pasajeros)->Codigo << endl;
					system("pause");
					break;
				}
				case 3: {// DESCOLAR
					system("CLS");

					PtrTArticulo Aux = Descolar(Cola_Pasajeros);

					if (Primero(Cola_Pasajeros) != NULL) {
						cout << "Se acaba de hacer DESCOLAR, el nuevo primero  de la Cola ahora es: " << endl << Primero(Cola_Pasajeros)->Codigo << endl;
					}
					else {
						cout << "Se acaba de hacer DESCOLAR, el primero de la Cola ahora es:  NULO " << endl;
					}

					system("pause");
					break;
				}
				case 4: {// SALIENDO Y DEVOLVIENDO MEMORIA DINAMICA
					menu = false;
					system("CLS");
					cout << "Liberando memoria ... " << endl << endl << endl;
					DestruirInventario(Cola_Pasajeros);
					system("Pause");
					break;
				}
				}
			}
			system("pause");
			break;
		}
		case 3: {
			menu = false;
			system("CLS");
			cout << "Opcion 5: saliendo . . ." << endl << endl << endl;
			cout << "ADIOS!!!" << endl;
			system("Pause");
			break;
		}
		}
	}
}