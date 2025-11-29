#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits> 

using namespace std;

// ayudita para limpiar el buffer de entrada
void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/* -------------------------------------------------
 * NIVEL 1: GETTERS Y SETTERS
 * ------------------------------------------------- */

// Ejercicio 1.1: Clase Vehículo
class Vehiculo {
private:
    string marca;
    string modelo;
    int anio;
    double velocidadMaxima;
public:
    // Constructor
    Vehiculo(string m, string mod, int a, double v) {
        setMarca(m); setModelo(mod);
        setAnio(a); setVelocidadMaxima(v);
    }
    
    // Getters
    string getMarca() const { return marca; }
    string getModelo() const { return modelo; }
    int getAnio() const { return anio; }
    double getVelocidadMaxima() const { return velocidadMaxima; }

    // Setters con validaciones
    void setMarca(string m) { marca = m; }
    void setModelo(string mod) { modelo = mod; }
    void setAnio(int a) {
       
        if (a > 1886) anio = a;
        else { cout << " Año inválido (< 1886), Se usará 1887\n"; anio = 1887; }
    }
    void setVelocidadMaxima(double v) {
       
        if (v > 0) velocidadMaxima = v;
        else { cout << "Velocidad debe ser positiva, Se usará 1 km/h.\n"; velocidadMaxima = 1; }
    }
    
   
    void acelerar(double incremento) {
        if (incremento > 0) velocidadMaxima += incremento;
    }
    
    virtual void mostrarInfo() const {
        cout << " VEHICULO : " << marca << " " << modelo << " (" << anio << ") | Vel : " << velocidadMaxima << " km/h\n";
    }
    virtual ~Vehiculo() = default;
};

// Ejercicio 1.2: Clase Producto
class Producto {
private:
    string codigo, nombre;
    double precio;
    int cantidad;

public:
  
    Producto(string cod, string n, double p, int c) : codigo(cod), nombre(n) {
        setPrecio(p); setCantidad(c);
    }
    
    
    string getCodigo() const { return codigo; }
    string getNombre() const { return nombre; }
    double getPrecio() const { return precio; }
    int getCantidad() const { return cantidad; }

    // Setters con validaciones
    void setPrecio(double p) { 
        
        precio = (p >= 0) ? p : 0; 
    }
    void setCantidad(int c) { 
        
        cantidad = (c >= 0) ? c : 0; 
    }

  
    double calcularValorTotal() const { return precio * cantidad; }

    
    void aplicarDescuento(double porcentaje) {
        if (porcentaje >= 0 && porcentaje <= 100) {
            double precioAnterior = precio;
            precio -= (precio * porcentaje / 100);

            cout << " Descuento aplicado(" << porcentaje <<"%).\n";
            cout << "Precio unitari anterior: $" << fixed << setprecision(2) << precioAnterior << "\n";
            cout << "  Nuevo precio unitario: $" << fixed << setprecision(2) << precio << "\n";
            cout << " NUEVO VALOR TOTAL INVENTARIO: $" << fixed << setprecision(2) << calcularValorTotal() << "\n";
        }
    }
    
    // Método mostrarInfo
    void mostrarInfo() const {
        cout << " PRODUCTO: " << nombre << " | Precio Unitario: $" << fixed << setprecision(2) << precio 
             << " | Cantidad: " << cantidad << " | Total Inventario: $" << calcularValorTotal() << "\n";
    }
};

/* -----------------------------------------
 * NIVEL 2: HERENCIA SIMPLE
 * --------------------------------------------- */

// Ejercicio 2.1: Clase Auto
class Auto : public Vehiculo {
private:
    int numeroPuertas;
    string tipoCombustible;

public:
    
    Auto(string m, string mod, int a, double v, int p, string t)
        : Vehiculo(m, mod, a, v), numeroPuertas(p), tipoCombustible(t) {}
    


    
    void mostrarInfo() const override {
        cout << " AUTO: "; Vehiculo::mostrarInfo();
        cout << " Puertas: " << numeroPuertas << ", Combustible: " << tipoCombustible << "\n";
    }
};

// Ejercicio 2.1: Clase Motocicleta
class Motocicleta : public Vehiculo {
private:
    bool tieneAleron;
    int cilindrada;
public:
    
    Motocicleta(string m, string mod, int a, double v, bool ala, int c)
        : Vehiculo(m, mod, a, v), tieneAleron(ala), cilindrada(c) {}


    void mostrarInfo() const override {
        cout << "MOTO: "; Vehiculo::mostrarInfo();
        cout << "  CC: " << cilindrada << ", Alerón: " << (tieneAleron ? "Sí" : "No") << "\n";
    }
};

