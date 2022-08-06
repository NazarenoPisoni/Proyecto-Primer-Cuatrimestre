#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "clientes.h"
#include "consumos.h"
#include "menu.h"

#define ARCHI_CLIENTES "clientes.dat"
#define ARCHI_CONSUMOS "consumos.dat"

void mostrarUnConsumo(stConsumos c)
{
    printf("\n ID CONSUMO:.....................: %d", c.id);
    printf("\n ID CLIENTE:.....................: %d", c.idCliente);
    printf("\n ANIO............................: %d", c.anio);
    printf("\n MES.............................: %d", c.mes);
    printf("\n DIA.............................: %d", c.dia);
    printf("\n DATOS CONSUMIDOS................: %d", c.datosConsumidos);
    printf("\n DATOS CONSUMIDOS EN PESOS.......: $%.2f", c.datosCosumidosEnPesos);
    printf("\n BAJA (0=ACTIV0/ 1=BAJA).........: %d", c.baja);
    printf("\n---------------------------------------------------");
}

//FUNCION PARA MOSTRAR TODOS LOS REGISTROS EN EL ARCHIVO DE CONSUMOS
void mostrarArchivoConsumos(char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    stConsumos c;
    if(archi)
    {


        while(fread(&c, sizeof(stConsumos), 1, archi)>0)
        {
            mostrarUnConsumo(c);
        }
        fclose(archi);
    }
}


//FUNCION PARA CARGA DE UN CONSUMO
void cargarArchivoDeConsumos(char nombreArchivo[], int nroCliente)
{
    FILE *archiClientes = fopen(ARCHI_CLIENTES, "rb");//CREO UN PUNTERO DE ARCHICLIENTES PORQUE NECESITO VER SI EL NRO DE CLIENTE PEDIDO POR PARAMETRO EXISTE
    FILE *archiConsumos = fopen(nombreArchivo, "ab");
    stCliente a;
    stConsumos c;
    int acumuladorDeDatosConsumidos=0;
    float acumuladorDeDatosConsumidosEnPesos=0;
    int existeNroCliente=-1;
    int opcion=0;
    char opcionParaCargarCliente=0;
    int pos;
    int static id;
    int auxFecha=0;
    int auxFechaMes=0;
    int auxFechaDia=0;
    int anioCorrecto=0;
    int mesCorrecto=0;
    int diaCorrecto=0;
    id=ultimoIdConsumos(nombreArchivo);

    if(archiClientes)
    {
        existeNroCliente = buscaNroDeClienteEnArchivo(archiClientes, nroCliente);
        if(existeNroCliente==1) //SI EL CLIENTE EXISTE NOS POSICIONAMOS EN LA POSICION QUE ESTA EL REGISTRO Y LO LEEMOS ASI PODEMOS RELACIONAR LAS ESTRUCTURAS
        {
            pos=devuelvePosicionArchivoPorNroCliente(ARCHI_CLIENTES, nroCliente);
            fseek(archiClientes, sizeof(stCliente)*(pos-1), 0);
            fread(&a, sizeof(stCliente), 1, archiClientes);
            c.idCliente = a.nroCliente;//EN ESTA PARTE RELACIONAMOS EL NUMERO DE CLIENTES DE LA ESTRUCTURA CLIENTE CON EL IDCLIENTE DE LA ESTRUCTURA CONSUMOS

        }
        else
        {
            printf("\nEL CLIENTE NO EXISTE DESEA DARSE DE ALTA? s/n: ");
            fflush(stdin);
            scanf("%c", &opcionParaCargarCliente);
            if(opcionParaCargarCliente==115)
            {
                cargaArchivoClientes(ARCHI_CLIENTES);//SI EL CLIENTE NO EXISTE Y PRESIONA 's' LO MANDAMOS A DARSE DE ALTA

            }

        }
        fclose(archiClientes);
    }



    if(archiConsumos)
    {
        do
        {
            system("cls");
            id++;

            do{
                printf("\nINGRESE ANIO: ");
                fflush(stdin);
                scanf("%d", &auxFecha);
                anioCorrecto=validaFechaAnio(auxFecha);
                if(anioCorrecto==1){
                    c.anio=auxFecha;
                }else{
                    printf("\nERROR - ANIO NO VALIDO");
                    getch();
                }
            }while(anioCorrecto!=1);





            do{
                printf("\nINGRESE MES: ");
                fflush(stdin);
                scanf("%d", &auxFechaMes);
                mesCorrecto=validaFechaMes(auxFechaMes);
                if(mesCorrecto==1){
                    c.mes=auxFechaMes;
                }else{
                    printf("\nERROR - MES NO VALIDO");
                    getch();
                }
            }while(mesCorrecto!=1);



            do{
                printf("\nINGRESE DIA: ");
                fflush(stdin);
                scanf("%d", &auxFechaDia);
                diaCorrecto=validaFechaDia(auxFechaDia, auxFechaMes);
                if(diaCorrecto==1){
                    c.dia=auxFechaDia;
                }else{
                    printf("\nERROR - DIA NO VALIDO");
                    getch();
                }
            }while(diaCorrecto!=1);



            do
            {
                system("cls");
                printf("\nINGRESE CANTIDAD DE MB QUE DESEA: ");
                fflush(stdin);
                scanf("%d", &c.datosConsumidos);
            }
            while(c.datosConsumidos<1);

            if(id == c.id)
            {
                acumuladorDeDatosConsumidos = acumuladorDeDatosConsumidos + c.datosConsumidos;
                c.datosConsumidos = acumuladorDeDatosConsumidos;

                c.datosCosumidosEnPesos=(float)(c.datosConsumidos*10);

                acumuladorDeDatosConsumidosEnPesos = acumuladorDeDatosConsumidosEnPesos + c.datosCosumidosEnPesos;
                c.datosCosumidosEnPesos = acumuladorDeDatosConsumidosEnPesos;
            }
            else
            {
                c.datosCosumidosEnPesos=(float)(c.datosConsumidos*10);
            }

            c.id=id;
            c.baja=0;
            fseek(archiConsumos, 0, SEEK_END);
            fwrite(&c, sizeof(stConsumos), 1, archiConsumos);
            printf("\nCONSUMO CARGADO CON EXITO...\n");

            acumuladorDeDatosConsumidosEnPesos = acumuladorDeDatosConsumidosEnPesos - c.datosCosumidosEnPesos;

            if(c.anio==2022 && c.mes==6 && c.dia==21)
            {
                id--;

            }


            printf("\nESC PARA SALIR / CUALQUIER TECLA PARA CARGAR OTRO CONSUMO...\n");
            opcion=getch();


        }
        while(opcion!=27);
        fclose(archiConsumos);
    }
}

