#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<set>

using namespace std;
//estructura de persona
struct Persona {
    //atributos
    int ID;
    string NombreCompleto;
    int edad;
    char genero;
    float altura;  
    //constructor vacio
    Persona (int id=0, string n="", int e= 0, char g=' ', float a=0.0) :ID (id), NombreCompleto(n), edad(e), genero(g), altura(a) {}
};
//estructura de nodos
template <typename T>
struct Nodo {
    //atributos
    T data;
    Nodo<T>* next;
    //constructor 
    Nodo(T data): data(data), next(NULL) {}
};
//clase de lista circular simple
template<typename T>
class ListaCircularSimple {
    private:
    Nodo<T>* head;
    Nodo<T>* tail;
    int contadorID;
    public:
    //funcion para actualizar el archivo
    void actualizarArchivo (const string& nombreArchivo) {  
        ofstream archivo (nombreArchivo);
            if(!archivo) {
                cout<<"No se pudo abrir el archivo"<<endl;
                return;
            }
        Nodo<T> *actual=head;
        archivo << "ID;nombre;apellido;edad;genero;altura\n"; //encabezado
        if (head!=NULL) {
        do {
            stringstream NombreCompleto(actual->data.NombreCompleto);
            string nombre, apellido;
            getline(NombreCompleto, nombre, ' ');
            getline(NombreCompleto, apellido, ' ');
            //se scriben los datos de la persona
            archivo <<actual->data.ID<<';'
                    <<nombre<<';'
                    <<apellido<<';'
                    <<actual->data.edad<<';'
                    <<actual->data.genero<<';'
                    <<actual->data.altura<<'\n';
            actual=actual->next;
        } while (actual != head);
        }
        archivo.close();
        cout<<"Archivo actualizado"<<endl;
    }
    //constructor 
    ListaCircularSimple() : head(NULL), tail(NULL), contadorID(0){}
    //funcion para insertar al final
    void insertar (T value) {
        Nodo<T>* newNode= new Nodo<T> (value);
        if (head==NULL) { //CASO LISTA VACIA
            head=tail=newNode;
            tail->next=head; //tail y head son iguales pq es el unico elemento
        } else { //CASO LISTA NO VACIA
            tail->next=newNode;
            tail=newNode;
            tail->next=head;
        }
         if (newNode->data.ID == 0) {
        newNode->data.ID = ++contadorID;
        }
    }
    //funcion para mostrar la lista
    void mostrar () const {
        if (head==NULL) {
            cout<<"la lista esta vacia"<<std::endl;
            return;
    }
    Nodo <T> *actual=head;
    do {
        cout<<"ID: "<<actual->data.ID
        <<" Nombre: "<<actual->data.NombreCompleto
        <<" Edad: "<<actual->data.edad
        <<" Genero: "<<actual->data.genero
        <<" Altura: "<<actual->data.altura<<endl;
        actual=actual->next;
    } while (actual != head);
    }
    //funcion para borrar un elemento por nombre nt: se tiene que borrar desde cualquier elemento
    void borrar (string NombreCompleto) {
        if (head==NULL) return;

        Nodo <T> *actual=head;
        Nodo <T> *prev=NULL;
        do {
            if (actual->data.NombreCompleto==NombreCompleto) {
                if (actual==head) { //si es el primer elemento
                    if (head==tail) { // si es el unico elemento
                        delete head;
                        head=tail=NULL; //lista queda vacia
                    } else {
                        head=head->next;
                        tail->next=head;
                        delete actual;
                    }
                } else if (actual==tail) { //si es el ultimo elemento
                    prev->next=head;
                    tail=prev;
                    delete actual;
                } else { //si es un elemento entre head y tail
                    prev->next=actual->next;
                    delete actual;
               }
               return;
            }
            prev=actual;
            actual=actual->next;
        } while (actual != head);
    }
    //funcion para leer el archivo 
    void leerArchivo (const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo) {
            cout<<"No se pudo abrir el archivo"<<endl;
            return;
        }
        cout<<"Se abrio el archivo"<<endl;
        string linea;
        //logica para leer un archivo con ID's mezclados 
        set<int> idsUnicos;
        int maxID=0;
        getline(archivo, linea);
        while(getline(archivo, linea)) {
        stringstream ss(linea);
        int id;
        string nombre, apellido, NombreCompleto;
        int edad;
        char genero;
        float altura;
        char delimitador; //para leer los datos
        ss>>id>>delimitador;
        //recorre la lista
        getline(ss, nombre, ';');
        getline(ss, apellido, ';');
        ss >> edad >> delimitador;
        ss >> genero >> delimitador;
        ss >> altura; 
        NombreCompleto=nombre+" "+apellido; //concatenar nombre y apellido
        //verificacion
        if (idsUnicos.find(id) != idsUnicos.end()) {
            cout<<"ID repetido: "<<id<<endl;
            continue;
        }

        idsUnicos.insert(id);
        if (id>maxID) {
            maxID=id;
        }
        Persona p(id, NombreCompleto, edad, genero, altura);
        p.ID=id;
        insertar(p);
        contadorID = max(contadorID, maxID);
    }
    //asegurarse de que el contadorID es al menos el máximo ID encontrado en el archivo
    contadorID = max(contadorID, maxID);
    archivo.close();
    cout<<"Archivo leido"<<endl;
    }
    //destructor de lista circular simple
    ~ListaCircularSimple(){
        if (head==NULL) return;
        Nodo <T> *actual=head;
        do {
            Nodo<T> *next=actual->next;
            delete actual;
            actual=next;
        } while (actual!=head);
    }
    //funcion para insertar entre dos nodos
    void insertarEntreDosNodos (T value, int idDespuesDe) {
       if (head==NULL) {
        insertar(value);
        return;
       }
        Nodo <T> *actual=head;
        Nodo <T> *prev=NULL;
            //buscar el nodo al que se quiere insertar despues
            do {
            if (actual->data.ID==idDespuesDe) {   
            Nodo<T>* newNode = new Nodo<T>(value);
            newNode->next = actual->next;
            actual->next = newNode;
            if (actual == tail) {
                tail = newNode;
            } if (newNode->data.ID == 0) {
                newNode->data.ID = ++contadorID;
            }
            return;
            }
            actual = actual->next;
        //se crea nuevo nodo
        } while (actual != head);
    }
    //funcion para buscar un ID especifico
    void buscarID (int idABuscar) const {
        if (head==NULL) {
            cout<<"la lista esta vacia"<<endl;
            return;
        }
        Nodo<T> *actual=head;  
        do {
            if (actual->data.ID==idABuscar) {
                cout << "ID: " << actual->data.ID
                     << " Nombre: " << actual->data.NombreCompleto
                     << " Edad: " << actual->data.edad
                     << " Genero: " << actual->data.genero
                     << " Altura: " << actual->data.altura << endl;
                return; //Se acaba la busqueda al encontrar el ID
            }
            actual=actual->next; 
        } while (actual != head);
        cout<<"ID:  "<<idABuscar<<" no encontrado"<<endl;
    }
    //funcion para insertar al inicio
        void insertarAlInicio (T value) {
        Nodo<T> *newNode= new Nodo<T> (value);
        newNode->data.ID=1;
        if (head==NULL) {
        head=tail=newNode;
        tail->next=head;
        } else { //caso si la lista no esta vacia
            Nodo<T> *actual=head;
            //incrementar todos los nodos existentes
            do{
                actual->data.ID++;
                actual=actual->next;
            } while (actual != head);
            newNode->next=head;
            head=newNode;
            tail->next=head;
        }
        contadorID++;
    }
    //funcion para insertar un nodo en un lugar aleatorio de la lista
    void insertarEnLugarAleatorio (T value) {
        if (head==NULL) {
            insertarAlInicio(value);
            return;
        }
        //se calcula el tamaño de la lista
        Nodo<T> *actual=head;
        int nodosTotales=0;
        do {
            nodosTotales++;
            actual=actual->next;
        } while (actual != head);
        //index random
        srand(time(0)); //random seed
        int indiceAleatorio = rand () % nodosTotales;
        //se recorre la lista hasta la posicion aleatoria
        actual=head;
        Nodo<T> *prev=NULL;
        for (int i=0; i<indiceAleatorio; i++) {
            prev=actual;
            actual=actual->next;
        }
        //se inserta
        Nodo<T> *newNode= new Nodo<T> (value);
        newNode->data.ID=actual->data.ID;
        if (prev==NULL) { //si es el inicio
            newNode->next=head;
            head=newNode;
            tail->next=head;
        } else {
            newNode->next=actual;
            prev->next=newNode;
            if (actual==head) { // si se inserta antes
                tail->next=head;
            }
        }
        Nodo<T>* temp = newNode->next;
        while (temp != head) {
        temp->data.ID++;
        temp = temp->next;
    }
    contadorID++;
    }
}; 

    //funcion para mostrar el menu
    void mostrarMenu() {
    cout << "1. Mostrar lista de personas" << endl;
    cout << "2. Insertar nueva persona (Final)" << endl;
    cout << "3. Insertar nueva persona (Inicio)" << endl;
    cout << "4. Borrar persona" << endl;
    cout << "5. Buscar persona por ID" << endl;
    cout << "6. Insertar persona en posición aleatoria" << endl;
    cout << "7. Insertar persona entre dos nodos" << endl;
    cout << "8. Salir" << endl;
    cout << "Seleccione una opción: ";
    }

//implementacion
int main(){
    ListaCircularSimple<Persona> listaPersonas;
    //leer el archivo
    string ArchivoPersonas="archivoListaSimple.txt";
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
            case 2: //insertar una nueva persona (Al final)
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
            case 3: //insertar una nueva persona (Al inicio)
                {
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
            case 4: { //borrar persona
                string nombre;
                cout << "Ingrese el nombre completo de la persona a borrar: ";
                cin.ignore();
                getline(cin, nombre);
                listaPersonas.borrar(nombre);
                listaPersonas.actualizarArchivo(ArchivoPersonas);
                break;
            }
            case 5: { //buscar persona por ID
                int idABuscar;
                cout << "Ingrese el ID a buscar: ";
                cin >> idABuscar;
                listaPersonas.buscarID(idABuscar);
                break;
            }
            case 6: { //insertar persona aleatoria
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
            case 7: { //insertar persona entre dos nodos
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
            case 8: //terminar programa
                cout<<"programa terminado"<<endl;
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
        }
    } while (opcion != 8);
    return 0;
}