// Ejercicio 2.2: Clase Base Empleado
class Empleado {
protected:
    string nombreCompleto;
    string numeroEmpleado;
    double salarioBase;
public:
    // Constructor
    Empleado(string nom, string num, double sal) : nombreCompleto(nom), numeroEmpleado(num), salarioBase(sal) {}
    virtual ~Empleado() = default;
    
    virtual void mostrarInfo() const = 0;
    virtual double calcularSalarioTotal() const = 0;
};

// Ejercicio 2.2: Clase EmpleadoTiempoCompleto
class EmpleadoTiempoCompleto : public Empleado {
private:
    string beneficios;
    double bono;
public:
   
    EmpleadoTiempoCompleto(string nom, string num, double sal, string ben, double b)
        : Empleado(nom, num, sal), beneficios(ben), bono(b) {}
    
  
    double calcularSalarioTotal() const override { return salarioBase + bono; }
    
    void mostrarInfo() const override {
        cout << "EMPLEADO tc : " << nombreCompleto << " (ID: " << numeroEmpleado << ") | Pago: $" << calcularSalarioTotal() << "\n";
    }
};

// Ejercicio 2.2: Clase EmpleadoPorHoras
class EmpleadoPorHoras : public Empleado {
private:
    int horasTrabajadas;
    double tarifaPorHora;

public:
    
    EmpleadoPorHoras(string nom, string num, int h, double t) : Empleado(nom, num, 0), horasTrabajadas(h), tarifaPorHora(t) {}

   
    double calcularSalarioTotal() const override { return horasTrabajadas * tarifaPorHora; }

  
    void mostrarInfo() const override {
        cout << " EMPLEADO por h: " << nombreCompleto << " (ID: " << numeroEmpleado << ") | Pago: $" << calcularSalarioTotal() << "\n";
    }
};

/*----------------------------------------------
 * NIVEL 3: Herencia multi nivel (Animales y Banco)
 *-------------------------------------------------- */

// Ejercicio 3.1: Clase Base Animal
class Animal {
protected:
    string nombre; int edad; double peso;
public:
    Animal(string n, int e, double p) : nombre(n), edad(e), peso(p) {}
    virtual ~Animal() = default;
    virtual void hacerSonido() const = 0; 
    virtual void mostrarInfo() const { cout << "Nombre " << nombre << " (" << edad << " años, " << peso << "kg)"; }
};


class Mamifero : public Animal {
protected: bool tieneColaMamifero;
public: Mamifero(string n, int e, double p, bool cola) : Animal(n, e, p), tieneColaMamifero(cola) {}
    void mostrarInfo() const override { Animal::mostrarInfo(); }
};


class Ave : public Animal {
protected: double envergaduraAlas;
public: Ave(string n, int e, double p, double enverg) : Animal(n, e, p), envergaduraAlas(enverg) {}
    void mostrarInfo() const override { Animal::mostrarInfo(); }
};


class Perro : public Mamifero {
public: Perro(string n, int e, double p) : Mamifero(n, e, p, true) {}
    void hacerSonido() const override { cout << " ---> ¡Guau guau!\n"; }
    void mostrarInfo() const override { Mamifero::mostrarInfo(); hacerSonido(); }
};

class Gato : public Mamifero {
public: Gato(string n, int e, double p) : Mamifero(n, e, p, true) {}
    void hacerSonido() const override { cout << " - > ¡ Miau  miau!"<<"\n"<<" O si le das comidita"<<"    wiwiwi uwawa uwa wa we"<<" XD\n"; }
    void mostrarInfo() const override { Mamifero::mostrarInfo(); hacerSonido(); }
};

class Loro : public Ave {
public: Loro(string n, int e, double p) : Ave(n, e, p, 0.5) {}
    void hacerSonido() const override { cout << " -> ¡Hola! ¡Soy un loro!\n"; }
    void mostrarInfo() const override { Ave::mostrarInfo(); hacerSonido(); }
};

class Aguila : public Ave {
public: Aguila(string n, int e, double p) : Ave(n, e, p, 2.1) {}
    void hacerSonido() const override { cout << " ---> ¡Kraaak!\n"; }
    void mostrarInfo() const override { Ave::mostrarInfo(); hacerSonido(); }
};

