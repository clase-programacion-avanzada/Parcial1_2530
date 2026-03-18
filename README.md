# Exámen de programación avanzada 2530



## I. (20 PUNTOS) CONCEPTOS

1. ¿Cuál es la forma correcta de concatenar dos objetos `string` en C++?
* [ ] a. `strcat(s1, s2);`
* [ ] b. `s1.append(s2);`
* [ ] c. `s1.add(s2);`
* [ ] d. b y c son correctas


<details>
<summary>Respuesta</summary>
Opción (b). El método `append()` es una función estándar de la clase `std::string` en C++ utilizada para concatenar. (El operador `+` también es correcto pero no está listado).
</details>

2. ¿Qué hará el siguiente código?
   
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int *ptr = arr;
*(ptr + 2) = 10;

```


* [ ] a. Asignará el valor 10 al primer elemento de arr.
* [ ] b. Asignará el valor 10 al tercer elemento de arr.
* [ ] c. Asignará el valor 10 al segundo elemento de arr.
* [ ] d. Asignará el valor 10 al cuarto elemento de arr.


<details>
<summary>Respuesta</summary>
Opción (b). Utilizando aritmética de apuntadores, `ptr + 2` desplaza la dirección de memoria dos posiciones enteras hacia adelante, apuntando al índice 2 (el tercer elemento del arreglo). Al desreferenciarlo y asignarle 10, modifica ese tercer elemento. 	</details>

3. ¿Cuál es el formato correcto para abrir un archivo de texto en modo de escritura en C++?
* [ ] a. `ofstream file("archivo.txt", ios::in);`
* [ ] b. `ifstream file("archivo.txt", ios::out);`
* [ ] c. `ofstream file("archivo.txt", ios::out);`
* [ ] d. `fstream file("archivo.txt", ios::in);`


<details>
<summary>Respuesta</summary>
Opción (c). La clase `ofstream` se utiliza para escritura (output file stream) y la bandera `ios::out` especifica explícitamente el modo de escritura.
</details>

4. En C++, el operador `new` se utiliza para liberar memoria asignada dinámicamente.
* [ ] a. Verdadero
* [ ] b. Falso


<details>
<summary>Respuesta</summary>
Opción (b) Falso. El operador `new` se utiliza para asignar memoria dinámicamente. Para liberarla, se utiliza el operador `delete` o `delete[]`.
</details>

5. ¿Cual es la forma correcta de recibir un apuntador por referencia en C++?
* [ ] a. `void funcion(int *&ptr){...}`
* [ ] b. `void funcion(int &ptr){...}`
* [ ] c. `void funcion(int *ptr){...}`
* [ ] d. `void funcion(int &*ptr){...}`


<details>
<summary>Respuesta</summary>
Opción (a). La sintaxis correcta en C++ para una referencia a un tipo de dato es `Tipo &amp;nombre`. Si el tipo de dato es un apuntador a entero (`int *`), la sintaxis correcta es `int *&amp;ptr`.
</details>

6. ¿Qué devuelve la función `strcmp("hola", "hola");`?
* [ ] a. true
* [ ] b. false
* [ ] c. 0
* [ ] d. 1


<details>
<summary>Respuesta</summary>
Opción (c). La función `strcmp` devuelve 0 cuando ambas cadenas de caracteres alfanuméricos son exactamente iguales.
</details>

7. ¿Qué función de la clase `ifstream` se utiliza para verificar si la apertura del archivo fue exitosa?
* [ ] a. `eof()`
* [ ] b. `fail()`
* [ ] c. `good()`
* [ ] d. `!fail()`


<details>
<summary>Respuesta</summary>
Opción (c). La función `good()` verifica si el estado del stream es válido y no se ha producido ningún error (incluyendo que el archivo se haya abierto correctamente). `fail()` también se usa, pero requiere ser negada, y la opción (d) no es el nombre de la función en sí.
</details>

8. Dada la estructura:
```cpp
struct Persona {
    char nombre[20];
    int edad;
};
Persona arr[3];
Persona *p = arr;

