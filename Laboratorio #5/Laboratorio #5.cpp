// Pila_Cola.cpp: define el punto de entrada de la aplicación de consola.

// Inclusión de las librerías necesarias
#include <stdio.h>      // Para funciones estándar de entrada/salida (printf, scanf, etc.).
#include <stdlib.h>     // Para funciones estándar como malloc, free, etc.
#include <string.h>     // Para manipulación de cadenas de caracteres.
#include <iostream>     // Para entrada/salida con cin y cout.

using namespace std;    // Permite usar funciones del espacio de nombres std sin prefijo (ej. cout en vez de std::cout).

// Definición de la estructura TArticulo, que representa un artículo en el inventario
typedef struct TArticulo {
	int Codigo;               // Código único del artículo.
	char Nombre[20];          // Nombre del artículo (hasta 20 caracteres).
	int Disponible;           // Cantidad disponible del artículo.
	float Precio;             // Precio del artículo.
	TArticulo* Siguiente;     // Puntero al siguiente artículo (para listas enlazadas).
} *PtrTArticulo;              // PtrTArticulo es un alias para punteros a TArticulo.

// Declaración de una variable global
int i;  // Variable global (no se usa en el fragmento proporcionado, pero podría emplearse en otros apartados del código).

// Función para inicializar el inventario
void InicializarInventario(PtrTArticulo& Lista) {
	Lista = NULL; // Se inicializa la lista como vacía asignando NULL.
}

// Función para liberar la memoria de todos los nodos en el inventario
void DestruirInventario(PtrTArticulo& Lista) {
	PtrTArticulo Aux;          // Puntero auxiliar para recorrer la lista.
	Aux = Lista;               // Asigna el inicio de la lista al puntero auxiliar.
	while (Aux != NULL) {      // Mientras el puntero auxiliar no sea NULL...
		Lista = Lista->Siguiente; // Avanza al siguiente nodo en la lista.
		delete(Aux);           // Libera la memoria del nodo actual.
		Aux = Lista;           // Actualiza el puntero auxiliar al siguiente nodo.
	}
}

// Función para crear un nuevo artículo en el inventario
PtrTArticulo CrearArticulo(int NCodigo, int NDisponible, float NPrecio) {
	PtrTArticulo Pieza = new(TArticulo); // Reserva memoria para un nuevo nodo tipo TArticulo.
	char buffer[5];                      // Arreglo temporal para convertir el código a cadena.

	Pieza->Codigo = NCodigo;             // Asigna el código único del artículo.
	Pieza->Disponible = NDisponible;     // Asigna la cantidad disponible.
	Pieza->Precio = NPrecio;             // Asigna el precio del artículo.

	strcpy_s(Pieza->Nombre, "Pieza");    // Copia "Pieza" al campo Nombre del artículo.
	_itoa_s(NCodigo, buffer, 10);        // Convierte el código (NCodigo) a una cadena y la almacena en buffer.
	strcat_s(Pieza->Nombre, buffer);     // Concadena el código convertido al nombre "Pieza".

	Pieza->Siguiente = NULL;             // Inicializa el puntero Siguiente como NULL (el artículo aún no está enlazado).
	return Pieza;                        // Retorna el puntero al nuevo artículo creado.
}

void AgregarInicioInventario(PtrTArticulo &Lista, PtrTArticulo &Nuevo){
	Nuevo->Siguiente = Lista;
	Lista = Nuevo;
}

void AgregarFinalInventario(PtrTArticulo &Lista, PtrTArticulo &Nuevo){
	PtrTArticulo Aux;
	Aux = Lista;
	if (Aux != NULL){
		while (Aux->Siguiente != NULL){
			Aux = Aux->Siguiente;
		}
		Aux->Siguiente = Nuevo;
	}
	else{
		Lista = Nuevo;
	}
}

