#ifndef CONSUMOS_H_INCLUDED
#define CONSUMOS_H_INCLUDED

typedef struct{
    int id; /// campo único y autoincremental
    int idCliente;
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a … dependiendo del mes
    int datosConsumidos; /// expresados en mb.
    float datosCosumidosEnPesos; //1MB = $10
    int baja; /// 0 si está activo - 1 si está eliminado
}stConsumos;

//FUNCION PARA CARGAR ARCHIVO RANDOM
void cargaArchivoConsumosRandom(char nombreArchivo[]);

//PROTOTIPOS DE FUNCIONES DE ARCHIVO DE CONSUMOS
void mostrarUnConsumo(stConsumos c);
void mostrarArchivoConsumos(char nombreArchivo[]);
int ultimoIdConsumos(char nombreArchivo[]);
void cargarArchivoDeConsumos(char nombreArchivo[], int nroCliente);
void buscarConsumoPorFechaYLoMuestra(char nombreArchivo[], int nroCliente);
int devuelvePosicionArchivoDeConsumosPorNroCliente(char nombreArchivo[], int nroCliente);
int buscaConsumoPorFecha(FILE *archi, int anio, int mes, int dia);
int buscaIdClienteEnArchivoConsumos(FILE *archi, int nroCliente);
void buscarConsumoPorNroDeCliente(char nombreArchivo[], int nroCliente);
int devuelvePosicionArchivoDeConsumosPorFecha(char nombreArchivo[], int anio, int mes, int dia);
void darDeBajaConsumoPorFecha(char nombreArchivo[], int nroCliente);

//PROTOTIPOS DE FUNCIONES PARA ORDENAR LISTADO DE CONSUMOS
int pasaArchivoAArregloConsumos(char nombreArchivo[], stConsumos c[], int dim);
void muestraArregloConsumos(stConsumos c[], int v);
void muestraConsumosPorNroCliente(stConsumos c[], int v, int nroCliente);
void ordenaConsumosPorSeleccionPorMes(stConsumos c[], int v);
int buscaPosMenorPorMes(stConsumos c[], int v, int pos);
void intercambioStConsumos(stConsumos *a, stConsumos *b);

int validaFechaAnio(int anio);
int validaFechaMes(int mes);
int validaFechaDia(int dia, int mes);


#endif // CONSUMOS_H_INCLUDED