int ultimoIdConsumos(char nombreArchivo[])
{
    int id=0;
    stConsumos c;
    FILE *archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        fseek(archi, -1*(sizeof(stCliente)), SEEK_END);
        if(fread(&c, sizeof(stConsumos), 1, archi)>0)
        {
            id= c.id;
        }
        fclose(archi);
    }
    return id;
}

//FUNCIONES PARA MOSTRAR CONSUMOS
void buscarConsumoPorFechaYLoMuestra(char nombreArchivo[], int nroCliente)
{
    int existeNroCliente=-1;
    int existeFecha=-1;
    int pos;
    stConsumos c;
    int anio, mes, dia;

    printf("\nINGRESE ANIO: ");
    fflush(stdin);
    scanf("%d", &anio);

    printf("\nINGRESE MES: ");
    fflush(stdin);
    scanf("%d", &mes);

    printf("\nINGRESE DIA: ");
    fflush(stdin);
    scanf("%d", &dia);

    FILE *archiConsumos = fopen(nombreArchivo, "rb");


    if(archiConsumos)
    {

        existeNroCliente=buscaIdClienteEnArchivoConsumos(archiConsumos, nroCliente);
        if(existeNroCliente==1)
        {
            pos=devuelvePosicionArchivoDeConsumosPorNroCliente(nombreArchivo, nroCliente);
            fseek(archiConsumos, sizeof(stConsumos)*(pos-1), 0);
            fread(&c, sizeof(stConsumos), 1, archiConsumos);
            existeFecha=buscaConsumoPorFecha(archiConsumos, anio, mes, dia);
            if(existeFecha==1)
            {
                while(fread(&c, sizeof(stConsumos), 1, archiConsumos)>0)
                {
                    if(nroCliente==c.idCliente && anio==c.anio && mes==c.mes && dia==c.dia)
                    {
                        mostrarUnConsumo(c);
                    }
                }

            }
            else
            {
                printf("\nERROR - NO HAY CONSUMOS EN ESA FECHA\n");
                getch();
            }
        }
        else
        {
            printf("\nERROR - EL NUMERO DE CLIENTE NO EXISTE\n");
            getch();
        }



        fclose(archiConsumos);
    }
}

