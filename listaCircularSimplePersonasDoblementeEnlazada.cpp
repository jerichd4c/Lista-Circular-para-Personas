#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<set>

using namespace std;

// Estructura de persona
struct Persona {
    int ID;
    string NombreCompleto;
    int edad;
    char genero;
    float altura;
    // Constructor vacío
    Persona(int id = 0, string n = "", int e = 0, char g = ' ', float a = 0.0) : ID(id), NombreCompleto(n), edad(e), genero(g), altura(a) {}
};

// Estructura de nodos para lista doblemente enlazada
template <typename T>
struct Nodo {
    T data;
    Nodo<T>* next;
    Nodo<T>* prev;
    // Constructor
    Nodo(T data) : data(data), next(NULL), prev(NULL) {}
};

// Clase de lista circular doblemente enlazada
template<typename T>
class ListaCircularDoble {
private:
    Nodo<T>* head;
    Nodo<T>* tail;
    int contadorID;

public:
    // Constructor
    ListaCircularDoble() : head(NULL), tail(NULL), contadorID(0) {}

    // Destructor
    ~ListaCircularDoble() {
        if (head == NULL) return;
        Nodo<T>* actual = head;
        do {
            Nodo<T>* next = actual->next;
            delete actual;
            actual = next;
        } while (actual != head);
    }

