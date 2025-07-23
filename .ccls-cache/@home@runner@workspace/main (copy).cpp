#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// int estado = 1; // 0 cerrar la aplicación
//  Estructura para almacenar los datos de un producto
void imprimirSeparador() {
  cout << "-------------------------------------------" << endl;
}
void imprimirSeparador2() {
  for (int i = 0; i < 64; i++) {
    cout << "-";
  }
  cout << endl;
}
void limpiarBuffer() {
  cin.clear();
  string basura;
  getline(cin, basura);
}
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
  int cantidad = 1;
  // imagen
  void mostrarDescripcion() { cout << descripcion << endl; }

  void mostrarProductoCompleto() {
    cout << id << ", " << nombre << ", " << fixed << setprecision(2) << precio
         << " USD, Category: " << categoria << ", Tags: ";
    for (const string &tagsito : tags) {
      cout << tagsito << ", ";
    }
    cout << "Description: " << descripcion;
    cout << endl;
  }

  void mostrarProductoSimple(int siCantidad = 0) {
    cout << id << ", " << nombre << ", " << fixed << setprecision(2) << precio
         << " USD";
    if (siCantidad == 1) {
      cout << ", Cantidad: " << cantidad;
    }
    cout << endl;
  }
};

// Estructura para almacenar los productos del carrito
struct carrito {
  vector<producto> productos;
  int cantidad = 0;
  double total = 0;
  double descuento = 0;
  double iva = 0.19;

  void mostrarCarrito(int forma = 0) { // 1 para preguntar qué hacer
    int posicion = 1;
    if (productos.empty()) {
      cout << "Carrito vacío." << endl;
      imprimirSeparador();
      return;
    }
    actualizarDescuentos();
    cout << "Carrito: " << endl << endl;
    for (producto productoDeCarrito : productos) {
      cout << posicion++ << ". ";
      productoDeCarrito.mostrarProductoSimple(1);
    }
    cout << endl;
    cout << "Descuento: " << descuento * 100 << "%" << endl;
    cout << "Total sin descuento e IVA: " << fixed << setprecision(2) << total
         << endl;
    cout << "Total: " << fixed << setprecision(2)
         << total - (total * descuento) + ((total - (total * descuento)) * iva)
         << endl;
    if (forma == 1) {
      int decision = 1;
      while (decision != 4) {
        cout << endl;
        cout << "¿Qué desea hacer?" << endl;
        cout << "1. Quitar un producto" << endl;
        cout << "2. Vaciar carrito" << endl;
        cout << "3. Mostrar todas las caracteristicas de un producto" << endl;
        cout << "4. Ir atrás" << endl << endl;

        if(!(cin >> decision)){
          imprimirSeparador();
          cout << "Opción inválida" << endl;
          limpiarBuffer();
          imprimirSeparador();
          continue;
        }
        cin.ignore();

        if (decision == 1) {
          cout << "Digite el indice correspondiente al producto a borrar:"
               << endl;
          int elementoBorrar;
          if(!(cin >> elementoBorrar)){
            imprimirSeparador();
            cout << "Opción inválida" << endl;
            limpiarBuffer();
            imprimirSeparador();
            continue;
          }
          cin.ignore();
          if (elementoBorrar >= 1 && elementoBorrar <= productos.size()) {
            total -= productos[elementoBorrar - 1].precio;
            cantidad -= 1;
            productos.erase(productos.begin() + elementoBorrar - 1);
            cout << "Producto #" << elementoBorrar << " borrado." << endl;
            imprimirSeparador();
          } else {
            cout << "Índice no válido" << endl;
            imprimirSeparador();
          }
        } else if (decision == 2) {
          productos.clear();
          total = 0;
          cantidad = 0;
          imprimirSeparador();
          cout << "Carrito eliminado con éxito." << endl;
          imprimirSeparador();
          return;
        } else if (decision == 3) {
          cout << "Digite el indice correspondiente al producto a mostrar "
                  "características:"
               << endl;
          int elementoConocer;
          if(!(cin >> elementoConocer)){
            imprimirSeparador();
            cout << "Opción inválida" << endl;
            limpiarBuffer();
            imprimirSeparador();
            continue;
          }
          cin.ignore();
          if (elementoConocer >= 1 && elementoConocer <= productos.size()) {
            imprimirSeparador();
            cout << elementoConocer << ". ";
            productos[elementoConocer - 1].mostrarProductoCompleto();

          } else {
            cout << "Índice no válido" << endl;
          }
          imprimirSeparador();
        } else if (decision == 4) {
          imprimirSeparador();
          return;
        } else {
          cout << "Opción no válida" << endl;
        }
        mostrarCarrito();
      }
    }
    imprimirSeparador();
  }

  void actualizarDescuentos() {
    // si tienen entre 10 y 15 productos,10%
    // si tienen entre 15 y 20, 15%
    // mas de 20, 20%
    if (cantidad < 10) {
      ;
    } else if (cantidad < 15) {
      descuento = 0.1;
    } else if (cantidad < 20) {
      descuento = 0.15;
    } else {
      descuento = 0.2;
    }
  }

  void añadirProducto(producto producto) {
    total += producto.precio;
    cantidad += 1;
    if (productos.empty()) {
      productos.push_back(producto);
      return;
    } else {
      for (int i = 0; i < productos.size(); i++) {
        if (productos[i].id == producto.id) {
          productos[i].cantidad += 1;
          return;
        } else if (i == productos.size() - 1) {
          // cout<<"."<<productos[i].id<<"."
          productos.push_back(producto);
          return;
        }
      }
    }
  }

