/*
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

struct producto {
  string nombre;
  string id;
  double precio;
  string categoria;
  vector<string> tags;
  string descripcion;
  bool nombreEncontrado = false;
  bool precioEncontrado = false;
  bool idEncontrado = false;
  bool categoriaEncontrada = false;
  bool tagEncontrado = false;
  // imagen
  void mostrarDescripcion() { cout << descripcion << endl; }

  void mostrarProductoCompleto() {
    cout << id << ", " << nombre << ", " << fixed << setprecision(2) << precio
         << " USD, Category: " << categoria << ", Tags: ";
    for (const string &tagsito : tags) {
      cout << tagsito;
      if(tagsito != tags[tags.size()-1])
        cout<<", ";
      else
        cout<<".";
    }
    cout << endl;
  }

  void mostrarProductoSimple() {
    cout << id << ", " << nombre << ", " << fixed << setprecision(2) << precio
         << " USD" << endl;
  }
};
struct carrito {
  vector<producto> productos;
  int cantidad = 0;
  double total = 0;
  double descuento;

  void mostrarCarrito() {
    for (producto productoDeCarrito : productos) {
      productoDeCarrito.mostrarProductoSimple();
    }
    cout << "Descuento: " << descuento * 100 << "%" << endl;
    cout << "Total sin descuento: " << fixed << setprecision(2) << total
         << endl;
    cout << "Total: " << fixed << setprecision(2) << total - (total * descuento)
         << endl;
  }

  void añadirProducto(producto producto) {
    productos.push_back(producto);
    total += producto.precio;
    cantidad+= 1;
  }

  void quitarProducto(producto producto) {

    total += producto.precio;
    cantidad+= 1;
  }

};
struct usuario{
  string nombre;
  string contrasena;
  carrito carrito;
  string telefono;
  string direccion;
};
void GuardarCarrito(vector <producto> carrito, string arch){
  ofstream archivo(arch, ios::app);
  for(producto p : carrito){
  if(archivo.is_open()){
    archivo << p.id << "," << p.categoria << ",\""<< p.nombre << "\"," << p.precio << ",\""; 
    int i = 0;
    for (string tag : p.tags){
      i++;
      if(p.tags.size()==1) archivo << tag;
      else if(!(p.tags.size()==i))archivo << tag << ",";
      else archivo<<tag;
    }
    archivo << "\",\"" << p.descripcion << "\"" << endl;
  }
}
}
void GuardarUsuario(usuario usuario1){
  string nombrearchivo = usuario1.nombre + ".txt";
      ofstream archivo(nombrearchivo);
      if (archivo.is_open()) {
          archivo << usuario1.nombre << "," << usuario1.contrasena << "," << usuario1.telefono << "," << usuario1.direccion << endl;
        GuardarCarrito(usuario1.carrito.productos, nombrearchivo);
          archivo.close();
          cout << "Usuario guardado correctamente." << endl;
      } else {
          cout << "Error al guardar el usuario." << endl;
      }
}
carrito LeerCarrito(string nombrearchivo){
 carrito carrito1;
  ifstream archivo(nombrearchivo);
  string linea;
  if (archivo.is_open()){
    getline(archivo, linea);
    while (getline(archivo, linea)){
      stringstream ss(linea);
      string id, nombre, categoria, descripcion, tag, precio1;
      double precio;
      vector<string> tags;
      getline(ss, id, ',');
      getline(ss, categoria, ',');
      ss.ignore();
      getline(ss, nombre, '"');
      ss.ignore();
      getline(ss, precio1, ',');
      try {
        precio = stod(precio1);
      } catch (const exception &) {
        cout << "Error: " << nombre << endl;
        continue;
      }
      string tagg;
      ss.ignore();
      getline(ss, tag, '"');
      stringstream ss2(tag);
      while (getline(ss2, tagg, ','))
        tags.push_back(tagg);
      ss.ignore();
      getline(ss, descripcion, '"');
      producto producto1;
      producto1.id = id;
      producto1.nombre = nombre;
      producto1.precio = precio;
      producto1.categoria = categoria;
      producto1.tags = tags;
      producto1.descripcion = descripcion;
      carrito1.añadirProducto(producto1);
    }
  }
  return carrito1;
}
usuario LeerUsuario(string nombrearchivo){
  usuario usuario1;
  ifstream archivo(nombrearchivo);
  string linea;
  if (archivo.is_open()){
    getline(archivo, linea);
      stringstream ss(linea);
      string nombre, telefono, direccion, contraseña;
      getline(ss, nombre, ',');
      getline(ss, contraseña, ',');
      getline(ss, telefono, ',');
      getline(ss, direccion, ',');
      usuario1.carrito = LeerCarrito(nombrearchivo);
      usuario1.nombre = nombre;
      usuario1.contrasena = contraseña;
      usuario1.telefono = telefono;
      usuario1.direccion = direccion;
}
  return usuario1;
}  

int main(){
  usuario usuario1;
  usuario1.nombre = "Juan";
  usuario1.contrasena = "1234";
  usuario1.telefono = "123456789";
  usuario1.direccion = "Calle falsa 123";
  carrito carrito1;
  producto producto1;
  producto1.id = "1";
  producto1.nombre = "Anillo de oro";
  producto1.precio = 1000;
  producto1.categoria = "Anillos";
  producto1.tags = {"oro", "anillo"};
  producto1.descripcion = "Anillo de oro de 18k";
  producto producto2;
  producto2.id = "2";
  producto2.nombre = "Pulsera de plata";
  producto2.precio = 500;
  producto2.categoria = "Pulseras";
  producto2.tags = {"plata", "pulsera"};
  producto2.descripcion = "Pulsera de plata de 925";
  carrito1.añadirProducto(producto2);
  carrito1.añadirProducto(producto1);
  usuario1.carrito = carrito1;
  GuardarUsuario(usuario1);
  usuario usuario2 = LeerUsuario("Juan.txt");
  cout << usuario2.nombre << endl;
  cout << usuario2.contrasena << endl;
  cout << usuario2.telefono << endl;
  cout << usuario2.direccion << endl;
  usuario2.carrito.mostrarCarrito();
  return 0;
}


  */