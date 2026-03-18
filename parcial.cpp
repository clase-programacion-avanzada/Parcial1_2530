// ============================================================================
// PARCIAL 1 - PROGRAMACIÓN AVANZADA
// Pontificia Universidad Javeriana - Departamento de Ingeniería de Sistemas
// ============================================================================
// PARTE I - RESPUESTAS CONCEPTUALES (20 PUNTOS)
// ============================================================================
// 1. (b) s1.append(s2) - append() es el método estándar de std::string para concatenar.
// 2. (b) Asigna 10 al tercer elemento - *(ptr+2) desplaza 2 posiciones desde el inicio (índice 2).
// 3. (c) ofstream file("archivo.txt", ios::out) - ofstream es para escritura, ios::out indica modo escritura.
// 4. (b) Falso - new asigna memoria dinámica, delete/delete[] la libera.
// 5. (a) void funcion(int *&ptr){...} - la referencia a un apuntador se declara como Tipo *&nombre.
// 6. (c) 0 - strcmp retorna 0 cuando las cadenas son exactamente iguales.
// 7. (c) good() - verifica que el estado del stream sea válido y sin errores.
// 8. (b) (*(p+i)).nombre - se desreferencia el apuntador desplazado para acceder al miembro.
// 9. (b) La dirección de memoria del primer elemento - el nombre del arreglo decae a un apuntador.
// 10. (a) Verdadero - se debe liberar la memoria con delete/delete[] para evitar fugas.
// ============================================================================

// ============================================================================
// PARTE II - PARTE PRÁCTICA (80 PUNTOS)
// ============================================================================

// ============================= BOILERPLATE ===================================
// Esta sección contiene las inclusiones de librerías, las definiciones de
// estructuras y las declaraciones adelantadas de funciones necesarias para
// el funcionamiento del sistema.
// =============================================================================

#include <iostream>   // Para entrada/salida estándar (cout, cin)
#include <fstream>    // Para manejo de archivos (ifstream, ofstream, fstream)
#include <cstring>    // Para funciones de cadenas C (strcmp, strcpy, strcat, strlen)
#include <string>     // Solo se usa std::string en los parámetros del punto 5
#include <sstream>    // Para stringstream, usado en la tokenización de datos (punto 7)

using namespace std;

// =============================================================================
// PUNTO 1 (5 puntos) - Definición de estructuras
// =============================================================================
// Se definen las estructuras Producto, Venta, Cliente y Tienda.
// Cada estructura modela una entidad del sistema de ventas de calzado.
// Los arreglos dinámicos requieren un campo adicional para rastrear su tamaño.
// =============================================================================

// Estructura Producto: representa un artículo de calzado en la tienda.
// Contiene código identificador, nombre, color, talla, cantidad en inventario y precio.
struct Producto {
    int codigo;              // Código único del producto
    char nombre[101];        // Nombre del producto (arreglo de caracteres)
    char color[21];          // Color del producto
    int talla;               // Talla del producto
    int cantidadExistente;   // Cantidad disponible en inventario
    float precio;            // Precio unitario del producto
};

// Estructura Venta: representa una transacción de venta realizada.
// Contiene el número de factura, un arreglo dinámico de productos vendidos,
// el nombre y el ID del cliente que realizó la compra.
struct Venta {
    int numFactura;          // Número único de factura
    Producto *productos;     // Arreglo dinámico de productos vendidos
    int numProductos;        // Cantidad de productos en la venta (necesario para el arreglo dinámico)
    char nombreCliente[101]; // Nombre del cliente
    int idCliente;           // ID del cliente
};

// Estructura Cliente: representa un cliente registrado en la tienda.
// Incluye un acumulado de compras para el programa de fidelización.
struct Cliente {
    char nombre[101];   // Nombre del cliente
    int id;             // ID único del cliente
    float acumulado;    // Total acumulado de compras (para puntos de fidelidad)
};

// Estructura Tienda: contiene todos los arreglos dinámicos del sistema.
// Es la estructura principal que agrupa ventas, clientes y productos.
// Cada arreglo dinámico tiene un contador asociado para saber su tamaño actual.
struct Tienda {
    Venta *ventas;         // Arreglo dinámico de ventas realizadas
    int numVentas;         // Cantidad de ventas registradas
    Cliente *clientes;     // Arreglo dinámico de clientes registrados
    int numClientes;       // Cantidad de clientes registrados
    Producto *productos;   // Arreglo dinámico de productos disponibles
    int numProductos;      // Cantidad de productos en la tienda
};

// ======================== DECLARACIONES ADELANTADAS ===========================
// Prototipos de todas las funciones que se implementan en este archivo.
// Esto permite llamar a cualquier función sin importar el orden de definición.
// =============================================================================

// Punto 2: Buscar un producto por nombre en el arreglo dinámico de la tienda
Producto* buscarProducto(Tienda &tienda, const char *nombre, float &precio, int &cantidadExistente);

// Punto 3: Agregar un producto al arreglo dinámico de la tienda
void agregarProducto(Tienda &tienda, int codigo, const char *nombre, const char *color, int talla, int cantidadExistente, float precio);

// Punto 4: Buscar un cliente en el archivo binario clientes.dat por nombre
int buscarClienteArchivo(const char *nombre);