  void quitarProducto(producto producto) {

    total -= producto.precio;
    cantidad -= 1;
  }
};



struct usuario {
  string nombre;
  string contrasena;
  carrito carrito;
  string telefono;
  string direccion;
};

string encriptar(const string &pass) {
  string con;
  for (unsigned char c : pass) {
    if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
      c = c + 1;
    else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
      c = c + 3;
    else if (c >= '0' && c <= '8')
      c = c + 1;
    else if (c == 0xD1) // Ñ
      c = '*';
    else if (c == 0xF1) // ñ
      c = '-';
    else if (c == '9')
      c = '+';
    else
      continue;
    con += c;
  }
  return con;
}

string desencriptar(const string &passEnc) {
  string con;
  for (unsigned char c : passEnc) {
    if ((c >= 'b' && c <= 'n') || (c >= 'B' && c <= 'N'))
      c = c - 1;
    else if ((c >= 'o' && c <= 'z') || (c >= 'O' && c <= 'Z'))
      c = c - 3;
    else if (c >= '1' && c <= '9')
      c = c - 1;
    else if (c == '*')
      c = char(0xD1);
    else if (c == '-')
      c = char(0xF1);
    else if (c == '+')
      c = '9';
    else
      continue;
    con += c;
  }
  return con;
}
// Funcion para guardar el carrito IMPLICITA CON EL USUARIO
void GuardarCarrito(vector<producto> carrito, string arch) {
  ofstream archivo(arch, ios::app);
  for (producto p : carrito) {
    if (archivo.is_open()) {
      archivo << p.id << "," << p.categoria << ",\"" << p.nombre << "\","
              << p.precio << ",\"";
      int i = 0;
      for (string tag : p.tags) {
        i++;
        if (p.tags.size() == 1)
          archivo << tag;
        else if (!(p.tags.size() == i))
          archivo << tag << ",";
        else
          archivo << tag;
      }
      archivo << "\",\"" << p.descripcion << "\"," << p.cantidad << "." << endl;
    }
  }
}
// Funcion para guardar el usuario
void GuardarUsuario(usuario usuario1) {
  string nombrearchivo = usuario1.nombre + ".txt";
  ofstream archivo(nombrearchivo);
  if (archivo.is_open()) {
    archivo << encriptar(usuario1.nombre) << ","
            << encriptar(usuario1.contrasena) << ","
            << encriptar(usuario1.telefono) << ","
            << encriptar(usuario1.direccion) << endl;
    GuardarCarrito(usuario1.carrito.productos, nombrearchivo);
    archivo.close();
    // cout << "Usuario guardado correctamente." << endl;
  } else {
    cout << "Error al guardar el usuario." << endl;
  }
}
// Funcion para leer el carrito IMPLICITA CON EL USUARIO
carrito LeerCarrito(string nombrearchivo) {
  carrito carrito1;
  ifstream archivo(nombrearchivo);
  string linea;
  if (archivo.is_open()) {
    getline(archivo, linea);
    while (getline(archivo, linea)) {
      stringstream ss(linea);
      string id, nombre, categoria, descripcion, tag, precio1, cantidad1;
      int cantidad;
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
      ss.ignore();
      getline(ss, descripcion, '"');
      ss.ignore();
      getline(ss, cantidad1, '.');
      try {
        cantidad = stoi(cantidad1);
      } catch (const exception &) {
        cout << "Error: " << nombre << endl;
        continue;
      }
      producto producto1;
      producto1.id = id;
      producto1.nombre = nombre;
      producto1.precio = precio;
      producto1.categoria = categoria;
      producto1.tags = tags;
      producto1.descripcion = descripcion;
      producto1.cantidad = cantidad;
      carrito1.añadirProducto(producto1);
    }
  }
  return carrito1;
  //  Funcion para leer el usuario
}
usuario LeerUsuario(string nombrearchivo) {
  usuario usuario1;
  ifstream archivo(nombrearchivo);
  string linea;
  if (archivo.is_open()) {
    getline(archivo, linea);
    stringstream ss(linea);
    string nombre, telefono, direccion, contraseña;
    getline(ss, nombre, ',');
    getline(ss, contraseña, ',');
    getline(ss, telefono, ',');
    getline(ss, direccion, ',');
    usuario1.carrito = LeerCarrito(nombrearchivo);
    usuario1.nombre = desencriptar(nombre);
    usuario1.contrasena = desencriptar(contraseña);
    usuario1.telefono = desencriptar(telefono);
    usuario1.direccion = desencriptar(direccion);
  }
  return usuario1;
}
void imprimirFactura(usuario usuario);