// Ejercicio 3.2: Clase Base Cuenta
class Cuenta {
protected:
    string numeroCuenta, propietario;
    double saldo;

public:
    Cuenta(string num, string prop, double s) : numeroCuenta(num), propietario(prop), saldo(s >= 0 ? s : 0) {}
    virtual void depositar(double monto) { if (monto > 0) saldo += monto; }
    virtual void retirar(double monto) { if (monto > 0 && monto <= saldo) saldo -= monto; }
    virtual void mostrarInfo() const {
        cout << " Cuenta " << numeroCuenta << " | Propietario: " << propietario << " | Saldo: $" << fixed << setprecision(2) << saldo << "\n";
    }
    virtual ~Cuenta() = default;
};

// Ejercicio 3.2: Clase CuentaAhorro 
class CuentaAhorro : public Cuenta {
private:
    double tasaInteres;
public:
    CuentaAhorro(string num, string prop, double s, double tasa)
        : Cuenta(num, prop, s), tasaInteres(tasa) {}

    double getTasaInteres() const { return tasaInteres; }

    void generarInteres() { 
        double interes = saldo * tasaInteres;
        saldo += interes;
        cout << " Interés (" << tasaInteres * 100 << "%) generado: $" << fixed << setprecision(2) << interes 
             << " | Nuevo Saldo: $" << fixed << setprecision(2) << saldo << "\n";
    }

    void mostrarInfo() const override {
        cout << " CTA AHORRO: " << numeroCuenta << " | Propietario: " << propietario << " | Saldo: $" << fixed << setprecision(2) << saldo 
             << " | Tasa: " << tasaInteres * 100 << "%\n";
    }
};

// Ejercicio 3.2: Clase CuentaCorriente
class CuentaCorriente : public Cuenta {
private:
    double limiteDescubierto;
public:
    CuentaCorriente(string num, string prop, double s, double limite) : Cuenta(num, prop, s), limiteDescubierto(limite >= 0 ? limite : 0) {}

    void solicitarDescubierto(double monto) {
        if (monto > 0 && monto <= limiteDescubierto) cout << " Solicitud de descubierto de $" << monto << " aprobada.\n";
        else cout << "Solicitud rechazada\n";
    }

    void retirar(double monto) override {
        if (monto > 0 && monto <= (saldo + limiteDescubierto)) {
            saldo -= monto;
            cout << " Retiro de $" << monto << " realizado.\n";
        } else {
            cout << " Retiro rechazado: excede saldo +descubierto.\n";
        }
    }
};








/* ---------------------------------------------
 * NIVEL 4: SISTEMA UNIVERSITARIO
 * ------------------------------------- */

// Ejercicio 4.1: Clase Curso (Composición)
class Curso {
private:
    string codigo, nombre, profesor;
    int creditos;
public:
    Curso(string cod, string n, int cred, string prof)
        : codigo(cod), nombre(n), creditos(cred), profesor(prof) {}

    string getNombre() const { return nombre; }
    void mostrarInfo() const { cout << " |_| - " << nombre << " (" << codigo << ")\n"; }
};

// Ejercicio 4.1: Clase Base Persona
class Persona {
protected:
    string nombre, cedula;
    int edad;
public:
    Persona(string n, int e, string c) : nombre(n), edad(e), cedula(c) {}
    virtual ~Persona() = default;
    virtual void mostrarInfo() const {
        cout << "  Nombre: " << nombre << ", Edad: " << edad << ", Cédula: " << cedula << "\n";
    }
};

// Ejercicio 4.1: Clase Estudiante
class Estudiante : public Persona {
private:
    string carrera;
    double promedio;
    int semestre;
    vector<Curso> cursos;
public:
    Estudiante(string n, int e, string c, string car, double prom, int sem) : Persona(n, e, c), carrera(car), promedio(prom), semestre(sem) {}

    void matricularCurso(const Curso& c) { cursos.push_back(c); }

    double calcularPromedioActual() const { return promedio; }

    void mostrarInfo() const override {
        cout << "\n ESTUDIANTE:\n";
        Persona::mostrarInfo();
        cout << " Carrera: " << carrera << ", Promedio: " << promedio << ", Semestre: " << semestre << "\n";
        cout << "  Cursos matriculados: " << cursos.size() << "\n";
    }
};

// Ejercicio 4.1: Clase Profesor
class Profesor : public Persona {
private:
    string especialidad;
    int aniosExperiencia;
    int numeroEstudiantes;
public:
    Profesor(string n, int e, string c, string esp, int anios, int num)  : Persona(n, e, c), especialidad(esp), aniosExperiencia(anios), numeroEstudiantes(num) {}
       
        
    // Método especial
    bool estaDisponible(int horaDelDia) const { return (horaDelDia >= 8 && horaDelDia <= 18); }

