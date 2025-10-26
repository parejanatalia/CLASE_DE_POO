#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

// ===== FUNCIONES =====


char mi_tolower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A'); // Convierte mayúscula a minúscula usando ASCII ya que
    }
    return c;
}

// Compara el nombre en minusculas para operator== y busqueda
string a_minusculas(string s) {
    transform(s.begin(), s.end(), s.begin(), mi_tolower);
    return s;
}


void limpiar_buffer() {
    if (cin.fail()) {
        cin.clear();
    }

    cin.ignore(10000, '\n');
}

// ===== ESTRUCTURAS DE DATOS =====

struct Producto {
    string nombre;
    double precio = 0.0;
    int stock = 0;

    // Constructor (Punto 1)
    Producto(string nom = "", double prec = 0.0, int stk = 0)
        : nombre(nom), precio(prec), stock(stk) {}

    // Metodos const (Punto 2)
    bool esta_disponible() const { return stock > 0; }
    bool es_valido() const { return precio >= 0 && !nombre.empty(); }
};



struct Termino {
    double coeficiente = 0.0;
    int exponente = 0;
};

// Polinomio (Punto 4)
struct Polinomio {
    vector<Termino> lista_terminos;

    void poner_termino(double coef, int exp) {
        lista_terminos.push_back({coef, exp});
    }

    void imprimir() const {
        if (lista_terminos.empty()) { cout << "0" << endl; return; }
        bool es_primero = true;
        for (const auto& t : lista_terminos) {
            if (!es_primero) cout << " + ";
            cout << "(" << t.coeficiente << "x^" << t.exponente << ")";
            es_primero = false;
        }
        cout << endl;
    }
};




// Inventario (Punto 5)
struct Sistema_Inventario {
    vector<Producto> productos;
    void poner_producto(const Producto& p) {
        productos.push_back(p);
        cout << "Inventario: Agregado '" << p.nombre << "'" << endl;
    }
    // Devuelve un iterador para poder modificar el producto original
    vector<Producto>::iterator buscar_producto(const string& nombre);
};



// Fraccion (Punto 6)
struct Fraccion {
    int numerador = 0;
    int denominador = 1;

    Fraccion(int num, int den) {
        if (den == 0) { cerr << "Error: Denominador no puede ser 0. Usando 1." << endl; denominador = 1; }
        else { denominador = den; }
        numerador = num;
        simplificar();
    }

    void simplificar() {
        int divisor = gcd(abs(numerador), abs(denominador));
        if (divisor > 0) {
            numerador /= divisor;
            denominador /= divisor;
        }
        if (denominador < 0) { numerador *= -1; denominador *= -1; }
    }
    void imprimir() const { cout << numerador << "/" << denominador << endl; }
};

struct Contacto {
    string nombre;
    string telefono;
    string email = "No Registrado";
};

// Agenda (Punto 7)
struct Agenda {
    vector<Contacto> contactos;
    void poner(string nom, string tel, string mail = "No Registrado") {
        contactos.push_back({nom, tel, mail});
        cout << "Agenda: Agregado '" << nom << "'" << endl;
    }
    bool encontrar(const string& nombre, Contacto& datos_encontrados);

    void ver_todos() const {
        cout << "--- Contactos en la Agenda ---" << endl;
        if (contactos.empty()) { cout << "  (Vacía)" << endl; return; }
        for (const auto& c : contactos) {
            cout << "  - " << c.nombre << ", Tel: " << c.telefono << ", Email: " << c.email << endl;
        }
    }
};



// ===== IMPLEMENTACIÓN DE OPERADORES Y BUSCADORES =====

// Operador de igualdad (Punto 3)
bool operator==(const Producto& a, const Producto& b) {
    return a_minusculas(a.nombre) == a_minusculas(b.nombre);
}

// Operador de menor que (Punto 3)
bool operator<(const Producto& a, const Producto& b) {
    if (a.precio != b.precio) { return a.precio < b.precio; }
    return a.nombre < b.nombre;
}

vector<Producto>::iterator Sistema_Inventario::buscar_producto(const string& nombre) {
    Producto busqueda(nombre);
    return find(productos.begin(), productos.end(), busqueda);
}

bool Agenda::encontrar(const string& nombre, Contacto& datos_encontrados) {
    for (auto& c : contactos) {
        if (c.nombre == nombre) {
            datos_encontrados = c;
            return true;
        }
    }
    return false;
}

void ver_producto(const Producto& p) {
    cout << "  - " << (p.nombre.empty() ? "[Sin Nombre]" : p.nombre)
         << ", Precio: $" << p.precio
         << ", Stock: " << p.stock
         << " (Valido: " << (p.es_valido() ? "Si" : "No")
         << ", Disp: " << (p.esta_disponible() ? "Si" : "No") << ")"
         << endl;
}

void ver_inventario(const string& titulo, const vector<Producto>& lista) {
    cout << titulo << " (" << lista.size() << "):" << endl;
    if (lista.empty()) { cout << "  (Vacío)" << endl; return; }
    for (const auto& p : lista) { ver_producto(p); }
}

// ===== FUNCION PRINCIPAL=====

void mostrar_menu() {
    cout << "\n================ MENU DE PRUEBAS ================\n";
    cout << "1. Agregar Producto\n";
    cout << "2. Ver y Filtrar Inventario\n";
    cout << "3. Gestion de Inventario y Stock\n";
    cout << "4. Crear Polinomio\n";
    cout << "5. Simplificar Fraccion\n";
    cout << "6. Gestionar Agenda\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
}


