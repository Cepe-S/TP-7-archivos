#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pila.c"

void clrscr() {
    system("@cls||clear");
}


//---------Trabajo Práctico N° 7: Archivos---------//
// En cada ejercicio, el archivo debe abrirse y cerrarse dentro de cada función. La variable de tipo FILE * 
// debe ser local a la función. Se puede pasar por parámetro una variable de tipo char [30] con el nombre 
// del archivo, ejemplos: “archivo.bin” o "alumnos.dat", o trabajar con una constante declarada.

void fadd(char e[30]) {
    FILE *file = fopen("archivo.bin", "ab");
    if (file == NULL) {
        printf("Error");
    }
    fprintf(file, "%s\n", e);
    fclose(file);
}

//1. Hacer una función que agregue un elemento al final de un archivo.
int Ejercicio1() {
    char e[30];
    printf("Introduzca el texto que desee agregar: ");
    scanf("%s", &e);
    fadd(e);
}

//2. Hacer una función que muestre por pantalla el contenido de un archivo.
int Ejercicio2() {
    
}

//3. Hacer una función que retorne la cantidad de registros que contiene un archivo.
int Ejercicio3() {
    
}

//---------Utilizando la estructura:---------//

typedef struct { 
    int legajo;
    char nombreYapellido [30];
    int edad;
    int anio; 
//año que cursa, recordar que no podemos utilizar la ñ para definir variables
} stAlumno;

void show_student(stAlumno a) {
    printf("Legajo: %d\n", a.legajo);
    printf("Nombre: %s\n", a.nombreYapellido);
    printf("Edad: %d\n", a.edad);
    printf("Anio: %d\n\n", a.anio);
}

void get_data() {
    FILE *file = fopen("alumnos.dat", "rb");
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int len = size / sizeof(stAlumno);
    printf("||%d||\n", len);
    stAlumno a[len];
    fread(&a, len, sizeof(stAlumno), file);
    for (int i = 0; i < len; i++) {
        show_student(a[i]);
    }
    fclose(file);
}

//4. Crear una función que muestre por pantalla los registros de un archivo de alumnos. Modularizar.
int Ejercicio4() {
    get_data();
}

// loads from stdin a stAlumno struct and adds returns it
stAlumno get_student() {
    stAlumno a;
    printf("Legajo: "); fflush(stdin);
    scanf("%d", &a.legajo);
    printf("Nombre: "); fflush(stdin);
    scanf("%s", &a.nombreYapellido); 
    printf("Edad: "); fflush(stdin);
    scanf("%d", &a.edad);
    printf("Anio: "); fflush(stdin);
    scanf("%d", &a.anio);
    return a;
}

// adds a stAlumno struct to the file "alumnos.dat"
void add_student(stAlumno a) {
    stAlumno b = a;
    FILE *file = fopen("alumnos.dat", "ab");
    fwrite(&b, sizeof(stAlumno), 1, file);
    fclose(file);
}

//5. Crear una función que permita agregar de a un elemento al final del archivo. O sea, se debe abrir el archivo, 
//   se piden los datos (se llena una variable de tipo struct alumno), se escribe en el archivo y se cierra.
int Ejercicio5() {
    add_student(get_student());
}

// prints the data from the file "alumnos.dat" in a human readable format
void print_file() {
    FILE *file = fopen("alumnos.dat", "rb");
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int len = size / sizeof(stAlumno);
    stAlumno a[len];
    fread(&a, sizeof(stAlumno), len, file);
    for (int i = 0; i < len; i++) {
        show_student(a[i]);
    }
    fclose(file);
}


void get_adults(Pila *p) {
    FILE *file = fopen("alumnos.dat", "rb");
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int len = size / sizeof(stAlumno);
    printf("||%d||\n", len);
    stAlumno a[len];
    fread(&a, sizeof(stAlumno), len, file);
    for (int i = 0; i < len; i++) {
        if (a[i].edad >= 18) {
            apilar(p, a[i].legajo);
        }
    }
    fclose(file);
}

//6. Crear una función que pase a una pila los números de legajo de los alumnos mayores de edad.
int Ejercicio6() {
    Pila pila; inicpila(&pila);
    get_adults(&pila);
    get_data();
    mostrar(&pila);
}

// pass the data from the file "alumnos.dat" to a stack
void get_data_to_stack(Pila *p) {
    FILE *file = fopen("alumnos.dat", "rb");
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int len = size / sizeof(stAlumno);
    printf("||%d||\n", len);
    stAlumno a[len];
    fread(&a, sizeof(stAlumno), len, file);
    for (int i = 0; i < len; i++) {
        apilar(p, a[i].legajo);
    }
    fclose(file);
}

//7. Crear una función que pase a una pila los números de legajo de los alumnos mayores de edad. 
int Ejercicio7() {
    Pila pila; inicpila(&pila);
    get_data_to_stack(&pila);
    mostrar(&pila);
}