// Punto 5: Auxiliar - buscar posición de un producto en productos.dat por nombre
int buscarProductoArchivo(const char *nomProducto);

// Punto 5: Realizar una venta completa actualizando arreglos y archivos
int hacerVenta(Tienda &tienda, string nombresProductos[], int numNombres, string nombreCliente);

// Punto 6: Generar archivo factura.txt con los datos de una venta
void generarFactura(int numFactura, Venta *ventas, int numVentas);

// Punto 7: Leer productos desde el archivo de texto productos.txt
void leerProductosTxt(Tienda &tienda);

// =============================================================================
// ============================= SOLUCIÓN ======================================
// A partir de aquí se implementa cada función solicitada en el examen.
// =============================================================================

// =============================================================================
// PUNTO 2 (10 puntos) - Buscar un producto
// =============================================================================
// Busca un producto por su nombre en el arreglo dinámico de productos de la Tienda.
// Recibe la tienda por referencia, el nombre a buscar, y dos referencias para
// retornar el precio y la cantidad existente del producto encontrado.
// Retorna un apuntador al producto si se encuentra, o nullptr si no existe.
// Se recorre el arreglo usando notación de índice (ptr[i]).
// =============================================================================
Producto* buscarProducto(Tienda &tienda, const char *nombre, float &precio, int &cantidadExistente) {
    // Recorremos el arreglo dinámico de productos con notación de índice
    for (int i = 0; i < tienda.numProductos; i++) {
        // tienda.productos[i] accede al elemento en la posición i
        if (strcmp(tienda.productos[i].nombre, nombre) == 0) {
            // Producto encontrado: se asignan los valores por referencia
            precio = tienda.productos[i].precio;
            cantidadExistente = tienda.productos[i].cantidadExistente;
            // Retornamos un apuntador al producto encontrado
            return &tienda.productos[i];
        }
    }
    // Si no se encontró el producto, retornamos nullptr
    return nullptr;
}

// =============================================================================
// PUNTO 3 (10 puntos) - Agregar un producto a la Tienda
// =============================================================================
// Recibe los datos del producto por valor y la Tienda por referencia.
// Primero verifica si el producto ya existe comparando nombres con strcmp.
// Si no existe, crea un nuevo arreglo dinámico con espacio para un producto más,
// copia los productos existentes, agrega el nuevo y libera el arreglo anterior.
// Se usa notación de índice para recorrer y copiar los elementos.
// =============================================================================
void agregarProducto(Tienda &tienda, 
    int codigo, 
    const char *nombre, 
    const char *color, 
    int talla, 
    int cantidadExistente, 
    float precio) {
    // Primero verificamos si el producto ya existe en la tienda
    for (int i = 0; i < tienda.numProductos; i++) {
        if (strcmp(tienda.productos[i].nombre, nombre) == 0) {
            // El producto ya existe, informamos al usuario y no lo agregamos
            cout << "El producto '" << nombre << "' ya existe en la tienda. No se agrego." << endl;
            return;
        }
    }

    // El producto no existe, procedemos a agregarlo
    // Creamos un nuevo arreglo dinámico con espacio para un producto adicional
    Producto *nuevoArreglo = new Producto[tienda.numProductos + 1];

    // Copiamos los productos existentes al nuevo arreglo
    for (int i = 0; i < tienda.numProductos; i++) {
        nuevoArreglo[i] = tienda.productos[i];
    }

    // Agregamos el nuevo producto al final del arreglo
    // Inicializamos cada campo del nuevo producto
    nuevoArreglo[tienda.numProductos].codigo = codigo;
    strcpy(nuevoArreglo[tienda.numProductos].nombre, nombre);
    strcpy(nuevoArreglo[tienda.numProductos].color, color);
    nuevoArreglo[tienda.numProductos].talla = talla;
    nuevoArreglo[tienda.numProductos].cantidadExistente = cantidadExistente;
    nuevoArreglo[tienda.numProductos].precio = precio;

    // Liberamos la memoria del arreglo anterior para evitar fugas de memoria
    if (tienda.numProductos > 0) {
        delete[] tienda.productos;
    }

    // Actualizamos el apuntador y el contador de la tienda
    tienda.productos = nuevoArreglo;
    tienda.numProductos++;
}

// =============================================================================
// PUNTO 4 (5 puntos) - Buscar un cliente en el archivo binario clientes.dat
// =============================================================================
// Dado el nombre del cliente, busca en el archivo binario clientes.dat.
// Lee cada estructura Cliente del archivo y compara el nombre usando strcmp.
// Retorna la posición (índice basado en 0) donde se encuentra el cliente,
// o -1 si no lo encuentra.
// Se usa fstream con ios::binary para leer el archivo binario.
// =============================================================================
int buscarClienteArchivo(const char *nombre) {
    // Abrimos el archivo binario en modo lectura
    ifstream archivo("clientes.dat", ios::binary | ios::in);

    // Verificamos que el archivo se haya abierto correctamente
    if (archivo.fail()) {
        cout << "Error: No se pudo abrir el archivo clientes.dat" << endl;
        return -1;
    }

    Cliente cliente;
    int posicion = 0;

    // Leemos cada estructura Cliente del archivo binario
    // reinterpret_cast convierte el apuntador a Cliente en un apuntador a char
    // para que read() pueda leer los bytes crudos en la estructura
    while (archivo.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))) {
        // Comparamos el nombre del cliente con el buscado
        if (strcmp(cliente.nombre, nombre) == 0) {
            archivo.close();
            return posicion; // Retornamos la posición donde se encontró
        }
        posicion++;
    }

    archivo.close();
    return -1; // No se encontró el cliente
}