//  Funcion para filtrar los productos
vector<producto> FiltrarProductos(
    int x) { // 1 es precio, 2 es categoria, 3 es tag, 4 es nombre y 5 es un id
  double min = 0, max = 0;
  string categorian, tagar, nombreBuscado, idBuscado;
  switch (x) {
  case 1:
    cout << "Ingrese un precio minimo:" << endl;
    while(!(cin >> min)||min<0){
      imprimirSeparador();
      cout << "Opción inválida" << endl
        <<"Ingrese un precio minimo:"<<endl;
      limpiarBuffer();
    }
    cout << "Ingrese un precio maximo:" << endl;
    while(!(cin >> max)||max<min){
      imprimirSeparador();
      cout << "Opción inválida" << endl
        <<"Ingrese un precio maximo:"<<endl;
      limpiarBuffer();
    }
    break;
  case 2:
    cout << "Ingrese una categoria" << endl;
    getline(cin, categorian);
    while (categorian.empty()) {
      cout << "Ingrese una categoria valida" << endl;
      getline(cin, categorian);
    }
    break;
  case 3:
    cout << "Ingrese un tag" << endl;
    getline(cin, tagar);
    while (tagar.empty()) {
      cout << "Ingrese un tag valido" << endl;
      getline(cin, tagar);
    }
    break;
  case 4:
    cout << "Ingrese un nombre" << endl;
    getline(cin, nombreBuscado);
    while (nombreBuscado.empty()) {
      cout << "Ingrese un nombre valido" << endl;
      getline(cin, nombreBuscado);
    }
    break;
  case 5:
    cout << "Ingrese un id" << endl;
    getline(cin, idBuscado);
    while (idBuscado.empty()) {
      cout << "Ingrese un id valido" << endl;
      getline(cin, idBuscado);
    }
    // cout << idBuscado << endl;
    break;
  default:
    cout << "No se pudo abrir el archivo." << endl;
    producto productoEncontrado;
    vector<producto> productosEncontrados;
    productoEncontrado.nombreEncontrado = false;
    productosEncontrados.push_back(productoEncontrado);
    return productosEncontrados;
  }

  producto productoEncontrado;
  vector<producto> productosEncontrados;
  ifstream archivo("Supet.csv");
  if (!archivo.is_open()) {
    cout << "No se pudo abrir el archivo." << endl;
    productoEncontrado.nombreEncontrado = false;
    productosEncontrados.push_back(productoEncontrado);
    return productosEncontrados;
  }

  string linea;
  bool encontrado = false;

  producto productoActual;
  getline(archivo, linea);
  int i = 0, j = 0;
  while (getline(archivo, linea)) {
    i++;
    stringstream ss(linea);
    string id, nombre, categoria, descripcion, tag, basura, precio1;
    double precio;
    vector<string> tags;
    // Separar por comas
    ss.ignore();
    getline(ss, id, ',');
    id.erase(remove_if(id.begin(), id.end(),
                       [](unsigned char c) {
                         return isspace(c) ||
                                c == static_cast<unsigned char>(0xA0);
                       }),
             id.end());
    getline(ss, categoria, ',');
    if (ss.peek() == '"') {
      ss.ignore();
      getline(ss, nombre, '"');
      ss.ignore();
    } else {
      getline(ss, nombre, ',');
    }
    getline(ss, precio1, ',');
    try {
      precio = stod(precio1);
    } catch (const exception &) {
      cout << "Error: " << i << " " << nombre << endl;
      continue;
    }
    string tagg;
    if (ss.peek() == '"') {
      ss.ignore();
      getline(ss, tag, '"');
      stringstream ss2(tag);
      while (getline(ss2, tagg, ','))
        tags.push_back(tagg);
      ss.ignore();
    } else {
      getline(ss, tagg, ',');
      tags.push_back(tagg);
    }
    ss.ignore();
    getline(ss, descripcion, '"');
    ss.ignore();
    getline(ss, basura, ',');
    ss.ignore();
    bool cumple = false;
    switch (x) {
    case 1:
      if (precio >= min && precio <= max)
        cumple = true;

      break;
    case 2:
      if (categoria == categorian)
        cumple = true;
      break;
    case 3:
      for (string taga : tags) {
        if (taga == tagar)
          cumple = true;
      }
      break;
    case 4:
      if (nombre == nombreBuscado)
        cumple = true;
      break;
    case 5:
      if (id == idBuscado)
        cumple = true;
      break;
    default:
      continue;
    }
    if (cumple == true) {
      encontrado = true;
      productoEncontrado.id = id;
      productoEncontrado.nombre = nombre;
      productoEncontrado.precio = precio;
      productoEncontrado.categoria = categoria;
      productoEncontrado.tags = tags;
      productoEncontrado.descripcion = descripcion;
      productoEncontrado.nombreEncontrado = true;
      j++;
      productosEncontrados.push_back(productoEncontrado);
    }
  }

  switch (x) {
  case 1:
  case 2:
  case 3:
    if (encontrado == false) {
      cout << "No hay ningun producto que cumpla con esas caracteristicas."
           << endl;
      productoEncontrado.id = "N/A";
      productoEncontrado.nombre = "N/A";
      productoEncontrado.precio = 0.0;
      productoEncontrado.categoria = "N/A";
      productoEncontrado.tags = {"N/A"};
      productoEncontrado.descripcion = "N/A";
      productoEncontrado.nombreEncontrado = false;
      // productosEncontrados.push_back(productoEncontrado);
      return productosEncontrados;
    }
    if (productosEncontrados.size() == 1) {
      cout << "Solo se encontro 1 producto que cumpla con esas "
              "caracteristicas."
           << endl
           << "Producto encontrado:" << endl;
      productoEncontrado.mostrarProductoSimple();
      return productosEncontrados;
    } else {
      cout << "Se ha encontrado un total de " << j
           << " que cumplen esas caracteristicas." << endl
           << "Productos encontrados:" << endl;
      int m = 1;
      for (producto productoEncontrado : productosEncontrados) {
        cout << m;
        if (m < 10)
          cout << ".  ";
        else
          cout << ". ";
        m++;
        productoEncontrado.mostrarProductoSimple();
      }
      return productosEncontrados;
    }
    archivo.close();
    break;
  case 4:
    if (!encontrado) {
      cout << "Producto no encontrado." << endl;
      productoEncontrado.id = "N/A";
      productoEncontrado.nombre = "N/A";
      productoEncontrado.precio = 0.0;
      productoEncontrado.categoria = "N/A";
      productoEncontrado.tags = {"N/A"};
      productoEncontrado.descripcion = "N/A";
      productoEncontrado.nombreEncontrado = false;
      // productosEncontrados.push_back(productoEncontrado);
      return productosEncontrados;
    }
    if (productosEncontrados.size() == 1) {
      cout << "Producto encontrado:" << endl;
      productoEncontrado.mostrarProductoSimple();
      return productosEncontrados;
    } else {
      cout << "Se ha encontrado un total de " << j
           << " productos con el mismo nombre" << endl
           << "Productos encontrados:" << endl;
      int m = 1;
      for (producto productoEncontrado : productosEncontrados) {
        cout << m;
        if (m < 10)
          cout << ".  ";
        else
          cout << ". ";
        m++;
        productoEncontrado.mostrarProductoSimple();
      }
      return productosEncontrados;
    }
    break;
  case 5:
    if (encontrado == false) {
      cout << "Producto no encontrado." << endl;
      productoEncontrado.id = "N/A";
      productoEncontrado.nombre = "N/A";
      productoEncontrado.precio = 0.0;
      productoEncontrado.categoria = "N/A";
      productoEncontrado.tags = {"N/A"};
      productoEncontrado.descripcion = "N/A";
      productoEncontrado.nombreEncontrado = false;
      // productosEncontrados.push_back(productoEncontrado);
      return productosEncontrados;
    }
    cout << "Producto con la id " << idBuscado << ":" << endl;
    productoEncontrado.mostrarProductoCompleto();
    productosEncontrados.push_back(productoEncontrado);
    return productosEncontrados;
    break;
  default:
    cout << "No se pudo abrir el archivo." << endl;
    producto productoEncontrado;
    vector<producto> productosEncontrados;
    productoEncontrado.nombreEncontrado = false;
    // productosEncontrados.push_back(productoEncontrado);
    return productosEncontrados;
  }
  archivo.close();
}
// Funcion para filtrar por mas de una categoria
vector<producto>
ReFiltrarProductos(vector<producto> joyas,
                   int x) { // 1 precio, 2 categoria, 3 tag, 4 nombre, 5 id
  double min = 0, max = 0;
  string categorian, tagar, nombreBuscado, idBuscado;
  switch (x) {
  case 1:
    cout << "Ingrese un precio minimo" << endl;
    cin >> min;
    while (min < 0) {
      cout << "El precio minimo debe ser mayor a 0." << endl
           << "Ingrese un precio minimo:" << endl;
      cin >> min;
    }
    cout << "Ingrese un precio maximo" << endl;
    cin >> max;
    while (min > max) {
      cout << "El precio maximo debe ser mayor al precio minimo." << endl
           << "Ingrese un precio maximo:" << endl;
      cin >> max;
    }
    break;
  case 2:
    cout << "Ingrese una categoria" << endl;
    getline(cin, categorian);
    while (categorian.empty()) {
      cout << "Ingrese una categoria valida" << endl;
      getline(cin, categorian);
    }
    break;
  case 3:
    cout << "Ingrese un tag" << endl;
    getline(cin, tagar);
    while (tagar.empty()) {
      cout << "Ingrese un tag valido" << endl;
      getline(cin, tagar);
    }
    break;
  case 4:
    cout << "Ingrese un nombre" << endl;
    getline(cin, nombreBuscado);
    while (nombreBuscado.empty()) {
      cout << "Ingrese un nombre valido" << endl;
      getline(cin, nombreBuscado);
    }
    break;
  case 5:
    cout << "Ingrese un id" << endl;
    getline(cin, idBuscado);
    while (idBuscado.empty()) {
      cout << "Ingrese un id valido" << endl;
    }
    break;
  default:
    cout << "No se pudo abrir el archivo." << endl;
    producto productoEncontrado;
    vector<producto> productosEncontrados;
    productoEncontrado.nombreEncontrado = false;
    productosEncontrados.push_back(productoEncontrado);
    return productosEncontrados;
  }
  int j = 0;
  producto productoEncontrado;
  vector<producto> productosEncontrados;
  string id, nombre, categoria, descripcion, tag;
  double precio = 0.0;
  bool encontrado = false;
  vector<string> tags;
  for (producto joya : joyas) {
    id = joya.id;
    nombre = joya.nombre;
    precio = joya.precio;
    categoria = joya.categoria;
    tags = joya.tags;
    descripcion = joya.descripcion;
    bool cumple = false;
    switch (x) {
    case 1:
      if (precio >= min && precio <= max)
        cumple = true;
      break;
    case 2:
      if (categoria == categorian)
        cumple = true;
      break;
    case 3:
      for (string taga : tags) {
        if (taga == tagar)
          cumple = true;
      }
      break;
    case 4:
      if (nombre == nombreBuscado)
        cumple = true;
      break;
    case 5:
      if (id == idBuscado)
        cumple = true;
      break;
    default:
      continue;
    }
    if (cumple == true) {
      encontrado = true;
      productoEncontrado.id = id;
      productoEncontrado.nombre = nombre;
      productoEncontrado.precio = precio;
      productoEncontrado.categoria = categoria;
      productoEncontrado.tags = tags;
      productoEncontrado.descripcion = descripcion;
      productoEncontrado.nombreEncontrado = true;
      j++;
      productosEncontrados.push_back(productoEncontrado);
    }
  }

  switch (x) {
  case 1:
  case 2:
  case 3:
    if (encontrado == false) {
      cout << "No hay ningun producto que cumpla con esas "
              "caracteristicas."
           << endl;
      productoEncontrado.id = "N/A";
      productoEncontrado.nombre = "N/A";
      productoEncontrado.precio = 0.0;
      productoEncontrado.categoria = "N/A";
      productoEncontrado.tags = {"N/A"};
      productoEncontrado.descripcion = "N/A";
      productoEncontrado.nombreEncontrado = false;
      // productosEncontrados.push_back(productoEncontrado);
      return productosEncontrados;
    }
    if (productosEncontrados.size() == 1) {
      cout << "Solo se encontro 1 producto que cumpla con esas "
              "caracteristicas."
           << endl
           << "Producto encontrado:" << endl;
      productoEncontrado.mostrarProductoSimple();
      return productosEncontrados;
    } else {
      cout << "Se ha encontrado un total de " << j
           << " que cumplen esas caracteristicas." << endl
           << "Productos encontrados:" << endl;
      int m = 1;
      for (producto productoEncontrado : productosEncontrados) {
        cout << m;
        if (m < 10)
          cout << ".  ";
        else
          cout << ". ";
        m++;
        productoEncontrado.mostrarProductoSimple();
      }
      return productosEncontrados;
    }
    break;
  case 4:
    if (!encontrado) {
      cout << "Producto no encontrado." << endl;
      productoEncontrado.id = "N/A";
      productoEncontrado.nombre = "N/A";
      productoEncontrado.precio = 0.0;
      productoEncontrado.categoria = "N/A";
      productoEncontrado.tags = {"N/A"};
      productoEncontrado.descripcion = "N/A";
      productoEncontrado.nombreEncontrado = false;
      productosEncontrados.push_back(productoEncontrado);
      return productosEncontrados;
    }
    if (productosEncontrados.size() == 1) {
      cout << "Producto encontrado:" << endl;
      productoEncontrado.mostrarProductoSimple();
      return productosEncontrados;
    } else {
      cout << "Se ha encontrado un total de " << j
           << " productos con el mismo nombre" << endl
           << "Productos encontrados:" << endl;
      int m = 1;
      for (producto productoEncontrado : productosEncontrados) {
        cout << m;
        if (m < 10)
          cout << ".  ";
        else
          cout << ". ";
        m++;
        productoEncontrado.mostrarProductoSimple();
      }
      return productosEncontrados;
    }
    break;
  case 5:
    if (encontrado == false) {
      cout << "Producto no encontrado." << endl;
      productoEncontrado.id = "N/A";
      productoEncontrado.nombre = "N/A";
      productoEncontrado.precio = 0.0;
      productoEncontrado.categoria = "N/A";
      productoEncontrado.tags = {"N/A"};
      productoEncontrado.descripcion = "N/A";
      productoEncontrado.nombreEncontrado = false;
      productosEncontrados.push_back(productoEncontrado);
      return productosEncontrados;
    }
    cout << "Producto con la id " << idBuscado << ":" << endl;
    productoEncontrado.mostrarProductoSimple();
    productosEncontrados.push_back(productoEncontrado);
    return productosEncontrados;
    break;
  default:
    cout << "No se pudo hacer el filtro." << endl;
    producto productoEncontrado;
    vector<producto> productosEncontrados;
    productoEncontrado.nombreEncontrado = false;
    productosEncontrados.push_back(productoEncontrado);
    return productosEncontrados;
  }
}