// returns the amount of students that have an age greater than a parameter
int get_adults_count(int age) {
    FILE *file = fopen("alumnos.dat", "rb");
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int len = size / sizeof(stAlumno);
    stAlumno a[len];
    fread(&a, sizeof(stAlumno), len, file);
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (a[i].edad >= age) {
            count++;
        }
    }
    fclose(file);
    return count;
}

//8. Dado un archivo de alumnos, hacer una función que cuente la cantidad de alumnos mayores a edad específica que se envía por parámetro.
int Ejercicio8() {
    int age = 18;
    printf("Los adultos mayores a %d anos son: %d\n", age, get_adults_count(age));
}

// prints the data of a student with a legacy passed from parameter
void print_student_with_legacy(int legajo) {
    FILE *file = fopen("alumnos.dat", "rb");
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int len = size / sizeof(stAlumno);
    stAlumno a[len];
    fread(&a, sizeof(stAlumno), len, file);
    for (int i = 0; i < len; i++) {
        if (a[i].legajo == legajo) {
            show_student(a[i]);
        }
    }
    fclose(file);
}

// shows the students that have a age between two parameters from the file "alumnos.dat"
void get_students_with_age(int age1, int age2) {
    FILE *file = fopen("alumnos.dat", "rb");
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int len = size / sizeof(stAlumno);
    stAlumno a[len];
    fread(&a, sizeof(stAlumno), len, file);
    for (int i = 0; i < len; i++) {
        if (a[i].edad >= age1 && a[i].edad <= age2) {
            show_student(a[i]);
        }
    }
    fclose(file);
}

//9. Dado un archivo de alumnos, mostrar por pantalla el nombre de todos los alumnos entre un rango de edades específico (por ejemplo, entre 17 y 25 años). Dicho rango debe recibirse por parámetro. Modularizar 
int Ejercicio9() {
    get_students_with_age(23, 40);
}

// gets the legacy of the oldest student and prints the data of the student with that legacy
int print_oldest_student() {
    int oldest = 0;
    int legacy = 0;
    FILE *file = fopen("alumnos.dat", "rb");
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int len = size / sizeof(stAlumno);
    stAlumno a[len];
    fread(&a, sizeof(stAlumno), len, file);
    for (int i = 0; i < len; i++) {
        if (a[i].edad > oldest) {
            oldest = a[i].edad;
            legacy = a[i].legajo;
        }
    }
    print_student_with_legacy(legacy);
    fclose(file);
}



//11. Crear una función que retorne la cantidad de alumnos que cursan un determinado año. El año buscado se pasa por parámetro.
int Ejercicio10() {
    print_oldest_student();
}

// returns the amount of students with a determinated anio passed by parameter
int get_students_with_year(int anio) {
    FILE *file = fopen("alumnos.dat", "rb");
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int len = size / sizeof(stAlumno);
    stAlumno a[len];
    fread(&a, sizeof(stAlumno), len, file);
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (a[i].anio == anio) {
            count++;
        }
    }
    fclose(file);
    return count;
}

//11. Crear una función que retorne la cantidad de alumnos que cursan un determinado año. El año buscado se pasa por parámetro. 
int Ejercicio11() {
    int anio = 2019;
    printf("Los alumnos que cursan el año %d son: %d\n", anio, get_students_with_year(anio));
}

// adds an array of students to a file
void add_students_to_file(stAlumno a[], int len) {
    FILE *file = fopen("alumnos.dat", "ab");
    fwrite(&a, sizeof(stAlumno), len, file);
    fclose(file);
}

// adds to an array the students that are from a determinated year from the file "alumnos.dat"
int get_students_with_year_from_file(int anio, stAlumno *a) {
    FILE *file = fopen("alumnos.dat", "rb");
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int len_file = size / sizeof(stAlumno);
    stAlumno a_file[len_file];
    fread(&a_file, sizeof(stAlumno), len_file, file);
    int len = 0;
    for (int i = 0; i < len_file; i++) {
        if (a_file[i].anio == anio) {
            a[len] = a_file[i];
            len++;
        }
    }
    fclose(file);
    return len;
}	

//12. Crear una función que reciba como parámetro un arreglo de tipo alumno y lo copie en el archivo. Asimismo, realice otra función que pase los elementos del archivo a un arreglo de alumnos, filtrando los estudiantes de un año en particular.
int Ejercicio12() {
    stAlumno *a;
    int len = get_students_with_year_from_file(2019, a);
    for (int i = 0; i < len; i++) {
        show_student(a[i]);
    }
}

// returns the amount of registers of a file using fseek and ftell
int get_file_len(char file_name[]) {
    FILE *file = fopen(file_name, "rb");
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fclose(file);
    return size / sizeof(stAlumno);
}

// 13. Crear una función que retorne la cantidad de registros que tiene el archivo. Usar fseek y ftell. Puede pensar la función para uso genérico, que sirva para averiguar la cantidad de registros de cualquier archivo.
int Ejercicio13() {
    int len = get_file_len("alumnos.dat");
}