    // Función para actualizar el archivo
    void actualizarArchivo(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);
        if (!archivo) {
            cout << "No se pudo abrir el archivo" << endl;
            return;
        }
        Nodo<T>* actual = head;
        archivo << "ID;nombre;apellido;edad;genero;altura\n"; // Encabezado
        if (head != NULL) {
            do {
                stringstream NombreCompleto(actual->data.NombreCompleto);
                string nombre, apellido;
                getline(NombreCompleto, nombre, ' ');
                getline(NombreCompleto, apellido, ' ');
                // Se escriben los datos de la persona
                archivo << actual->data.ID << ';'
                        << nombre << ';'
                        << apellido << ';'
                        << actual->data.edad << ';'
                        << actual->data.genero << ';'
                        << actual->data.altura << '\n';
                actual = actual->next;
            } while (actual != head);
        }
        archivo.close();
        cout << "Archivo actualizado" << endl;
    }

    // Función para insertar al final
    void insertar(T value) {
        Nodo<T>* newNode = new Nodo<T>(value);
        if (head == NULL) { // Caso lista vacía
            head = tail = newNode;
            head->next = head->prev = head; // La lista circular
        } else { // Caso lista no vacía
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            tail = newNode;
        }
        if (newNode->data.ID == 0) {
            newNode->data.ID = ++contadorID;
        }
    }

    // Función para mostrar la lista
    void mostrar() const {
        if (head == NULL) {
            cout << "La lista está vacía" << endl;
            return;
        }
        Nodo<T>* actual = head;
        do {
            cout << "ID: " << actual->data.ID
                 << " Nombre: " << actual->data.NombreCompleto
                 << " Edad: " << actual->data.edad
                 << " Género: " << actual->data.genero
                 << " Altura: " << actual->data.altura << endl;
            actual = actual->next;
        } while (actual != head);
    }

    // Función para borrar un elemento por nombre
    void borrar(string NombreCompleto) {
        if (head == NULL) return;

        Nodo<T>* actual = head;
        do {
            if (actual->data.NombreCompleto == NombreCompleto) {
                if (actual == head) { // Si es el primer elemento
                    if (head == tail) { // Si es el único elemento
                        delete head;
                        head = tail = NULL; // Lista queda vacía
                    } else {
                        head = head->next;
                        head->prev = tail;
                        tail->next = head;
                        delete actual;
                    }
                } else if (actual == tail) { // Si es el último elemento
                    tail = tail->prev;
                    tail->next = head;
                    head->prev = tail;
                    delete actual;
                } else { // Si es un elemento entre head y tail
                    actual->prev->next = actual->next;
                    actual->next->prev = actual->prev;
                    delete actual;
                }
                return;
            }
            actual = actual->next;
        } while (actual != head);
    }

    // Función para leer el archivo
    void leerArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo) {
            cout << "No se pudo abrir el archivo" << endl;
            return;
        }
        cout << "Se abrió el archivo" << endl;
        string linea;
        set<int> idsUnicos;
        int maxID = 0;
        getline(archivo, linea); // Leer encabezado
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            int id;
            string nombre, apellido, NombreCompleto;
            int edad;
            char genero;
            float altura;
            char delimitador; // Para leer los datos
            ss >> id >> delimitador;
            getline(ss, nombre, ';');
            getline(ss, apellido, ';');
            ss >> edad >> delimitador;
            ss >> genero >> delimitador;
            ss >> altura;
            NombreCompleto = nombre + " " + apellido;
            if (idsUnicos.find(id) != idsUnicos.end()) {
                cout << "ID repetido: " << id << endl;
                continue;
            }
            idsUnicos.insert(id);
            if (id > maxID) {
                maxID = id;
            }
            Persona p(id, NombreCompleto, edad, genero, altura);
            insertar(p);
        }
        contadorID = max(contadorID, maxID);
        archivo.close();
        cout << "Archivo leído" << endl;
    }

    // Función para buscar por ID
    void buscarID(int idABuscar) const {
        if (head == NULL) {
            cout << "La lista está vacía" << endl;
            return;
        }
        Nodo<T>* actual = head;
        do {
            if (actual->data.ID == idABuscar) {
                cout << "ID: " << actual->data.ID
                     << " Nombre: " << actual->data.NombreCompleto
                     << " Edad: " << actual->data.edad
                     << " Género: " << actual->data.genero
                     << " Altura: " << actual->data.altura << endl;
                return;
            }
            actual = actual->next;
        } while (actual != head);
        cout << "ID: " << idABuscar << " no encontrado" << endl;
    }

    // Función para insertar al inicio
    void insertarAlInicio(T value) {
        insertar(value);
        head = tail->next; // Ajustar la cabeza al nuevo nodo insertado
    }

    // Función para insertar en una posición aleatoria
    void insertarEnLugarAleatorio(T value) {
        if (head == NULL) {
            insertarAlInicio(value);
            return;
        }
        // Calcular el tamaño de la lista
        Nodo<T>* actual = head;
        int nodosTotales = 0;
        do {
            nodosTotales++;
            actual = actual->next;
        } while (actual != head);
        // Índice aleatorio
        srand(time(0));
        int indiceAleatorio = rand() % nodosTotales;
        // Recorrer la lista hasta la posición aleatoria
        actual = head;
        for (int i = 0; i < indiceAleatorio; i++) {
            actual = actual->next;
        }
        insertarEntreDosNodos(value, actual->data.ID);
    }

    // Función para insertar entre dos nodos
    void insertarEntreDosNodos(T value, int idDespuesDe) {
        if (head == NULL) {
            insertar(value);
            return;
        }
        Nodo<T>* actual = head;
        do {
            if (actual->data.ID == idDespuesDe) {
                Nodo<T>* nuevo = new Nodo<T>(value);
                nuevo->next = actual->next;
                nuevo->prev = actual;
                actual->next->prev = nuevo;
                actual->next = nuevo;
                if (nuevo->data.ID == 0) {
                    nuevo->data.ID = ++contadorID;
                }
                return;
            }
            actual = actual->next;
        } while (actual != head);
        cout << "ID no encontrado" << endl;
    }
    //funcion para recorrer la lista al reves
    void recorrerListaAlReves () const {
        if (tail==NULL) {
            cout<<"la lista esta vacia"<<endl;
            return;
        }
        Nodo<T> *actual=tail;
        do {
            cout << "ID: " << actual->data.ID
                 << " Nombre: " << actual->data.NombreCompleto
                 << " Edad: " << actual->data.edad
                 << " Genero: " << actual->data.genero
                 << " Altura: " << actual->data.altura << endl;
            actual=actual->prev;
        } while (actual != tail);
    }
};

    //funcion para mostrar el menu
    void mostrarMenu() {
    cout << "1. Mostrar lista de personas" << endl;
    cout << "2. Mostrar lista al reves" << endl;
    cout << "3. Insertar nueva persona (Final)" << endl;
    cout << "4. Insertar nueva persona (Inicio)" << endl;
    cout << "5. Borrar persona" << endl;
    cout << "6. Buscar persona por ID" << endl;
    cout << "7. Insertar persona en posición aleatoria" << endl;
    cout << "8. Insertar persona entre dos nodos" << endl;
    cout << "9. Salir" << endl;
    cout << "Seleccione una opción: ";
    }