// Funcion para añadir producto desde la lista
void añadirProducto(vector<producto> filtrados, carrito *carrito) {
  int conf;
  while (true) {
    int x;
    cout << "Ingrese el número del producto que desea añadir:" << endl;
    cin >> x;
    cin.ignore();

    if (x > 0 && x <= filtrados.size()) {
      cout << "Cuantos productos desea añadir?" << endl;
      int cantidad;
      cin >> cantidad;
      cin.ignore();
      for (int i = 0; i < cantidad; i++) {
        (*carrito).añadirProducto(filtrados[x - 1]);
      }
      if (cantidad == 1) {
        cout << "Producto añadido al carrito." << endl;
      } else
        cout << "Productos añadidos al carrito." << endl;
      imprimirSeparador();
    } else {
      cout << "Índice inválido." << endl;
      continue;
    }

    cout << "¿Desea añadir otro producto?" << endl
         << "1. Sí" << endl
         << "2. No" << endl;
    cin >> conf;
    cin.ignore();

    if (conf == 2) {
      imprimirSeparador();
      return;
    } else if (conf != 1) {
      cout << "Opción inválida." << endl;
      return;
    }
  }
}

vector<producto> MostrarTodosLosProductos() {
  vector<producto> productos;
  string linea;
  ifstream archivo("Supet.csv");
  if (!archivo.is_open()) {
    cout << "No se pudo abrir el archivo." << endl;
    return productos;
    getline(archivo, linea);
    int i = 0;
    while (getline(archivo, linea)) {
      i++;
      stringstream ss(linea);
      string id, nombre, categoria, descripcion, tag, basura, precio1;
      double precio;
      vector<string> tags;
      // Separar por comas
      ss.ignore();
      getline(ss, id, ',');
      id.erase(remove_if(id.begin(), id.end(),
                         [](unsigned char c) {
                           return isspace(c) ||
                                  c == static_cast<unsigned char>(0xA0);
                         }),
               id.end());
      getline(ss, categoria, ',');
      if (ss.peek() == '"') {
        ss.ignore();
        getline(ss, nombre, '"');
        ss.ignore();
      } else {
        getline(ss, nombre, ',');
      }
      getline(ss, precio1, ',');
      try {
        precio = stod(precio1);
      } catch (const exception &) {
        cout << "Error: " << i << " " << nombre << endl;
        continue;
      }
      string tagg;
      if (ss.peek() == '"') {
        ss.ignore();
        getline(ss, tag, '"');
        stringstream ss2(tag);
        while (getline(ss2, tagg, ','))
          tags.push_back(tagg);
        ss.ignore();
      } else {
        getline(ss, tagg, ',');
        tags.push_back(tagg);
      }
      ss.ignore();
      getline(ss, descripcion, '"');
      ss.ignore();
      getline(ss, basura, ',');
      ss.ignore();
      producto producto;
      producto.id = id;
      producto.nombre = nombre;
      producto.precio = precio;
      producto.categoria = categoria;
      producto.tags = tags;
      producto.descripcion = descripcion;
      productos.push_back(producto);
    }
  }
  return productos;
}
void conocerCaracteristicas(vector<producto> filtrados, carrito *carrito) {
  int conf = 1;
  while (true) {
    int x;
    cout << "Ingrese el numero del producto del cual desee ver las "
            "caracteristicas:"
         << endl;
    if(!(cin >> x)){
      imprimirSeparador();
      cout << "Opción inválida" << endl;
      limpiarBuffer();
      imprimirSeparador();
      continue;
    }
    cin.ignore();
    if (x > 0 && x <= filtrados.size()) {
      cout << x << ". ";
      filtrados[x - 1].mostrarProductoCompleto();
      cout << endl;
    } else {
      imprimirSeparador();
      cout << "Índice inválido" << endl;
      imprimirSeparador();
      continue;
    }
    if (conf == 1) {
      cout << "Desea ver las caracteristicas de otro producto?" << endl
           << "1. Sí" << endl
           << "2. No" << endl
           << endl;
      while(!(cin >> conf)){
        imprimirSeparador();
        cout << "Opción inválida" << endl;
        limpiarBuffer();
        imprimirSeparador();
        
      }
      cin.ignore();
      if (conf == 2) {
        return;
      }
    } else if (!(conf == 1 || conf == 2))
      cout << "Ingrese un caracter valido" << endl;
  }
}