int devuelvePosicionArchivoDeConsumosPorNroCliente(char nombreArchivo[], int nroCliente)
{
    stConsumos c;
    int flag=0;
    int i=0;
    FILE *archi = fopen(ARCHI_CONSUMOS, "rb");
    if(archi)
    {
        while(flag==0 && fread(&c, sizeof(stConsumos), 1, archi)>0)
        {
            if(nroCliente == c.idCliente)
            {
                flag=1;
            }
            i++;
        }
        fclose(archi);
    }
    return i;
}

int devuelvePosicionArchivoDeConsumosPorFecha(char nombreArchivo[], int anio, int mes, int dia)
{
    stConsumos c;
    int flag=0;
    int i=0;
    FILE *archi = fopen(ARCHI_CONSUMOS, "rb");
    if(archi)
    {
        while(flag==0 && fread(&c, sizeof(stConsumos), 1, archi)>0)
        {
            if(anio==c.anio && mes==c.mes && dia==c.dia)
            {
                flag=1;
            }
            i++;
        }
        fclose(archi);
    }
    return i;
}

int buscaConsumoPorFecha(FILE *archi, int anio, int mes, int dia)
{
    stConsumos c;
    int flag=0;
    rewind(archi);
    if(archi)
    {
        while(flag==0 && fread(&c, sizeof(stConsumos), 1, archi)>0)
        {
            if(anio == c.anio && mes == c.mes && dia == c.dia)
            {
                flag=1;
            }
        }
    }

    return flag;
}

int buscaIdClienteEnArchivoConsumos(FILE *archi, int nroCliente)
{
    stConsumos c;
    int flag=0;
    if(archi)
    {
        while(flag==0 && fread(&c, sizeof(stConsumos), 1, archi)>0)
        {
            if(nroCliente == c.idCliente)
            {
                flag=1;
            }
        }
    }
    return flag;
}

void buscarConsumoPorNroDeCliente(char nombreArchivo[], int nroCliente)
{

    stConsumos c;
    int existeNroCliente=-1;
    FILE *archi = fopen(nombreArchivo, "rb");

    if(archi)
    {
        existeNroCliente=buscaIdClienteEnArchivoConsumos(archi, nroCliente);
        if(existeNroCliente==1)
        {
            while(fread(&c, sizeof(stConsumos), 1, archi) > 0)
            {
                if(nroCliente == c.idCliente)
                {
                    mostrarUnConsumo(c);

                }
            }
        }
        else
        {
            printf("\nERROR - NO HAY CONSUMOS CON ESE CLIENTE\n");
        }

        fclose(archi);
    }
}

void cargaArchivoConsumosRandom(char nombreArchivo[])
{
    stConsumos c;
    int i;
    int static id;
    id=ultimoIdConsumos(nombreArchivo);
    srand(time(NULL));
    FILE *archi = fopen(nombreArchivo, "ab");


    if(archi)
    {
        for(i=1; i<=1001; i++)
        {
            id++;
            c.id=id;
            c.idCliente = rand() % (10152-10101)+10101;
            c.anio=2022;
            c.mes = rand() % (6-1)+1;
            if(c.mes == 1 || c.mes == 3 || c.mes == 5)
            {
                c.dia = rand()%(31-1)+1;
            }
            else if(c.mes == 4)
            {
                c.dia = rand()%(30-1)+1;
            }
            else if(c.mes == 2)
            {
                c.dia = rand()%(28-1)+1;
            }
            else
            {
                c.mes = rand()%(21-1)+1;
            }

            c.datosConsumidos = rand()%(100-1)+1;
            c.datosCosumidosEnPesos = (float) c.datosConsumidos*10;
            c.baja=0;
            fwrite(&c, sizeof(stConsumos), 1, archi);

        }
        fclose(archi);
    }

}