int main() {
    Sistema_Inventario inventario;
    Agenda agenda;
    int opcion;

    inventario.poner_producto(Producto("Laptop", 230000, 5));
    inventario.poner_producto(Producto("Mouse", 350000, 10));
    agenda.poner("Juan Perez", "311-123-4567", "juan@mail.com");

    do {
        mostrar_menu();
        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Saliendo.\n";
            break;
        }
        limpiar_buffer();

        switch (opcion) {
            case 1: {
                cout << "\n--- 1. AGREGAR PRODUCTO ---\n";
                string nombre;
                double precio;
                int stock;

                cout << "Nombre del producto: "; getline(cin, nombre);
                cout << "Precio ($COP): "; cin >> precio;
                cout << "Stock inicial: "; cin >> stock;
                limpiar_buffer();

                Producto p_nuevo(nombre, precio, stock);

                if (p_nuevo.es_valido()) {
                    inventario.poner_producto(p_nuevo);
                } else {
                    cout << " Producto invalido.\n";
                }
                break;
            }
            case 2: {
                cout << "\n- 2. VER Y FILTRAR INVENTARIO ---\n";
                vector<Producto> lista_a_filtrar = inventario.productos;
                ver_inventario("Inventario completo", lista_a_filtrar);

                auto fin_basura = remove_if(lista_a_filtrar.begin(), lista_a_filtrar.end(),
                    [](const Producto& p) { return !p.es_valido() || !p.esta_disponible(); }
                );
                lista_a_filtrar.erase(fin_basura, lista_a_filtrar.end());
                ver_inventario("Inventario VALIDOS y DISPONIBLES", lista_a_filtrar);
                break;
            }
            case 3: {
                cout << "\n- 3. GESTION DE INVENTARIO -\n";

                vector<Producto> lista_ordenada = inventario.productos;
                sort(lista_ordenada.begin(), lista_ordenada.end());
                ver_inventario("Inventario ordenado", lista_ordenada);

                string nombre_busqueda;
                cout << "\nNombre del producto para MODIFICAR STOCK: "; getline(cin, nombre_busqueda);

                auto it = inventario.buscar_producto(nombre_busqueda);

                if (it != inventario.productos.end()) {
                    cout << "\n¡Producto '" << it->nombre << "' encontrado!\n";
                    cout << "Stock actual: " << it->stock << endl;

                    int cambio;
                    cout << "Cantidad a AGREGAR (+) o QUITAR (-): "; cin >> cambio;
                    limpiar_buffer();

                    it->stock += cambio;
                    cout << "\n--- STOCK ACTUALIZADO ---\n";
                    ver_producto(*it);
                } else {
                    cout << "Producto '" << nombre_busqueda << "' NO encontrado.\n";
                }
                break;
            }
            case 4: {
                cout << "\n--- 4. CREAR POLINOMIO ---\n";
                Polinomio poli;
                int num_terminos;
                cout << "Cuantos terminos tendra? "; cin >> num_terminos;
                limpiar_buffer();

                for (int i = 0; i < num_terminos; ++i) {
                    double coef;
                    int exp;
                    cout << "  Termino " << i+1 << ": Coeficiente: "; cin >> coef;
                    cout << "  Termino " << i+1 << ": Exponente: "; cin >> exp;
                    poli.poner_termino(coef, exp);
                    limpiar_buffer();
                }
                cout << "  Resultado P(x) = ";
                poli.imprimir();
                break;
            }
            case 5: {
                cout << "\n--- 5. SIMPLIFICAR FRACCION ---\n";
                int num, den;
                cout << "Numerador: "; cin >> num;
                cout << "Denominador: "; cin >> den;
                limpiar_buffer();

                Fraccion f(num, den);
                cout << "Fraccion simplificada: ";
                f.imprimir();
                break;
            }
            case 6: {
                cout << "\n--- 6. GESTIONAR AGENDA ---\n";
                string nombre, tel, email;
                int sub_opcion;

                cout << "1. Agregar contacto\n2. Buscar contacto\n3. Ver todos\nOpcion: ";
                cin >> sub_opcion;
                limpiar_buffer();

                if (sub_opcion == 1) {
                    cout << "  Nombre: "; getline(cin, nombre);
                    cout << "  Telefono: "; getline(cin, tel);
                    cout << "  Email (opcional): "; getline(cin, email);

                    if (email.empty()) {
                        agenda.poner(nombre, tel);
                    } else {
                        agenda.poner(nombre, tel, email);
                    }
                } else if (sub_opcion == 2) {
                    cout << "  Nombre del contacto a buscar: "; getline(cin, nombre);
                    Contacto contacto_buscado;
                    if (agenda.encontrar(nombre, contacto_buscado)) {
                        cout << "  ¡Contacto encontrado!\n";
                        cout << "  - Nombre: " << contacto_buscado.nombre << ", Tel: " << contacto_buscado.telefono << ", Email: " << contacto_buscado.email << endl;
                    } else {
                        cout << "  Contacto '" << nombre << "' no encontrado.\n";
                    }
                } else if (sub_opcion == 3) {
                    agenda.ver_todos();
                }
                break;
            }
            case 0: {
                cout << "Saliendo del programa\n";
                break;
            }
            default: {
                cout << "Opcion no valida. Intente de nuevo.\n";
                break;
            }
        }
    } while (opcion != 0);

    return 0;
}