void afterProducto(vector<producto> productosFiltrados, carrito *elCarrito) {
  int decision = 1;
  while (decision != 5) {
    cout << "¿Qué desea hacer?" << endl
         << "1. Agregar un producto al carrito." << endl
         << "2. Agregar todos los productos" << endl
         << "3. Conocer todas las características de un producto." << endl
         << "4. Aplicar otro filtro." << endl
         << "5. Regresar." << endl
         << endl;
    if(!(cin >> decision)){
      imprimirSeparador();
      cout << "Opción inválida" << endl;
      limpiarBuffer();
      imprimirSeparador();
      continue;
    }
    cin.ignore();
    imprimirSeparador();
    switch (decision) {
    case 1:
      añadirProducto(productosFiltrados, elCarrito);
      break;
    case 2:
      for (producto productoActual : productosFiltrados) {
        (*elCarrito).añadirProducto(productoActual);
      }
      cout << "Productos agregados con éxito" << endl;
      imprimirSeparador();
      break;
    case 3:
      conocerCaracteristicas(productosFiltrados, elCarrito);
      break;
    case 4: {
      cout << "¿Qué filtro desea agregar?" << endl
           << "1. Precio" << endl
           << "2. Categoría" << endl
           << "3. Tag" << endl
           << "4. Nombre" << endl
           << "5. ID" << endl
           << endl;
      int decision2;
      if(!(cin >> decision2)){
        imprimirSeparador();
        cout << "Opción inválida" << endl;
        limpiarBuffer();
        imprimirSeparador();
        break;
      }
      cin.ignore();
      if (decision >= 1 && decision <= 5) {
        ReFiltrarProductos(productosFiltrados, decision2);
        // 1 precio, 2 categoria, 3 tag, 4 nombre, 5 id
      } else {
        cout << "Opción inválida." << endl;
        imprimirSeparador();
      }
      break;
    }
    case 5:
      return;
    default:
      cout << "Opción inválida" << endl;
      imprimirSeparador();
    }
  }
}