    void mostrarInfo() const override {
        cout << "\n PROFESOR:\n";
        Persona::mostrarInfo();
        cout << " Especialidad: " << especialidad << ", Experiencia: " << aniosExperiencia << " años\n";
    }
};

// Ejercicio 4.1: Clase Personal
class Personal : public Persona {
private:
    string puesto, departamento;
    double salario;
public:
    Personal(string n, int e, string c, string p, string d, double s)
        : Persona(n, e, c), puesto(p), departamento(d), salario(s >= 0 ? s : 0) {}

    // Método especial
    double calcularSalarioMensual() const { return salario; }
    
    void mostrarInfo() const override {
        cout << "\nPERSONAL ADMINISTRATIVO:\n";
        Persona::mostrarInfo();
        cout << "  Puesto: " << puesto << ", Departa: " << departamento << ", Salario: $" << fixed << setprecision(2) << salario << "\n";
    }
};

/* ---------------------------------------------
 * LA FUNCIÓN MAIN (Contiene las pruebas)
 * ------------------------------------- */

int main() {
    cout << "=== TALLER FINAL  POO ===\n";
    limpiarBuffer();

    // --- Nivel 1: Vehículo 
    cout << "\n[1] PRUEBA VEHÍCULO (NIVEL 1)\n";
    string marca, modelo; int anio; double velMax;
    cout << "Marca: "; getline(cin, marca);
    cout << "Modelo: "; getline(cin, modelo);
    cout << "Año (ej. 1990): "; cin >> anio;
    cout << "Vel. máxima (ej. 150): "; cin >> velMax;
    limpiarBuffer();

    Vehiculo v(marca, modelo, anio, velMax);
    v.mostrarInfo();
    v.acelerar(10);
    v.mostrarInfo();

    // --- Nivel 1.2: Producto --
    cout << "\n[1.2] PRUEBA DE PRODUCTO\n";
    Producto p("A001", "Smartphone", 500.00, 10);
    p.mostrarInfo();
    p.aplicarDescuento(15); 
    p.mostrarInfo();

    // --- Nivel 2: Herencia y Empleados  ---
    cout << "\n[2] PRUEBA DE HERENCIA SIMPLE\n";
    Auto miAuto("Toyota", "Corolla", 2022, 180, 4, "Gasolina");
    miAuto.mostrarInfo();

    EmpleadoTiempoCompleto empTC("Ana Lopez", "E100", 2000, "Seguro Total", 500);
    empTC.mostrarInfo();

    EmpleadoPorHoras empPH("Carlos Pérez", "E101", 160, 15);
    empPH.mostrarInfo();

    // --- Nivel 3: Animales (--
    cout << "\n[3.1] PRUEBA DE JERARQUÍA ANIMAL\n";
    Perro perro("Rex", 5, 20); perro.mostrarInfo();
    Gato gato("Luna", 3, 5); gato.mostrarInfo();
    Aguila aguila("Halcón", 4, 6); aguila.mostrarInfo();

    // --- Nivel 3.2: Banco 
    cout << "\n[3.2] PRUEBA DE CUENTA BANCARIA\n";
    
  
    CuentaAhorro ahorros("123456", "Carlos Ahorrador", 5000, 0.02);
    ahorros.mostrarInfo();
    ahorros.depositar(1000);
    ahorros.mostrarInfo();
    ahorros.generarInteres();
    ahorros.mostrarInfo();
    
    
    CuentaCorriente cta("CTA-99", "Juan Pérez", 1000, 200);
    cta.mostrarInfo();
    cta.solicitarDescubierto(100);
    cta.retirar(1150);
    cta.mostrarInfo();

    // --- Nivel 4: Universidad 
    cout << "\n[4] PRUEBA DE SISTEMA UNIVERSITARIO COMPLETO\n";
    Estudiante est("Maria", 20, "1234", "Sistemas", 4.5, 3);
    est.matricularCurso(Curso("POO101", "POO Avanzada", 4, "Dr. Strange"));
    est.mostrarInfo();

    Profesor prof("Dr. Strange", 45, "DOC-1", "Magia", 15, 50);
    prof.mostrarInfo();
    cout << " ¿Disponible a las 10:00? " << (prof.estaDisponible(10) ? "Sí" : "No") << "\n";

    Personal admin("Luis Jefe", 30, "ADM-001", "Secretario", "Finanzas", 1500.00);
    admin.mostrarInfo();
    cout << " Salario Mensual: $" << admin.calcularSalarioMensual() << "\n";

    return 0;
}