//implementacion
int main(){
    ListaCircularDoble<Persona> listaPersonas;
    //leer el archivo
    string ArchivoPersonas="archivoListaDoble.txt";
    listaPersonas.leerArchivo(ArchivoPersonas);
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        switch (opcion) {
            case 1: //mostrar la lista
                cout<<"la lista de personas es: "<<endl;
                listaPersonas.mostrar();
                break;
            case 2: //mostrar la lista al reves
                cout<<"la lista de personas al reves es: "<<endl;
                listaPersonas.recorrerListaAlReves();
                break;
            case 3: //insertar una nueva persona (Al final)
                {
                string nombre;
                int edad;
                char genero;
                float altura;
                cout << "Ingrese el nombre completo: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la edad: ";
                cin >> edad;
                cout << "Ingrese el género (M/F): ";
                cin >> genero;
                cout << "Ingrese la altura: ";
                cin >> altura;
                Persona nuevaPersona(0, nombre, edad, genero, altura);
                listaPersonas.insertar(nuevaPersona);
                listaPersonas.actualizarArchivo(ArchivoPersonas);
                break;
            }
            case 4: { //insertar una nueva persona (Al inicio)
                string nombreInicio;
                int edadInicio;
                char generoInicio;
                float alturaInicio;
                cout << "Ingrese el nombre completo: ";
                cin.ignore();
                getline(cin, nombreInicio);
                cout << "Ingrese la edad: ";
                cin >> edadInicio;
                cout << "Ingrese el tamaño (M/F): ";
                cin >> generoInicio;
                cout << "Ingrese la altura: ";
                cin >> alturaInicio;
                Persona nuevaPersona(0, nombreInicio, edadInicio, generoInicio, alturaInicio);
                listaPersonas.insertarAlInicio(nuevaPersona);
                listaPersonas.actualizarArchivo(ArchivoPersonas);
                break;
            }
            case 5: { //borrar persona
                string nombre;
                cout << "Ingrese el nombre completo de la persona a borrar: ";
                cin.ignore();
                getline(cin, nombre);
                listaPersonas.borrar(nombre);
                listaPersonas.actualizarArchivo(ArchivoPersonas);
                break;
            }
            case 6: { //buscar persona por ID
                int idABuscar;
                cout << "Ingrese el ID a buscar: ";
                cin >> idABuscar;
                listaPersonas.buscarID(idABuscar);
                break;
            }
            case 7: { //insertar persona aleatoria
                string nombre;
                int edad;
                char genero;
                float altura;
                cout << "Ingrese el nombre completo: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la edad: ";
                cin >> edad;
                cout << "Ingrese el género (M/F): ";
                cin >> genero;
                cout << "Ingrese la altura: ";
                cin >> altura;
                Persona personaAleatoria(0, nombre, edad, genero, altura);
                listaPersonas.insertarEnLugarAleatorio(personaAleatoria);
                listaPersonas.actualizarArchivo(ArchivoPersonas);
                break;
            }
            case 8: { //insertar persona entre dos nodos
                string nombre;
                int edad;
                char genero;
                float altura;
                int idDespues;
                cout << "Ingrese el nombre completo: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la edad: ";
                cin >> edad;
                cout << "Ingrese el género (M/F): ";
                cin >> genero;
                cout << "Ingrese la altura: ";
                cin >> altura;
                cout << "Ingrese el ID después del cual insertar: ";
                cin >> idDespues;
                Persona nuevaPersona(0, nombre, edad, genero, altura);
                listaPersonas.insertarEntreDosNodos(nuevaPersona, idDespues);
                listaPersonas.actualizarArchivo(ArchivoPersonas);
                break;
            }
            case 9: //terminar programa
                cout<<"programa terminado"<<endl;
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
        }
    } while (opcion != 9);
    return 0;
}