void busquedaEnTienda(int estado, usuario *elUsuario, carrito *elCarrito) {
  int proximoEstado = 1;
  vector<producto> productosActuales;
  switch (estado) {
  case 1: // Comienzo full de búsqueda
    cout << "Opciones de búsqueda: " << endl;
    cout << "1. Filtrar por precio" << endl;
    cout << "2. Filtrar por categoria" << endl;
    cout << "3. Filtrar por tag" << endl;
    cout << "4. Buscar por nombre" << endl;
    cout << "5. Buscar por id" << endl;
    cout << "6. Mostrar todos los productos" << endl;
    cout << "7. Mostrar carrito" << endl;
    cout << "8. Finalizar compra" << endl;
    cout << "9. Regresar al menú principal" << endl;
    if(!(cin >> proximoEstado)){
      imprimirSeparador();
      cout << "Opción inválida" << endl;
      limpiarBuffer();
      imprimirSeparador();
      proximoEstado=1;
      break;
    }
    cin.ignore();
    if (proximoEstado >= 1 && proximoEstado <= 9) {
      proximoEstado++;
    } else {
      cout << "Opción no válida." << endl;
      imprimirSeparador();
      proximoEstado = 1;
    }
    imprimirSeparador();
    break;
  case 2: // vector<producto> FiltrarProductos(int x) { // 1 es precio, 2 es
          // categoria, 3 es tag, 4 es nombre y 5 es un id
    productosActuales = FiltrarProductos(1); // precio
    cout << endl;
    if (!productosActuales.empty()) { // preguntar si quiere añadir producto,
                                      // ver caracteristica o regresar
      afterProducto(productosActuales, elCarrito);
    }
    break;
  case 3:
    productosActuales = FiltrarProductos(2); // categoria
    cout << endl;
    if (!productosActuales.empty()) {
      afterProducto(productosActuales, elCarrito);
    }
    break;
  case 4:
    productosActuales = FiltrarProductos(3); // tag
    cout << endl;
    if (!productosActuales.empty()) {
      afterProducto(productosActuales, elCarrito);
    }
    break;
  case 5:
    productosActuales = FiltrarProductos(4); // nombre
    cout << endl;
    if (!productosActuales.empty()) {
      afterProducto(productosActuales, elCarrito);
    }
    break;
  case 6:
    productosActuales = FiltrarProductos(5); // id
    cout << endl;
    if (!productosActuales.empty()) {
      afterProducto(productosActuales, elCarrito);
    }
    break;
  case 7: // mostrar todos los productos
    productosActuales = MostrarTodosLosProductos();
    cout << endl;
    if (!productosActuales.empty()) {
      afterProducto(productosActuales, elCarrito);
    }
    break;
  case 8: // Mostrar carrito
    (*elCarrito).mostrarCarrito(1);
    break;
  case 9:
    imprimirFactura(*elUsuario);
    break;
  case 10:
    return;
  }
  GuardarUsuario(*elUsuario);
  return busquedaEnTienda(proximoEstado, elUsuario, elCarrito);
}

