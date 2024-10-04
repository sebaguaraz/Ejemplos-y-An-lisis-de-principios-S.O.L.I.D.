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
    string name;
    
public:
    Factura(){};
    ~Factura(){};
    void MostrarFactura(){
        cout<<"Nombre de Factura: " << name <<endl;
        cout<<"Cliente nombre: "<< p->getname()  <<endl;
        cout<<"Apellido: " << p->getsurname() <<endl;
        cout<<"Telef: " << p->gettelefono()<<endl;
        cout<<"DNI: " << p->getdni() <<endl;

    }

    void agregarCliente(std::shared_ptr<Persona> persona, string name){
        p=persona;
        this->name = name;
    }

};

//class Manager encargado de gestionar factura
class Manager {
private:
    shared_ptr<Factura> factura;  // Factura como miembro de la clase

public:
    Manager(){};
    ~Manager(){};

    // Método para crear la factura
    shared_ptr<Factura> crearFactura(std::shared_ptr<Persona> persona, std::string name) {
        factura = make_shared<Factura>();  // Asignamos la factura al miembro de la clase
        factura->agregarCliente(persona, name);
        return factura;  // Retornamos la misma factura
    }

    void facturar(){
        cout<<"--------Factura--------: " <<endl;
        factura->MostrarFactura();
    }
};






int main(){

    //cout<<"------------------------Creo factura-------------------" <<endl;
    shared_ptr<Persona> persona = make_shared<Persona>("Pedro", "Sanchez", 22355343, 44692604);
    shared_ptr<Manager> manager = make_shared<Manager>();
    manager->crearFactura(persona,"Pago de gas");
    manager->facturar();
    







    return 0;
}