// =============================================================================
// PUNTO 5 - FUNCIÓN AUXILIAR: Buscar producto en productos.dat
// =============================================================================
// El enunciado indica "Suponga que tiene el método int buscarProducto(string
// nomProducto) que retorna la posición del producto en productos.dat o -1".
// Aquí lo implementamos para completar la funcionalidad.
// Busca un producto por nombre en el archivo binario productos.dat.
// =============================================================================
int buscarProductoArchivo(const char *nomProducto) {
    // Abrimos el archivo binario de productos en modo lectura
    ifstream archivo("productos.dat", ios::binary | ios::in);

    if (archivo.fail()) {
        cout << "Error: No se pudo abrir el archivo productos.dat" << endl;
        return -1;
    }

    Producto producto;
    int posicion = 0;

    // Leemos cada estructura Producto del archivo
    while (archivo.read(reinterpret_cast<char*>(&producto), sizeof(Producto))) {
        if (strcmp(producto.nombre, nomProducto) == 0) {
            archivo.close();
            return posicion;
        }
        posicion++;
    }

    archivo.close();
    return -1;
}

// =============================================================================
// PUNTO 5 (25 puntos) - Hacer una Venta
// =============================================================================
// Función principal de venta. Recibe la Tienda por referencia, un arreglo de
// nombres de productos (std::string, según el enunciado) y el nombre del cliente.
// 
// Proceso:
// 1. Busca cada producto en la tienda y verifica disponibilidad
// 2. Crea un arreglo dinámico con los productos que sí se pueden vender
// 3. Calcula el valor total de la venta
// 4. Actualiza el arreglo dinámico de productos (decrementa cantidad)
// 5. Crea la venta y la agrega al arreglo dinámico de ventas
// 6. Actualiza el acumulado del cliente en el arreglo de clientes
// 7. Actualiza los tres archivos binarios: ventas.dat, productos.dat, clientes.dat
// 8. Retorna el número de factura generado
//
// NOTA: Se usa std::string SOLO en los parámetros, como indica el enunciado.
// Internamente se convierte a C-string con c_str() para las comparaciones.
// =============================================================================
int hacerVenta(Tienda &tienda, string nombresProductos[], int numNombres, string nombreCliente) {
    // Generamos el número de factura incrementando el total de ventas
    int numFactura = tienda.numVentas + 1;

    // Creamos un arreglo temporal para almacenar los productos vendidos
    // Su tamaño máximo posible es numNombres (si todos los productos se encuentran)
    Producto *productosVendidos = new Producto[numNombres];
    int cantVendidos = 0;    // Contador de productos efectivamente vendidos
    float totalVenta = 0.0;  // Acumulador del valor total de la venta

    // Recorremos cada nombre de producto solicitado
    for (int i = 0; i < numNombres; i++) {
        float precio = 0;
        int cantidad = 0;

        // Buscamos el producto en el arreglo dinámico de la tienda
        // Usamos c_str() para convertir el std::string a const char*
        Producto *encontrado = buscarProducto(tienda, nombresProductos[i].c_str(), precio, cantidad);

        if (encontrado == nullptr) {
            // El producto no existe en la tienda
            cout << "Producto '" << nombresProductos[i] << "' no encontrado en la tienda." << endl;
        } else if (encontrado->cantidadExistente <= 0) {
            // El producto existe pero no hay inventario disponible
            cout << "Producto '" << nombresProductos[i] << "' sin existencias disponibles." << endl;
        } else {
            // El producto está disponible: decrementamos la cantidad en el arreglo dinámico
            encontrado->cantidadExistente--;

            // Copiamos el producto al arreglo de productos vendidos
            productosVendidos[cantVendidos] = *encontrado;
            // La cantidad vendida es 1 por producto en esta lógica
            productosVendidos[cantVendidos].cantidadExistente = 1;

            // Acumulamos el precio al total
            totalVenta += precio;
            cantVendidos++;

            // Actualizamos el archivo binario productos.dat
            // Buscamos la posición del producto en el archivo
            int posArchivo = buscarProductoArchivo(encontrado->nombre);
            if (posArchivo != -1) {
                // Abrimos el archivo en modo lectura/escritura binaria
                fstream archProductos("productos.dat", ios::binary | ios::in | ios::out);
                if (archProductos.good()) {
                    // Nos posicionamos en la ubicación correcta del producto
                    // usando seekp con el desplazamiento calculado
                    archProductos.seekp(posArchivo * sizeof(Producto));
                    // Escribimos el producto actualizado (con cantidad decrementada)
                    archProductos.write(reinterpret_cast<char*>(encontrado), sizeof(Producto));
                    archProductos.close();
                }
            }
        }
    }

    // Si no se vendió ningún producto, liberamos memoria y retornamos -1
    if (cantVendidos == 0) {
        delete[] productosVendidos;
        cout << "No se pudo realizar la venta. Ningun producto disponible." << endl;
        return -1;
    }

    // Creamos la estructura Venta con los datos de la transacción
    Venta nuevaVenta;
    nuevaVenta.numFactura = numFactura;
    nuevaVenta.numProductos = cantVendidos;

    // Creamos un arreglo dinámico del tamaño exacto de productos vendidos
    nuevaVenta.productos = new Producto[cantVendidos];
    for (int i = 0; i < cantVendidos; i++) {
        nuevaVenta.productos[i] = productosVendidos[i];
    }

    // Copiamos el nombre del cliente (convertimos de string a C-string)
    strcpy(nuevaVenta.nombreCliente, nombreCliente.c_str());

    // Buscamos el cliente en el arreglo dinámico de la tienda para obtener su ID
    // y actualizar su acumulado
    nuevaVenta.idCliente = 0; // Valor por defecto
    for (int i = 0; i < tienda.numClientes; i++) {
        if (strcmp(tienda.clientes[i].nombre, nombreCliente.c_str()) == 0) {
            nuevaVenta.idCliente = tienda.clientes[i].id;
            // Actualizamos el acumulado del cliente en el arreglo dinámico
            tienda.clientes[i].acumulado += totalVenta;

            // Actualizamos el acumulado del cliente en clientes.dat
            int posCliente = buscarClienteArchivo(tienda.clientes[i].nombre);
            if (posCliente != -1) {
                fstream archClientes("clientes.dat", ios::binary | ios::in | ios::out);
                if (archClientes.good()) {
                    // Nos posicionamos en la ubicación del cliente en el archivo
                    archClientes.seekp(posCliente * sizeof(Cliente));
                    // Escribimos el cliente actualizado
                    archClientes.write(reinterpret_cast<char*>(&tienda.clientes[i]), sizeof(Cliente));
                    archClientes.close();
                }
            }
            break; // Ya encontramos al cliente, salimos del bucle
        }
    }

    // Agregamos la venta al arreglo dinámico de ventas de la tienda
    // Creamos un nuevo arreglo con espacio para una venta más
    Venta *nuevoArregloVentas = new Venta[tienda.numVentas + 1];
    for (int i = 0; i < tienda.numVentas; i++) {
        nuevoArregloVentas[i] = tienda.ventas[i];
    }
    nuevoArregloVentas[tienda.numVentas] = nuevaVenta;

    // Liberamos el arreglo anterior de ventas
    if (tienda.numVentas > 0) {
        delete[] tienda.ventas;
    }
    tienda.ventas = nuevoArregloVentas;
    tienda.numVentas++;

    // Adicionamos la venta al final del archivo binario ventas.dat
    // Usamos ios::app para agregar al final sin sobrescribir datos existentes
    ofstream archVentas("ventas.dat", ios::binary | ios::app);
    if (archVentas.good()) {
        archVentas.write(reinterpret_cast<char*>(&nuevaVenta), sizeof(Venta));
        archVentas.close();
    }

    // Liberamos la memoria del arreglo temporal de productos vendidos
    delete[] productosVendidos;

    // Retornamos el número de factura generado
    return numFactura;
}