void ListarInventario(PtrTArticulo &Lista){
	int Contador = 1;
	PtrTArticulo Aux;
	Aux = Lista;
	while (Aux != NULL){
		printf(" %d ", Contador);
		printf("%d ", Aux->Codigo);
		printf("%s ", Aux->Nombre);
		printf(" %d ", Aux->Disponible);
		printf(" %f\n ", Aux->Precio);
		Aux = Aux->Siguiente;
		Contador++;
	}
}

PtrTArticulo BuscarArticulo(PtrTArticulo &Lista, int cual){
	return Lista;
}

void GuardarInventario(PtrTArticulo Lista){
	FILE *archivo;
	fopen_s(&archivo, "ARCHIVO.txt", "w+");
	if (NULL == archivo){
		printf("No se pudo abrir el archivo.");
	}
	else{
		PtrTArticulo AUX = Lista;
		while (AUX != NULL){
			fprintf(archivo, "%i\n", AUX->Codigo);
			fprintf(archivo, "%s\n", AUX->Nombre);
			fprintf(archivo, "%i\n", AUX->Disponible);
			fprintf(archivo, "%f\n", AUX->Precio);
			AUX = AUX->Siguiente;
		}
	}
	fclose(archivo);
}

void CargarInventario(PtrTArticulo &Lista){
	PtrTArticulo Nuevo;
	FILE *archivo;
	fopen_s(&archivo, "ARCHIVO.txt", "r");
	if (NULL == archivo){
		printf("No se pudo abrir el archivo");
	}
	else{
		while (!feof(archivo)){
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

void Push(PtrTArticulo &Lista, PtrTArticulo Nuevo){
    // Esta función agrega un nuevo artículo al principio de la lista.
    // Utiliza la función AgregarInicioInventario para enlazar el nuevo artículo con la cabeza de la lista.
    AgregarInicioInventario(Lista, Nuevo);
}

PtrTArticulo Top(PtrTArticulo &Lista){
    // Esta función devuelve el primer artículo en la lista, es decir, la cabeza de la lista.
    // No modifica la lista, solo devuelve el puntero al primer nodo.
    return Lista;
}

PtrTArticulo Pop(PtrTArticulo &Lista){
    // Esta función elimina el primer artículo de la lista.
    // Guarda la cabeza de la lista en 'Aux', luego actualiza la cabeza de la lista al siguiente artículo.
    // Establece el puntero 'Siguiente' de 'Aux' como NULL y devuelve el artículo eliminado.
    PtrTArticulo Aux = Lista;
    Lista = Lista->Siguiente;
    Aux->Siguiente = NULL;
    return Aux;
}

void Encolar(PtrTArticulo &Lista, PtrTArticulo Nuevo){
    // Esta función agrega un nuevo artículo al final de la lista.
    // Utiliza la función AgregarFinalInventario para enlazar el nuevo artículo al final de la lista.
    AgregarFinalInventario(Lista, Nuevo);
}

PtrTArticulo Primero(PtrTArticulo &Lista){
    // Esta función devuelve el primer artículo en la lista (la cabeza).
    // No modifica la lista, solo retorna el puntero al primer nodo.
    return Lista;
}

PtrTArticulo Descolar(PtrTArticulo &Lista){
    // Esta función elimina el primer artículo de la lista, similar a 'Pop'.
    // Guarda la cabeza de la lista en 'Aux', luego actualiza la cabeza de la lista al siguiente artículo.
    // Establece el puntero 'Siguiente' de 'Aux' como NULL y devuelve el artículo eliminado.
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
	int ContadorDePush = 0;
	int ContadorDeEncolar = 0;
	while (menu) {
		system("CLS");
		cout << " ********* Menu de pila *********" << endl << endl;
		cout << "  1. Usar Pila" << endl;
		cout << "  2. Usar Cola" << endl;
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
				cout << "  1. Push" << endl; //
				cout << "  2. Top" << endl;
				cout << "  3. Pop" << endl;
				cout << "  4. Salir" << endl;
				cout << endl << "	Digite la opcion: ";
				cin >> opc;
				switch (opc) {
				case 1: {// INSERTANDO CON PUSH
					system("CLS");
					ContadorDePush = ContadorDePush + 1;
					Nuevo = CrearArticulo(ContadorDePush, ContadorDePush, ContadorDePush);
					Push(Pila_Llantas, Nuevo);
					cout << "Se acaba de hacer PUSH, el Top de la Pila ahora es: " << endl << Top(Pila_Llantas)->Codigo << endl;
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

					if (Top(Pila_Llantas) != NULL && Top(Pila_Llantas)->Siguiente != NULL) {
						Pop(Pila_Llantas);
						cout << "Se acaba de hacer POP, el Top de la Pila ahora es: " << endl << Top(Pila_Llantas)->Codigo << endl;
					}
					else if (Top(Pila_Llantas) != NULL && Top(Pila_Llantas)->Siguiente == NULL) {
						Pop(Pila_Llantas);
						cout << "Se acaba de hacer POP, solo habia un elemento en la Pila por lo cual ahora Top es: NULO" << endl;
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
					ContadorDePush = 0;
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
					ContadorDeEncolar = ContadorDeEncolar + 1;
					Nuevo = CrearArticulo(ContadorDeEncolar, ContadorDeEncolar, ContadorDeEncolar);
					Encolar(Cola_Pasajeros, Nuevo);
					cout << "Se acaba de hacer ENCOLAR al final de la Cola de : " << endl << Nuevo->Codigo << endl;
					system("pause");
					break;
				}
				case 2: {// PRIMERO
					system("CLS");
					if (Primero(Cola_Pasajeros) != NULL){
						cout << "El primero que va a ser atendido de la cola es : " << endl << Primero(Cola_Pasajeros)->Codigo << endl;
					}
					else{
						cout << "No hay gente en la cola" << endl;
					}
					system("pause");
					break;
				}
				case 3: {// DESCOLAR
					system("CLS");

					if (Primero(Cola_Pasajeros) != NULL && Primero(Cola_Pasajeros)->Siguiente != NULL) {
						Descolar(Cola_Pasajeros);
						cout << "Se acaba de hacer DESCOLAR, el nuevo primero de la Cola ahora es: " << endl << Primero(Cola_Pasajeros)->Codigo << endl;
					}
					else if (Primero(Cola_Pasajeros) != NULL && Primero(Cola_Pasajeros)->Siguiente == NULL) {
						Descolar(Cola_Pasajeros);
						cout << "Se acaba de hacer DESCOLAR, solo habia un elemento en la lista por lo cual ahora el primero es: NULO" << endl;
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
					ContadorDeEncolar = 0;
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
/*
	CONSIDERACION PARA EL PROFESOR:
		-Se acomodo algunas partes del codigo para poder ser mas facilmente legible

		-Se cambiaron las funciones POP y DESCOLAR, debido a que estas daban error al intentar usarlas cuando no habia ningun elemento, o solo un elemento
		 en la pila o cola respectiva

		-Se arreglo la funcion PRIMERO debido a que esta daba error cuando no habia elementos en la cola, esto debido a que no hacia la comprobaciona antes de mostrar
		 el elemento en pantalla
*/

// Pruebas del funcionamiento de PILA

/*
Consola:
	FUNCION PUSH:

	Se acaba de hacer PUSH, el Top de la Pila ahora es:
	1
	Presione una tecla para continuar . . .

	FUNCION TOP:

	El Top de la Pila es:
	10
	Presione una tecla para continuar . . .

	FUNCION POP:

	Se acaba de hacer POP, el Top de la Pila ahora es:
	9
	Presione una tecla para continuar . . .
*/

// Pruebas del funcionamiento de COLA

/*
Consola:
	FUNCION ENCOLAR:

	Se acaba de hacer ENCOLAR al final de la Cola de :
	1
	Presione una tecla para continuar . . .

	FUNCION PRIMERO

	El primero que va a ser atendido de la cola es :
	1
	Presione una tecla para continuar . . .

	FUNCION DESCOLAR

	Se acaba de hacer DESCOLAR, el nuevo primero de la Cola ahora es:
	2
	Presione una tecla para continuar . . .
*/
