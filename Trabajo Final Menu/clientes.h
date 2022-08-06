#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

typedef struct{
    int id; /// campo único y autoincremental
    int nroCliente;
    char nombre[30];
    char apellido[30];
    char dni[10];
    char email[30];
    char domicilio[45];
    char movil[12];
    int eliminado; /// 0 si está activo - 1 si está eliminado
}stCliente;

//Prototipos de funciones de estructuras
stCliente cargaUnCliente();
void muestraUnCliente(stCliente a);

//Prototipos de funciones de archivos de clientes
void cargaArchivoClientes(char nombreArchivo []);//ALTA DE CLIENTES SIN VALIDACIONES
void muestraArchivoClientes(char nombreArchivo[]);//MUESTRA TODOS LOS CLIENTES (ALTA Y BAJA)
void muestraArchivoClientesEnAltaActiva(char nombreArchivo[], int c);//MUESTRA CLIENTES EN ALTA
void muestraArchivoClientesEnBaja(char nombreArchivo[], int c);//MUESTRA CLIENTES EN BAJA
int ultimoId(char nombreArchivo[]);

//Prototipos de funciones de arreglos
void muestraArregloClientes(int v, stCliente a[]);

//PROTOTIPADOS DE FUNCIONES MODIFICACION
int devuelvePosicionArchivo(char nombreArchivo[], char dni[]);//FUNCION QUE DEVUELVE POSICION DE UN REGISTRO EN UN ARCHIVO, LA USAMOS EN LAS FUNCIONES DE MODIFICACION
int devuelvePosicionArchivoPorNroCliente(char nombreArchivo[], int nroCliente);
void modificaStCliente(char nombreArchivo[], char dni[]);
void bajaCliente(char nombreArchivo[], int nroCliente);//FUNCION PARA DAR DE BAJA A UN CLIENTE

//PROTOTIPADOS DE FUNCIONES DE BUSQUEDA EN ARCHIVO DE CLIENTES
int buscaNroDeClienteEnArchivo(FILE *archi, int nroCliente);
int buscaDniEnArchivo(FILE *archi, char dni[]);
int buscaEmailEnArchivo(FILE *archi, char email[]);
int buscaMovilEnArchivo(FILE *archi, char movil[]);
void buscaUnClienteYLoMuestra(char nombreArchivo[], int nroCliente);

//PROTOTIPADOS DE FUNCIONES DE PASAJE DE ARCHIVO A ARREGLO
int pasaArchivoAArreglo(char nombreArchivo[], stCliente arrayC[], int dim);

//PROTOTIPADOS DE FUNCIONES DE BUSQUEDA Y ORDENAMIENTO
int buscaPosicionMenorsStClientePorApellido(stCliente arrayC[], int v, int pos);
int buscaPosicionMenorsStClientePoDni(stCliente arrayC[], int v, int pos);
int buscaPosicionMenorsStClientePoNroCliente(stCliente arrayC[], int v, int pos);
void ordenamientoApellido(stCliente array[], int v);
void ordenamientoDni(stCliente array[], int v);
void ordenamientoNroCliente(stCliente array[], int v);

//PROTOTIPADOS DE FUNCIONES DE INTERCAMBIO
void intercambioStCliente (stCliente *a, stCliente *b);

//PROTOTIPOS DE FUNCIONES DE VALIDACION
int validacionNomOApe (char nom[]);
void validacionNomOApeGeneral (char nom[]);
int validacionConAtoi (char dni[]);
void validacionGeneralDni (char dni[]);
int validacionTelIsdigit(char tel[]);
int validacionTelCantidadDigit (char tel[]);
void validacionTelGeneral(char tel[]);


#endif // CLIENTES_H_INCLUDED