// =============================================================================
// PUNTO 6 (10 puntos) - Generar factura
// =============================================================================
// Dado el número de factura y el arreglo dinámico de ventas de una Tienda,
// genera un archivo de texto "factura.txt" con los datos formateados.
// Busca la venta correspondiente al número de factura en el arreglo.
// Luego escribe los datos del cliente y los productos vendidos con formato
// alineado, siguiendo el ejemplo del enunciado.
// Se recorre el arreglo usando notación de índice.
// =============================================================================
void generarFactura(int numFactura, Venta *ventas, int numVentas) {
    // Buscamos la venta con el número de factura dado
    Venta *ventaEncontrada = nullptr;

    for (int i = 0; i < numVentas; i++) {
        if (ventas[i].numFactura == numFactura) {
            ventaEncontrada = &ventas[i];
            break;
        }
    }

    // Si no se encontró la venta, informamos al usuario
    if (ventaEncontrada == nullptr) {
        cout << "Error: No se encontro la venta con factura No. " << numFactura << endl;
        return;
    }

    // Abrimos el archivo de texto para escritura
    ofstream archivo("factura.txt", ios::out);

    if (!archivo.good()) {
        cout << "Error: No se pudo crear el archivo factura.txt" << endl;
        return;
    }

    // Escribimos el encabezado de la factura
    archivo << "Factura No. " << ventaEncontrada->numFactura << endl;
    archivo << "Cliente: " << ventaEncontrada->nombreCliente << endl;
    archivo << "ID: " << ventaEncontrada->idCliente << endl;
    archivo << "Productos vendidos" << endl;

    // Calculamos el valor total mientras recorremos los productos
    float valorTotal = 0;

    // Recorremos los productos vendidos con notación de índice
    for (int i = 0; i < ventaEncontrada->numProductos; i++) {
        Producto prod = ventaEncontrada->productos[i];

        // Escribimos código, nombre, color y talla en una línea
        archivo << prod.codigo << "  " << prod.nombre;

        // Espaciado para alinear las columnas (ajuste básico)
        int espacios = 16 - strlen(prod.nombre);
        for (int j = 0; j < espacios; j++) {
            archivo << " ";
        }

        archivo << prod.color;

        // Espaciado después del color
        int espaciosColor = 10 - strlen(prod.color);
        for (int j = 0; j < espaciosColor; j++) {
            archivo << " ";
        }

        archivo << prod.talla << endl;

        // Escribimos el precio en la línea siguiente con indentación
        archivo << "      $" << (int)prod.precio << endl;

        // Acumulamos el precio al total
        valorTotal += prod.precio;
    }

    // Escribimos el valor total al final
    archivo << endl;
    archivo << "Valor total: $" << (int)valorTotal << endl;

    archivo.close();
    cout << "Factura generada exitosamente en factura.txt" << endl;
}