void menu(int estado, usuario *elUsuario, carrito *elCarrito) {
  int proximoEstado = 1;
  switch (estado) {
  case 1: // menu principal
    cout << "¡Bienvenido a la tienda Cartier Jewelry!" << endl;
    cout << "Seleccione una opción:" << endl;
    cout << "1. Registro/Inicio de sesión" << endl;
    cout << "2. Entrar a la tienda" << endl;
    cout << "3. Salir de la tienda" << endl << endl;
    if (!(cin >> proximoEstado)) {
      imprimirSeparador();
      cout << "Opción inválida" << endl;
      limpiarBuffer();
      proximoEstado = 1;
      imprimirSeparador();
      break;
    }
    cin.ignore();
    if (proximoEstado == 1 || proximoEstado == 2 || proximoEstado == 3) {
      proximoEstado++;
    } else {
      cout << "Opción inválida" << endl;
      proximoEstado = 1;
    }
    imprimirSeparador();
    break;
  case 2: { // registro
    int opcionRegistro;
    if ((*elUsuario).nombre.empty()) { // El usuario no está cargado o está
                                       // vacío
      cout << "Usuario, ¿ya está registrado?" << endl
           << "1. Sí" << endl
           << "2. No" << endl;
      int registrado;
      if(!(cin >> registrado)){
        imprimirSeparador();
        cout << "Opción inválida" << endl;
        limpiarBuffer();
        imprimirSeparador();
        proximoEstado =2;
        break;
      }
      cin.ignore();
      imprimirSeparador();
      if (registrado == 1) { // El usuario está registrado
        cout << "Por favor digite su nombre:" << endl;
        string nombrePaBuscar;
        getline(cin, nombrePaBuscar);
        ifstream intentoArchivo(nombrePaBuscar + ".txt");
        if (intentoArchivo.is_open()) {
          intentoArchivo.close();
          usuario usuarioTemp = *elUsuario;
          *elUsuario = LeerUsuario(nombrePaBuscar + ".txt");
          cout << "Digite la contraseña: " << endl;
          string contraseñaVerificacion;
          getline(cin, contraseñaVerificacion);
          imprimirSeparador();
          if (contraseñaVerificacion == (*elUsuario).contrasena) {
            /*cout << "Verificación: ." << contraseñaVerificacion << "." <<
            endl; cout << "Guardada: ." << (*elUsuario).contrasena << "." <<
            endl;*/
            cout << "¡Usuario cargado con éxito!" << endl;
          } else {
            /*cout << "Verificación: ." << contraseñaVerificacion << "." <<
            endl; cout << "Guardada: ." << (*elUsuario).contrasena << "." <<
            endl;*/
            cout << "Contraseña incorrecta" << endl;
            *elUsuario = usuarioTemp;
          }
        } else {
          intentoArchivo.close();
          cout << "Usuario no encontrado." << endl;
        }
      } else if (registrado == 2) { // El usuario NO está registrado
        cout << "Nuevo usuario, ingrese su nombre: " << endl;
        getline(cin, (*elUsuario).nombre);
        ifstream archivoPrueba((*elUsuario).nombre + ".txt");
        while (archivoPrueba.is_open()) {
          cout << "El nombre no está disponible, ingrese otro: " << endl;
          getline(cin, (*elUsuario).nombre);
          archivoPrueba.close();
          archivoPrueba.open((*elUsuario).nombre + ".txt");
        }
        archivoPrueba.close();
        cout << "Contraseña: " << endl;
        getline(cin, (*elUsuario).contrasena);
        cout << "Teléfono: " << endl;
        getline(cin, (*elUsuario).telefono);
        cout << "Dirección: " << endl;
        getline(cin, (*elUsuario).direccion);
        GuardarUsuario(*elUsuario);
        imprimirSeparador();
        cout << "¡Usuario registrado con éxito! " << endl;
      } else {
        cout << "Opción de registro inválida" << endl;
      }
    } else { // El usuario ya está cargado
      cout << (*elUsuario).nombre << ", ¿qué desea hacer?" << endl;
      cout << "1. Revisar datos." << endl;
      cout << "2. Actualizar datos existentes." << endl;
      cout << "3. Cerrar sesión." << endl;
      if(!(cin >> opcionRegistro)){
        imprimirSeparador();
        cout << "Opción inválida" << endl;
        limpiarBuffer();
        imprimirSeparador();
        proximoEstado =2;
        break;
      }
      cin.ignore();
      imprimirSeparador();
      switch (opcionRegistro) {
      case 1: // Revisar datos
        cout << "Datos del usuario" << endl << endl;
        cout << "Nombre: " << (*elUsuario).nombre << endl;
        cout << "Telefono: " << (*elUsuario).telefono << endl;
        cout << "Dirección: " << (*elUsuario).direccion << endl;
        break;
      case 2: { // Actualizar datos
        string nombreAnterior = (*elUsuario).nombre;
        cout << "Ingrese su nombre: " << endl;
        getline(cin, (*elUsuario).nombre);
        cout << "Contraseña: " << endl;
        getline(cin, (*elUsuario).contrasena);
        cout << "Teléfono: " << endl;
        getline(cin, (*elUsuario).telefono);
        cout << "Dirección: " << endl;
        getline(cin, (*elUsuario).direccion);
        remove((nombreAnterior + ".txt").c_str());
        GuardarUsuario(*elUsuario);
        imprimirSeparador();
        cout << "Usuario actualizado con éxito" << endl;
        break;
      }
      case 3: {
        GuardarUsuario(*elUsuario);
        usuario nuevoUsuario;
        *elUsuario = nuevoUsuario;
        cout << "Sesión cerrada con éxito." << endl;
        break;
      }
      default:
        cout << "Opción inválida" << endl;
      }
    }

    imprimirSeparador();
    break;
  }
  case 3: // Búsqueda en tienda
    if ((*elUsuario).nombre.empty()) {
      cout << "Por favor regístrese o inicie sesión para poder ingresar a la "
              "tienda."
           << endl;
    } else {
      busquedaEnTienda(1, elUsuario, elCarrito);
    }
    imprimirSeparador();
    break;
  case 4: // Salida de la aplicación
    cout << "Gracias por usar la aplicación. :)" << endl;
    cout << "Hecho por Juan Sebastian Parra y Miguel Rodriguez";
    return;
    break;
  default:
    cout << "No pasó por ningun switch del menú :(" << endl;
    cout << proximoEstado;
    return;
  }

  return menu(proximoEstado, elUsuario, elCarrito);
}
string obtenerFechaActual() {
  time_t ahora = time(0);
  tm *tiempoLocal = localtime(&ahora);

  char buffer[80];
  strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M",
           tiempoLocal); // dd/mm/yyyy hh:mm

  return string(buffer);
}