```


¿Cuál es la forma correcta de recorrer `p`, usando notación de apuntadores?
* [ ] a. `for(int i=0; i<3; i++) cout << p[i].nombre;`
* [ ] b. `for(int i=0; i<3; i++) cout << (*(p+i)).nombre;`
* [ ] c. `for(int i=0; i<3; i++) cout << p.nombre;`
* [ ] d. `for(int i=0; i<3; i++) cout << *(p+i)->nombre;`


<details>
<summary>Respuesta</summary>
Opción (b). `*(p+i)` desreferencia la dirección desplazada correctamente para obtener el objeto `Persona`, del cual luego se accede al atributo `.nombre`.
</details>

9. Dado `int numeros[5];`, ¿qué muestra por pantalla la instrucción `cout << numeros << endl;`?
* [ ] a. El valor del primer elemento del arreglo
* [ ] b. La dirección de memoria del primer elemento
* [ ] c. El listado de elementos del arreglo
* [ ] d. Genera error, no se puede imprimir por consola sin un índice


<details>
<summary>Respuesta</summary>
Opción (b). Al pasar el nombre de un arreglo a `cout`, el arreglo decae implícitamente a un apuntador a su primer elemento, imprimiendo su dirección en memoria.
</details>

10. Al usar memoria dinámica con apuntadores en C++, siempre que sea necesario liberar memoria se usa `delete` o `delete[]` con el fin de no desperdiciar la memoria.
* [ ] a. Verdadero
* [ ] b. Falso


<details>
<summary>Respuesta</summary>
Opción (a) Verdadero. Es fundamental liberar cualquier recurso reservado con `new` o `new[]` mediante sus correspondientes `delete` o `delete[]` para evitar fugas de memoria (memory leaks). 	</details>

---

## II. (80 PUNTOS) PARTE PRÁCTICA

Una prestigiosa cadena de calzado lo ha contratado para crear un sistema que les permita manejar las ventas en sus tiendas. Además, desea generar políticas de fidelización para sus clientes y de esta manera volverlos frecuentes.

**Información de una Venta:**

1. Número de factura: entero (int).
2. Productos vendidos: arreglo dinámico de productos.
3. Nombre del cliente: arreglo de 100 caracteres.
4. ID del cliente: entero (int).

**Información de una Tienda:**

1. **Ventas:** arreglo dinámico de Ventas, además, se cuenta con un archivo binario **ventas.dat** que contiene todas las estructuras de tipo Venta que se encuentran en el arreglo dinámico de ventas.
2. **Clientes:** arreglo dinámico de Clientes. Además, se cuenta con un archivo binario **clientes.dat** que contiene todas las estructuras de tipo Cliente que se encuentran en el arreglo dinámico de clientes.
3. **Productos:** arreglo dinámico de productos. También, se cuenta con un archivo binario **productos.dat** que contiene todas las estructuras de tipo Producto que se encuentran en el arreglo dinámico de productos.

**Del cliente se tiene:**

1. **Nombre:** arreglo de 100 caracteres.
2. **ID:** entero (int).
3. **Acumulado:** flotante (float) con el valor total de las compras realizadas. El acumulado se tiene con el fin de otorgarle al cliente puntos y para que obtenga tanto descuentos como puntos de fidelidad. En ocasiones, la tienda permite redimir puntos en la compra de productos.

**Del producto se tiene:**

1. **Código:** entero (int).
2. **Nombre:** arreglo de 100 caracteres.
3. **Color:** arreglo de 20 caracteres.
4. **Talla:** entero (int).
5. **Cantidad existente:** entero (int).
6. **Precio:** flotante (float).

Una Tienda maneja, también, un arreglo dinámico de productos, así como un archivo **productos.dat** con todos los productos de la tienda. Note que cuando se desea hacer la venta de un producto se debe consultar si la cantidad existente es superior a la que se desea vender. Cuando se vende, se debe decrementar, en la cantidad vendida, la cantidad existente del producto en el archivo **productos.dat**, así como en el arreglo dinámico de productos de la Tienda. Para facilitar la persistencia de las ventas de cada mes, se maneja un archivo binario llamado **ventas.dat**, donde se adiciona, al final de dicho archivo, la venta cuando ésta se realice.

Como desarrollador, lo han contratado a usted para que implemente un conjunto de funcionalidades listadas a continuación:

1. **(5 puntos)** Definir la estructura `Venta` y la estructura `Producto`.
2. **(10 puntos)** **Buscar un producto:** en el arreglo dinámico de la Tienda, dado su nombre. Retornar un apuntador al producto, el precio y la cantidad existente. Si el producto NO existe, debe retornar `NULL`.
3. **(10 puntos)** **Agregar un producto a la Tienda:** ingresan como parámetro los datos del producto (por valor) y la Tienda (por referencia). Se adiciona dicho producto al arreglo dinámico de productos de la Tienda. Si el producto ya existe, se debe informar al usuario y no se ingresa al arreglo dinámico.
4. **(5 puntos)** **Buscar un cliente en el archivo binario clientes.dat:** dado el nombre del cliente, retornar la posición en la que se encuentra. Si no lo encuentra, retorna `-1`.
5. **(25 puntos)** **Hacer una Venta:** dada una Tienda (por referencia), un arreglo de nombres de productos (arreglo de string), y el nombre del cliente (string), retornar el valor total de la venta. Note que se debe actualizar:
* El arreglo dinámico de productos de la Tienda (decrementar la cantidad existente de cada producto, si es posible, sino, informar por pantalla), adicionar una venta en el arreglo dinámico de ventas de la Tienda y, modificar el acumulado del cliente en el arreglo dinámico de clientes de la Tienda.
* El archivo de ventas (**ventas.dat**, adicionando la venta al final de dicho archivo), el de clientes (**clientes.dat**, actualizando el acumulado del cliente) y el de productos (**productos.dat**, decrementando la cantidad existente de cada producto, si es posible).
* Finalmente, se debe retornar el número de factura (entero). Suponga que tiene el método `int buscarProducto(string nomProducto)` que retorna la posición del producto en el archivo **productos.dat** o retorna **-1** si no lo encuentra.


6. **(10 puntos)** **Generar factura:** dado el número de factura y el arreglo dinámico de Ventas de una Tienda, generar un archivo **factura.txt** con los datos de factura, cliente y productos vendidos. Un ejemplo de una factura se muestra en el ejemplo:
```text
Factura No. 1520
Cliente: Ines Jimenez
ID: 28500404
Productos vendidos
1213  Tenis           Blanco    36
      $50000
2635  Sandalias       Azules    36
      $100000
3456  Zapato colegial Vinotinto 42
      $180000
1218  Tenis           Gris      28
      $70000

Valor total: $400000

```


7. **(15 puntos)** **Leer los productos de la Tienda desde el archivo productos.txt:** la primera línea corresponde al número de productos, la segunda es la palabra **Productos**. A partir de la tercera línea aparecen el nombre del producto y, en las siguientes, los datos de cada producto, separados por comas. El carácter (`%`) indica el fin de cada tipo de producto.
```text
5
Productos
Tenis
1218,Gris,28,70000,10
1213,Blanco,36,50000,5
%
Sandalias
2635,Azules,36,100000,8
%
Zapato colegial
3456,Vinotinto,42,180000,7
3457,Azul Oscuro,39,165000,4
%

```



**Restricciones:** no se pueden utilizar datos de tipo string (salvo los parámetros del punto 5). Los arreglos deben ser dinámicos y deben recorrerse con aritmética de apuntadores.