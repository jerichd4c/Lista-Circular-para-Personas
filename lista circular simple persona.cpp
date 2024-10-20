#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;
//estructura de persona
struct Persona {
    //atributos
    string NombreCompleto;
    int edad;
    char genero;
    float altura;  
    //constructor vacio
    Persona (string n="", int e= 0, char g=' ', float a=0.0) :NombreCompleto(n), edad(e), genero(g), altura(a) {}
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
    public:
    //constructor 
    ListaCircularSimple() : head(NULL), tail(NULL) {}
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
        
    }
    //funcion para mostrar la lista
    void mostrar () const {
        if (head==NULL) {
            cout<<"la lista esta vacia"<<std::endl;
            return;
    }
    Nodo <T> *actual=head;
    do {
        cout<<"Nombre: "<<actual->data.NombreCompleto
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
            if (actual->data.nombreCompleto==NombreCompleto) {
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
        getline(archivo, linea);
        while(getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, apellido, NombreCompleto;
        int edad;
        char genero;
        float altura;
        char delimitador; //para leer los datos
        //recorre la lista
        getline(ss, nombre, ';');
        getline(ss, apellido, ';');
        ss >> edad >> delimitador >> genero >> delimitador >> altura; 
        NombreCompleto=nombre+" "+apellido; //concatenar nombre y apellido
        Persona p(NombreCompleto, edad, genero, altura);
        insertar(p);
        }
        archivo.close();
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
};

//implementacion
int main(){
    ListaCircularSimple<Persona> listaPersonas;
    //leer el archivo
    listaPersonas.leerArchivo("archivo.txt");
    listaPersonas.mostrar();
}