int validaFechaAnio(int anio){
    int flag=0;
    if(anio==2022){
        flag=1;
    }
    return flag;
}

int validaFechaMes(int mes){
    int flag=0;
    if(mes > 0 && mes <7){
        flag=1;
    }
    return flag;
}

int validaFechaDia(int dia, int mes){
    int flag=0;
    if(mes == 1 || mes == 3 || mes ==5){
        if(dia >0 && dia <32){
            flag=1;
        }
    }else if(mes == 4 || mes == 6){
        if(dia>0 && dia<31){
            flag=1;
        }

    }else{
        if(dia>0 && dia <29){
            flag=1;
        }
    }
    return flag;
}




void darDeBajaConsumoPorFecha(char nombreArchivo[], int nroCliente){

    stConsumos c;
    int anio, mes, dia;
    int pos;
    int existeFecha=-1;
    int existeNroCliente=-1;
    FILE *archi = fopen(nombreArchivo, "r+b");

    if(archi){
        existeNroCliente=buscaIdClienteEnArchivoConsumos(archi, nroCliente);
        if(existeNroCliente==1){
            printf("\nINGRESE ANIO: ");
            fflush(stdin);
            scanf("%d", &anio);

            printf("\nINGRESE MES: ");
            fflush(stdin);
            scanf("%d", &mes);

            printf("\nINGRESE DIA: ");
            fflush(stdin);
            scanf("%d", &dia);
            existeFecha=buscaConsumoPorFecha(archi, anio, mes, dia);
            if(existeFecha==1){
                pos=devuelvePosicionArchivoDeConsumosPorFecha(nombreArchivo, anio, mes, dia);
                fseek(archi, sizeof(stConsumos)*(pos-1), 0);
                fread(&c, sizeof(stConsumos), 1, archi);
                c.baja =1;
                fseek(archi, sizeof(stConsumos)*(pos-1), 0);
                fwrite(&c, sizeof(stConsumos), 1, archi);
                printf("\nCONSUMO DADO DE BAJA CORRECTAMENTE");
                getch();
            }
        }
        fclose(archi);
    }
}

void muestraArregloConsumos(stConsumos c[], int v){

    int i=0;

    ordenaConsumosPorSeleccionPorMes(c, v);

    for(i=0; i<v; i++){
            mostrarUnConsumo(c[i]);
        }
}

void muestraConsumosPorNroCliente(stConsumos c[], int v, int nroCliente){

    int i=0;

    ordenaConsumosPorSeleccionPorMes(c, v);

    for(i=0; i<v; i++){
        if(c[i].idCliente == nroCliente){
            mostrarUnConsumo(c[i]);
        }
    }
}

void ordenaConsumosPorSeleccionPorMes(stConsumos c[], int v){
    int posMenor;
    int i=0;
    while(i<v-1){
        posMenor=buscaPosMenorPorMes(c, v, i);
        intercambioStConsumos(&c[posMenor],&c[i]);
        i++;
    }
}

int buscaPosMenorPorMes(stConsumos c[], int v, int pos){
    int posMenor = pos;
    pos++;
    while(pos<v){
        if(c[pos].mes < c[posMenor].mes){
            posMenor = pos;
        }
        pos++;
    }

    return posMenor;
}

void intercambioStConsumos(stConsumos *a, stConsumos *b){
    stConsumos aux = *a;
    *a = *b;
    *b = aux;
}

int pasaArchivoAArregloConsumos(char nombreArchivo[], stConsumos c[], int dim)
{
    int i=0;
    stConsumos con;
    FILE *archi=fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(i<dim && fread(&con, sizeof(stConsumos), 1, archi) > 0)
        {
            c[i] = con;
            i++;
        }
        fclose(archi);
    }
    return i;
}