void imprimirFactura(usuario usuario) {
  imprimirSeparador2(); // Línea superior
  cout << "                    Cartier Jewelry - FACTURA              " << endl;
  imprimirSeparador2();

  cout << "Fecha: " << obtenerFechaActual() << endl;
  cout << "Cliente: " << usuario.nombre << endl;
  cout << "Teléfono: " << usuario.telefono << endl;
  cout << "Dirección: " << usuario.direccion << endl;

  imprimirSeparador2();

  cout << "ID" << setw(7) << "|"
       << "Nombre" << setw(34) << "|"
       << "Cant"
       << "|"
       << "Precio" << endl;

  imprimirSeparador2();

  for (producto producto : usuario.carrito.productos) {
    cout << producto.id << "|" << producto.nombre
         << setw((40 - producto.nombre.size())) << "|" << producto.cantidad
         << "   "
         << "|" << fixed << setprecision(2)
         << (producto.precio * producto.cantidad) << endl;
  }

  imprimirSeparador2();

  cout << "Total sin descuento: " << fixed << setprecision(2)
       << usuario.carrito.total << endl;
  cout << "Descuento: " << usuario.carrito.descuento * 100 << "%" << endl;
  cout << "Total: " << fixed << setprecision(2)
       << usuario.carrito.total -
              (usuario.carrito.total * usuario.carrito.descuento)
       << endl;

  imprimirSeparador2();
  cout << "           ¡Gracias por comprar en Cartier Jewelry!       " << endl;
  imprimirSeparador2();
  exit(0);
}

int main() {
  usuario nuestroUsuario;
  menu(1, &nuestroUsuario, &(nuestroUsuario.carrito));
}

/*
int main() {
  usuario usuario1;
  usuario1.nombre = "Juan";
  usuario1.contrasena = "perrosconsalsa";
  usuario1.telefono = "123456789";
  usuario1.direccion = "Calle falsa 123";
  carrito carrito1;
  carrito carrito;
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
  carrito1.añadirProducto(producto1);
  usuario1.carrito = carrito1;
  GuardarUsuario(usuario1);
  string nombreusuario;
  getline(cin, nombreusuario);
  usuario usuario2 = LeerUsuario(nombreusuario + ".txt");
  cout << usuario2.nombre << endl;
  cout << usuario2.contrasena << endl;
  cout << usuario2.telefono << endl;
  cout << usuario2.direccion << endl;
  usuario2.carrito.mostrarCarrito();
}
*/