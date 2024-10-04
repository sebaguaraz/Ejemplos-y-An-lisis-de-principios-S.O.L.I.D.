#include <iostream>
#include <string>
#include <memory>
using namespace std;

//Class Persona responsable de manejar datos del cliente

class Persona
{
private:
    string name, surname;
    int telefono, dni;
public:
    Persona(string name, string surname, int telefono, int dni){
        this->dni=dni;
        this->telefono=telefono;
        this->name=name;
        this->surname=surname;
        
    };
    ~Persona(){};
    string getname(){
        return name;
    }
    string getsurname(){
        return surname;
    }
    int getdni(){
        return dni;
    }
    int gettelefono(){
        return telefono;
    }

    
};

//class Factura responsable de la logica de la factura
class Factura
{
private:
    shared_ptr<Persona> p;
    string namee;
    
public:
    Factura(){};
    ~Factura(){};

    void agregarCliente(std::shared_ptr<Persona> persona, string name){
        p=persona;
        namee = name;
    }
    void MostrarFactura(){
        cout<<"Nombre de Factura: " << namee <<endl;
        cout<<"Cliente nombre: "<< p->getname()  <<endl;
        cout<<"Apellido: " << p->getsurname() <<endl;
        cout<<"Telef: " << p->gettelefono()<<endl;
        cout<<"DNI: " << p->getdni() <<endl;
    }

};

//contrato que define si se guarda en un archivo o base de datos
class IPersistenciaFactura
{
private:
   
public:
    virtual void guardar(shared_ptr<Factura> factura) = 0;
};




//class Manager encargado de gestionar factura
class Manager {
private:
    shared_ptr<Factura> factura;  // puntero factura

    shared_ptr<IPersistenciaFactura> persistir;//si es persistido en una db o archivo


public:
    Manager(){
        factura = make_shared<Factura>();  // apunta al objeto

    };
    ~Manager(){};

    // Método para crear la factura
    shared_ptr<Factura> crearFactura(std::shared_ptr<Persona> persona, std::string name) {

        factura->agregarCliente(persona, name);
        return factura;  // Retornamos la misma factura
    }

    void ImprimirFactura(){
        cout<<"--------Factura--------: " <<endl;
        factura->MostrarFactura();
    }

    void GuardarFactura(shared_ptr<IPersistenciaFactura> persistir){//elige si es en una db o archivo

        this->persistir=persistir;
        persistir->guardar(factura);

    }
};


//extender nueva funcionalidad
class PersistirDataBase : public IPersistenciaFactura
{
private:
    shared_ptr<Factura> factura;
public:
    PersistirDataBase(/* args */){};
    ~PersistirDataBase(){};
    void guardar(shared_ptr<Factura> factura){
        this->factura = factura;
        cout<<"facturaa guardada en la base de datos!" <<endl;

    }


};


//funcionalidad ya hecha
class PersistirArchivo : public IPersistenciaFactura
{
private:
    shared_ptr<Factura> factura;
public:
    PersistirArchivo(/* args */){};
    ~PersistirArchivo(){};
    void guardar(shared_ptr<Factura> factura){
        this->factura = factura;
        cout<<"facturaa guardada como archivo!" <<endl;

    }

};











int main(){

    //creo la persona
    shared_ptr<Persona> persona = make_shared<Persona>("Pedro", "Sanchez", 22355343, 44692604);

    //creo el manager y la factura del cliente
    shared_ptr<Manager> manager = make_shared<Manager>();
    manager->crearFactura(persona,"Pago de gas");
    //muestra
    manager->ImprimirFactura();

    //guarda la factura en un archivo o la base de datos
    
    shared_ptr<IPersistenciaFactura> database = make_shared<PersistirDataBase>();
    manager->GuardarFactura(database);







    return 0;
}