// =============================================================================
// PUNTO 7 (15 puntos) - Leer productos desde productos.txt
// =============================================================================
// Lee el archivo de texto productos.txt con un formato específico:
// - Primera línea: número total de productos
// - Segunda línea: la palabra "Productos"
// - Luego, grupos de productos donde:
//   - Una línea tiene el nombre del tipo de producto
//   - Las siguientes líneas tienen: codigo,color,talla,precio,cantidad
//   - El carácter '%' indica el fin de un grupo
//
// Se usa stringstream para separar los campos por comas (más seguro que strtok).
// Los productos se almacenan en un arreglo dinámico en la Tienda.
// Se recorre con notación de índice.
// =============================================================================
void leerProductosTxt(Tienda &tienda) {
    // Abrimos el archivo de texto en modo lectura
    ifstream archivo("productos.txt", ios::in);

    if (!archivo.good()) {
        cout << "Error: No se pudo abrir el archivo productos.txt" << endl;
        return;
    }

    // Leemos el número total de productos (primera línea)
    int totalProductos = 0;
    archivo >> totalProductos;
    archivo.ignore(); // Ignoramos el salto de línea después del número

    // Leemos la palabra "Productos" (segunda línea) y la descartamos
    char lineaDescarte[100];
    archivo.getline(lineaDescarte, 100);

    // Creamos el arreglo dinámico con el tamaño total de productos
    Producto *productos = new Producto[totalProductos];
    int contadorProductos = 0;

    // Variable para almacenar el nombre del tipo de producto actual
    char nombreProducto[100];

    // Buffer para leer cada línea del archivo
    char linea[256];

    // Leemos el archivo línea por línea
    while (archivo.getline(linea, 256) && contadorProductos < totalProductos) {
        // Verificamos si la línea es el carácter de fin de grupo
        if (strcmp(linea, "%") == 0) {
            // Fin de un grupo de productos, la siguiente línea será un nuevo nombre
            continue;
        }

        // Verificamos si la línea contiene una coma (indica datos de producto)
        // Si no contiene coma, es el nombre del tipo de producto
        bool esDatos = false;
        for (int i = 0; i < (int)strlen(linea); i++) {
            if (linea[i] == ',') {
                esDatos = true;
                break;
            }
        }

        if (!esDatos) {
            // Es el nombre del tipo de producto (ej: "Tenis", "Sandalias")
            strcpy(nombreProducto, linea);
        } else {
            // Es una línea de datos: codigo,color,talla,precio,cantidad
            // Usamos stringstream para tokenizar la línea separada por comas
            // stringstream es más seguro que strtok porque no modifica la cadena original
            // y permite extraer tipos de datos directamente

            stringstream ss(linea);  // Creamos un flujo a partir de la línea leída
            char campo[100];         // Buffer temporal para cada campo extraído

            // Extraemos el código (primer campo, antes de la primera coma)
            ss.getline(campo, 100, ',');
            productos[contadorProductos].codigo = atoi(campo);

            // Extraemos el color (segundo campo)
            ss.getline(campo, 100, ',');
            strcpy(productos[contadorProductos].color, campo);

            // Extraemos la talla (tercer campo)
            ss.getline(campo, 100, ',');
            productos[contadorProductos].talla = atoi(campo);

            // Extraemos el precio (cuarto campo)
            ss.getline(campo, 100, ',');
            productos[contadorProductos].precio = atof(campo);

            // Extraemos la cantidad existente (quinto y último campo)
            ss.getline(campo, 100, ',');
            productos[contadorProductos].cantidadExistente = atoi(campo);

            // Copiamos el nombre del tipo de producto al campo nombre
            strcpy(productos[contadorProductos].nombre, nombreProducto);

            contadorProductos++;
        }
    }

    archivo.close();

    // Liberamos el arreglo anterior si existía
    if (tienda.numProductos > 0 && tienda.productos != nullptr) {
        delete[] tienda.productos;
    }

    // Asignamos el nuevo arreglo y actualizamos el contador
    tienda.productos = productos;
    tienda.numProductos = contadorProductos;

    cout << "Se leyeron " << contadorProductos << " productos desde productos.txt" << endl;
}