// shows the content of a register of a file with parameters 0-9 (the register)
void show_register(char file_name[], int reg) {
    FILE *file = fopen(file_name, "rb");
    fseek(file, reg * sizeof(stAlumno), SEEK_SET);
    stAlumno a;
    fread(&a, sizeof(stAlumno), 1, file);
    show_student(a);
    fclose(file);
}

//14. Dado un archivo de alumnos, que tenga al menos 10 registros, hacer una función que muestre el contenido de un registro, cuyo número (entre 0 y 9) se pase por parámetro. Controlar no sobrepasar los límites del archivo.
int Ejercicio14() {
    show_register("alumnos.dat", 1);
}

// overwrites the content of a register of a file with parameters 0-9 (the register)
void overwrite_register(char file_name[], int reg, stAlumno a) {
    FILE *file = fopen(file_name, "rb+");
    fseek(file, reg * sizeof(stAlumno), SEEK_SET);
    fwrite(&a, sizeof(stAlumno), 1, file);
    fclose(file);
}

//15. Realice una (o varias) funciones que permitan modificar un registro existente en el archivo de alumnos. La misma debe permitir modificar uno o todos los campos de la estructura y sobreescribir el registro existente en el archivo.
int Ejercicio15() {
    stAlumno a;
    a.legajo = 1;
    a.edad = 20;
    a.anio = 2019;
    strcpy(a.nombreYapellido, "Juan Perez");
    overwrite_register("alumnos.dat", 2, a);
}

// inverts the content of a file
void invert_file(char file_name[]) {
    FILE *file = fopen(file_name, "rb+");
    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int len = size / sizeof(stAlumno);
    for (int i = 0; i < len / 2; i++) {
        stAlumno a, b;
        fread(&a, sizeof(stAlumno), 1, file);
        fseek(file, (len-i) * sizeof(stAlumno), SEEK_SET);
        fread(&b, sizeof(stAlumno), 1, file);
        fwrite(&a, sizeof(stAlumno), 1, file);
        fseek(file, i * sizeof(stAlumno), SEEK_SET);
        fwrite(&b, sizeof(stAlumno), 1, file);
    }
    fclose(file);
}

//16. Dado un archivo de alumnos, hacer una función que invierta los elementos del mismo. No se puede usar otro archivo auxiliar ni un arreglo auxiliar. Debe trabajar sobre el archivo. Puede utilizar variables de tipo alumno auxiliares.
int Ejercicio16() {
    get_data();
    invert_file("alumnos.dat");
    printf("\n\n---------------\n\n");
    get_data();
}
//17. Hacer una función principal que pruebe el funcionamiento de todos los incisos anteriores, con un menú de opciones para poder ejecutar todas las funciones requeridas. Tengan presente la correcta declaración y el ámbito de variables.
int Ejercicio17() {
    // main
}
 
int main() {
    int s = 0;
    int a;
    while(1 > 0) {
        clrscr();        
        printf("\n--------------Trabajo Práctico N° 7: Archivos--------------\n\n[1] Ejercicio 1\n[2] Ejercicio 2\n[3] Ejercicio 3\n[4] Ejercicio 4\n[5] Ejercicio 5\n[6] Ejercicio 6\n[7] Ejercicio 7\n[8] Ejercicio 8\n[9] Ejercicio 9\n[10] Ejercicio 10\n[11] Ejercicio 11\n[12] Ejercicio 12\n[13] Ejercicio 13\n[14] Ejercicio 14\n[15] Ejercicio 15\n[16] Ejercicio 16\n[17] Ejercicio 17\n");
        printf("\nSeleccione un ejercicio: ");
        scanf("%d", &s);
        printf("\n-------------\n\n");
        switch (s) {
            case 1:
                Ejercicio1();
                break;
            case 2:
                Ejercicio2();
                break;
            case 3:
                Ejercicio3();
                break;
            case 4:
                Ejercicio4();
                break;
            case 5:
                Ejercicio5();
                break;
            case 6:
                Ejercicio6();
                break;
            case 7:
                Ejercicio7();
                break;
            case 8:
                Ejercicio8();
                break;
            case 9:
                Ejercicio9();
                break;
            case 10:
                Ejercicio10();
                break;
            case 11:
                Ejercicio11();
                break;
            case 12:
                Ejercicio12();
                break;
            case 13:
                Ejercicio13();
                break;
            case 14:
                Ejercicio14();
                break;
            case 15:
                Ejercicio15();
                break;
            case 16:
                Ejercicio16();
                break;
            case 17:
                Ejercicio17();
                break;
            default:
                printf("ejercicio fuera de rango");
                break;
        }
        printf("\n----------\n\n");
        printf("Introduzca 1 para continuar o 0 para cerrar: ");
        scanf("%d", &a);
        if (a == 0) {
            break;
        }
        printf("\n----------\n\n");
    }
    return 0;
}