// =============================================================================
// FUNCIÓN MAIN - Pruebas del sistema
// =============================================================================
// Esta función main prueba cada punto práctico del parcial con datos de ejemplo.
// Se imprime un encabezado por cada punto para facilitar la verificación visual.
// Se crean archivos binarios y de texto necesarios para las pruebas.
// =============================================================================
int main() {
    // =========================================================================
    // INICIALIZACIÓN - Creamos la tienda vacía
    // =========================================================================
    Tienda tienda;
    tienda.ventas = nullptr;
    tienda.numVentas = 0;
    tienda.clientes = nullptr;
    tienda.numClientes = 0;
    tienda.productos = nullptr;
    tienda.numProductos = 0;

    cout << "============================================" << endl;
    cout << "   SISTEMA DE VENTAS DE CALZADO - PRUEBAS  " << endl;
    cout << "============================================" << endl << endl;

    // =========================================================================
    // TEST PUNTO 3 - Agregar productos a la Tienda
    // =========================================================================
    // Se ejecuta primero que el punto 2 para que existan productos en la tienda
    // que luego puedan ser buscados. Probamos:
    // - Agregar 4 productos distintos (debe funcionar sin problemas)
    // - Intentar agregar un producto duplicado (debe informar y rechazar)
    // =========================================================================
    cout << "========== TEST PUNTO 3: Agregar Producto ==========" << endl;

    // Agregamos 4 productos de ejemplo, basados en los datos del enunciado
    agregarProducto(tienda, 1213, "Tenis", "Blanco", 36, 5, 50000);
    agregarProducto(tienda, 2635, "Sandalias", "Azules", 36, 8, 100000);
    agregarProducto(tienda, 3456, "Zapato colegial", "Vinotinto", 42, 7, 180000);
    agregarProducto(tienda, 1218, "Tenis deportivo", "Gris", 28, 10, 70000);

    // Intentamos agregar un producto que ya existe (debe mostrar mensaje de error)
    cout << "[Prueba duplicado] ";
    agregarProducto(tienda, 9999, "Tenis", "Rojo", 40, 3, 60000);

    // Verificamos el contenido del arreglo dinámico de productos
    cout << endl << "Productos en la tienda (" << tienda.numProductos << " total):" << endl;
    for (int i = 0; i < tienda.numProductos; i++) {
        cout << "  [" << i << "] Cod:" << tienda.productos[i].codigo
             << " | " << tienda.productos[i].nombre
             << " | " << tienda.productos[i].color
             << " | Talla:" << tienda.productos[i].talla
             << " | Cant:" << tienda.productos[i].cantidadExistente
             << " | $" << tienda.productos[i].precio << endl;
    }
    cout << endl;

    // =========================================================================
    // TEST PUNTO 2 - Buscar un producto
    // =========================================================================
    // Probamos buscar un producto que SÍ existe ("Sandalias") y uno que NO
    // existe ("Botas"). Verificamos que retorne el apuntador correcto o nullptr.
    // =========================================================================
    cout << "========== TEST PUNTO 2: Buscar Producto ==========" << endl;

    float precioEncontrado = 0;
    int cantidadEncontrada = 0;

    // Caso 1: producto que sí existe
    Producto *resultado = buscarProducto(tienda, "Sandalias", precioEncontrado, cantidadEncontrada);
    if (resultado != nullptr) {
        cout << "[OK] Producto 'Sandalias' encontrado:" << endl;
        cout << "     Precio: $" << precioEncontrado
             << " | Cantidad: " << cantidadEncontrada << endl;
    } else {
        cout << "[ERROR] 'Sandalias' deberia haberse encontrado." << endl;
    }

    // Caso 2: producto que NO existe
    resultado = buscarProducto(tienda, "Botas", precioEncontrado, cantidadEncontrada);
    if (resultado == nullptr) {
        cout << "[OK] Producto 'Botas' no encontrado (retorno nullptr, correcto)." << endl;
    } else {
        cout << "[ERROR] 'Botas' no deberia haberse encontrado." << endl;
    }
    cout << endl;

    // =========================================================================
    // SEMILLA: Crear arreglo dinámico de clientes y archivo clientes.dat
    // =========================================================================
    // Estos datos son necesarios para probar los puntos 4 y 5.
    // Creamos 2 clientes de ejemplo y los escribimos en el archivo binario.
    // =========================================================================
    cout << "========== SEMILLA: Clientes y archivos binarios ==========" << endl;

    // Creamos el arreglo dinámico de clientes
    tienda.numClientes = 2;
    tienda.clientes = new Cliente[2];

    // Cliente 1: Ines Jimenez (del ejemplo de factura del enunciado)
    strcpy(tienda.clientes[0].nombre, "Ines Jimenez");
    tienda.clientes[0].id = 28500404;
    tienda.clientes[0].acumulado = 0.0;

    // Cliente 2: Juan Perez
    strcpy(tienda.clientes[1].nombre, "Juan Perez");
    tienda.clientes[1].id = 12345678;
    tienda.clientes[1].acumulado = 0.0;

    // Escribimos los clientes en el archivo binario clientes.dat
    {
        ofstream archClientes("clientes.dat", ios::binary | ios::out);
        if (archClientes.good()) {
            for (int i = 0; i < tienda.numClientes; i++) {
                archClientes.write(reinterpret_cast<char*>(&tienda.clientes[i]), sizeof(Cliente));
            }
            archClientes.close();
            cout << "[OK] clientes.dat creado con " << tienda.numClientes << " clientes." << endl;
        } else {
            cout << "[ERROR] No se pudo crear clientes.dat" << endl;
        }
    }

    // Escribimos los productos actuales en el archivo binario productos.dat
    {
        ofstream archProductos("productos.dat", ios::binary | ios::out);
        if (archProductos.good()) {
            for (int i = 0; i < tienda.numProductos; i++) {
                archProductos.write(reinterpret_cast<char*>(&tienda.productos[i]), sizeof(Producto));
            }
            archProductos.close();
            cout << "[OK] productos.dat creado con " << tienda.numProductos << " productos." << endl;
        } else {
            cout << "[ERROR] No se pudo crear productos.dat" << endl;
        }
    }

    // Creamos el archivo ventas.dat vacío (se llenará en el punto 5)
    {
        ofstream archVentas("ventas.dat", ios::binary | ios::out);
        archVentas.close();
        cout << "[OK] ventas.dat creado (vacio)." << endl;
    }
    cout << endl;

    // =========================================================================
    // TEST PUNTO 4 - Buscar cliente en archivo binario clientes.dat
    // =========================================================================
    // Probamos buscar un cliente que SÍ existe ("Ines Jimenez", esperado pos 0)
    // y uno que NO existe ("Carlos Lopez", esperado -1).
    // =========================================================================
    cout << "========== TEST PUNTO 4: Buscar Cliente en Archivo ==========" << endl;

    // Caso 1: cliente que existe (posición 0)
    int posCliente = buscarClienteArchivo("Ines Jimenez");
    cout << "[Buscar 'Ines Jimenez'] Posicion: " << posCliente
         << (posCliente == 0 ? " [OK]" : " [ERROR: esperado 0]") << endl;

    // Caso 2: cliente que existe (posición 1)
    posCliente = buscarClienteArchivo("Juan Perez");
    cout << "[Buscar 'Juan Perez']   Posicion: " << posCliente
         << (posCliente == 1 ? " [OK]" : " [ERROR: esperado 1]") << endl;

    // Caso 3: cliente que NO existe
    posCliente = buscarClienteArchivo("Carlos Lopez");
    cout << "[Buscar 'Carlos Lopez'] Posicion: " << posCliente
         << (posCliente == -1 ? " [OK]" : " [ERROR: esperado -1]") << endl;
    cout << endl;

    // =========================================================================
    // TEST PUNTO 5 - Hacer una Venta
    // =========================================================================
    // Realizamos una venta con 3 nombres de productos:
    // - "Tenis" (existe, cantidad 5 -> 4)
    // - "Sandalias" (existe, cantidad 8 -> 7)
    // - "Botas" (NO existe, debe informar por pantalla)
    // El cliente es "Ines Jimenez".
    // Verificamos:
    // - Retorna un número de factura válido (> 0)
    // - tienda.numVentas se incrementó a 1
    // - Las cantidades de productos decrementaron correctamente
    // - El acumulado de Ines Jimenez se actualizó (50000 + 100000 = 150000)
    // =========================================================================
    cout << "========== TEST PUNTO 5: Hacer Venta ==========" << endl;

    // Creamos el arreglo de nombres de productos para la venta
    string productosVenta[] = {"Tenis", "Sandalias", "Botas"};

    // Realizamos la venta (3 productos solicitados, 2 vendibles)
    int factura = hacerVenta(tienda, productosVenta, 3, "Ines Jimenez");

    cout << endl << "Resultados de la venta:" << endl;
    cout << "  Numero de factura: " << factura
         << (factura > 0 ? " [OK]" : " [ERROR]") << endl;
    cout << "  Ventas en tienda: " << tienda.numVentas
         << (tienda.numVentas == 1 ? " [OK]" : " [ERROR: esperado 1]") << endl;

    // Verificamos cantidades decrementadas
    float p = 0; int c = 0;
    buscarProducto(tienda, "Tenis", p, c);
    cout << "  Tenis - cantidad restante: " << c
         << (c == 4 ? " [OK]" : " [ERROR: esperado 4]") << endl;

    buscarProducto(tienda, "Sandalias", p, c);
    cout << "  Sandalias - cantidad restante: " << c
         << (c == 7 ? " [OK]" : " [ERROR: esperado 7]") << endl;

    // Verificamos el acumulado del cliente
    for (int i = 0; i < tienda.numClientes; i++) {
        if (strcmp(tienda.clientes[i].nombre, "Ines Jimenez") == 0) {
            cout << "  Acumulado Ines Jimenez: $" << tienda.clientes[i].acumulado
                 << (tienda.clientes[i].acumulado == 150000.0f ? " [OK]" : " [ERROR: esperado 150000]")
                 << endl;
        }
    }

    // Realizamos una segunda venta para "Juan Perez" con "Zapato colegial"
    string productosVenta2[] = {"Zapato colegial"};
    int factura2 = hacerVenta(tienda, productosVenta2, 1, "Juan Perez");

    cout << endl << "Segunda venta (Juan Perez):" << endl;
    cout << "  Numero de factura: " << factura2
         << (factura2 == 2 ? " [OK]" : " [ERROR: esperado 2]") << endl;
    cout << "  Ventas en tienda: " << tienda.numVentas
         << (tienda.numVentas == 2 ? " [OK]" : " [ERROR: esperado 2]") << endl;

    buscarProducto(tienda, "Zapato colegial", p, c);
    cout << "  Zapato colegial - cantidad restante: " << c
         << (c == 6 ? " [OK]" : " [ERROR: esperado 6]") << endl;
    cout << endl;

    // =========================================================================
    // TEST PUNTO 6 - Generar Factura
    // =========================================================================
    // Generamos la factura de la primera venta (factura No. 1).
    // Luego leemos e imprimimos el contenido de factura.txt en consola
    // para verificar que el formato sea correcto según el enunciado.
    // =========================================================================
    cout << "========== TEST PUNTO 6: Generar Factura ==========" << endl;

    // Generamos la factura de la primera venta
    generarFactura(factura, tienda.ventas, tienda.numVentas);

    // Leemos e imprimimos el contenido de factura.txt para verificación
    cout << "--- Contenido de factura.txt ---" << endl;
    {
        ifstream archFactura("factura.txt", ios::in);
        if (archFactura.good()) {
            char lineaFactura[256];
            while (archFactura.getline(lineaFactura, 256)) {
                cout << lineaFactura << endl;
            }
            archFactura.close();
        } else {
            cout << "[ERROR] No se pudo leer factura.txt" << endl;
        }
    }
    cout << "--- Fin de factura.txt ---" << endl;

    // Generamos también la factura de la segunda venta para verificar
    cout << endl;
    generarFactura(factura2, tienda.ventas, tienda.numVentas);
    cout << "--- Contenido de factura.txt (2da venta) ---" << endl;
    {
        ifstream archFactura("factura.txt", ios::in);
        if (archFactura.good()) {
            char lineaFactura[256];
            while (archFactura.getline(lineaFactura, 256)) {
                cout << lineaFactura << endl;
            }
            archFactura.close();
        } else {
            cout << "[ERROR] No se pudo leer factura.txt" << endl;
        }
    }
    cout << "--- Fin de factura.txt ---" << endl;
    cout << endl;

    // =========================================================================
    // TEST PUNTO 7 - Leer productos desde productos.txt
    // =========================================================================
    // Primero creamos el archivo productos.txt con el formato del enunciado.
    // Luego llamamos a leerProductosTxt y verificamos que se cargaron
    // correctamente los 5 productos.
    // =========================================================================
    cout << "========== TEST PUNTO 7: Leer Productos de TXT ==========" << endl;

    // Creamos el archivo productos.txt con los datos de ejemplo del enunciado
    {
        ofstream archTxt("productos.txt", ios::out);
        archTxt << "5" << endl;
        archTxt << "Productos" << endl;
        archTxt << "Tenis" << endl;
        archTxt << "1218,Gris,28,70000,10" << endl;
        archTxt << "1213,Blanco,36,50000,5" << endl;
        archTxt << "%" << endl;
        archTxt << "Sandalias" << endl;
        archTxt << "2635,Azules,36,100000,8" << endl;
        archTxt << "%" << endl;
        archTxt << "Zapato colegial" << endl;
        archTxt << "3456,Vinotinto,42,180000,7" << endl;
        archTxt << "3457,Azul Oscuro,39,165000,4" << endl;
        archTxt << "%" << endl;
        archTxt.close();
        cout << "[OK] productos.txt creado con datos de ejemplo." << endl;
    }

    // Llamamos a la función (esto reemplaza el arreglo dinámico de productos)
    leerProductosTxt(tienda);

    // Verificamos la cantidad de productos cargados
    cout << "Productos cargados: " << tienda.numProductos
         << (tienda.numProductos == 5 ? " [OK]" : " [ERROR: esperado 5]") << endl;

    // Imprimimos cada producto cargado para verificación
    cout << "Detalle de productos:" << endl;
    for (int i = 0; i < tienda.numProductos; i++) {
        cout << "  [" << i << "] Cod:" << tienda.productos[i].codigo
             << " | " << tienda.productos[i].nombre
             << " | " << tienda.productos[i].color
             << " | Talla:" << tienda.productos[i].talla
             << " | Cant:" << tienda.productos[i].cantidadExistente
             << " | $" << tienda.productos[i].precio << endl;
    }
    cout << endl;

    // =========================================================================
    // RESUMEN FINAL
    // =========================================================================
    cout << "============================================" << endl;
    cout << "   TODAS LAS PRUEBAS FINALIZADAS           " << endl;
    cout << "============================================" << endl;

    // =========================================================================
    // LIMPIEZA - Liberamos toda la memoria dinámica
    // =========================================================================
    // Es fundamental liberar la memoria asignada con new/new[] para evitar
    // fugas de memoria (memory leaks). Se libera en orden inverso a la asignación.
    // =========================================================================
    if (tienda.numProductos > 0) {
        delete[] tienda.productos;
    }
    if (tienda.numClientes > 0) {
        delete[] tienda.clientes;
    }
    // Liberamos la memoria de los productos dentro de cada venta
    for (int i = 0; i < tienda.numVentas; i++) {
        if (tienda.ventas[i].numProductos > 0) {
            delete[] tienda.ventas[i].productos;
        }
    }
    if (tienda.numVentas > 0) {
        delete[] tienda.ventas;
    }

    return 0;
}
