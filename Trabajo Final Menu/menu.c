#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "clientes.h"
#include "consumos.h"
#include "menu.h"

#define ARCHI_CLIENTES "clientes.dat"
#define ARCHI_CONSUMOS "consumos.dat"
#define DIM_CONSUMOS 2000


void menuPrincipal()
{


    system("color 2F");

    int opcion;

    do
    {
        system("cls");
        printf("\n\t\t\t\t\t\tMENU PRINCIPAL\n");
        printf("\n====================================================================================================================");
        printf("\n\tBIENVENIDO\n");
        printf("\n<1> MODO CLIENTE");
        printf("\n<2> MODO EMPLEADO");
        printf("\n<0> SALIR\n");

        printf("\nINGRESE UNA OPCION: ");//Si entra en modo empleado le tenemos que pedir la contrasenia para que no entre cualquiera en ese modo
        scanf("%d", &opcion);

        switch(opcion)
        {

        case 1:

            menuCliente();
            break;

        case 2: ;//ESTA PARTE TENDRIA QUE ESTAR EN UNA FUNCION AFUERA Y LLAMARLA UNA VEZ QUE ENTRA A LA OPCION 2 ASI NO QUEDA TODO ESTE CHOCLO ACA ADENTRO

            char password[]= {"empleado"};
            char pass[9];
            char caracter;
            int i=0;
            printf("\nPASSWORD: ");
            while(caracter = getch())
            {
                if(caracter==13)
                {
                    pass[i]='\0';
                    break;
                }
                else if(caracter==8)
                {
                    i--;
                    printf("\b \b");
                }
                else
                {
                    printf("*");
                    pass[i]=caracter;
                    i++;
                }
            }
            if(strcmpi(pass, password)==0)
            {
                menuEmpleado();
            }
            else
            {
                printf("\nPASSWORD INCORRECTA");
                getch();
            }
            break;

        case 0:

            break;
        }


    }
    while(opcion!=0);




}

void menuCliente()
{

    system("color 6F");
    int opcion;


    do
    {
        system("cls");
        printf("\n\t\t\t\t\t\tMODO CLIENTE\n");
        printf("\n====================================================================================================================");
        printf("\n<1> ALTA");
        printf("\n<2> CONSULTA");
        printf("\n<0> REGRESAR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            menuAlta();
            break;

        case 2:
            menuConsultaCliente();
            break;

        case 0:
            system("color 2F");
            break;
        }
    }
    while(opcion!=0);


}










void menuEmpleado()
{

    system("color 3F");
    int opcion;





    do
    {
        system("cls");
        printf("\n\t\t\t\t\t\tMODO EMPLEADO\n");
        printf("\n====================================================================================================================");
        printf("\n<1> ALTA");
        printf("\n<2> BAJA");
        printf("\n<3> EDITAR");
        printf("\n<4> CONSULTA");
        printf("\n<5> LISTADO");
        printf("\n<6> CARGAR 1000 CONSUMOS");
        printf("\n<0> REGRESAR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);
        switch(opcion)
        {
        case 1:
            menuAlta();
            break;

        case 2:
            menuBaja();
            break;

        case 3:

            menuEditar();
            break;

        case 4:
            menuConsultaEmpleado();
            break;

        case 5:
            menuListadoDeClientes();
            break;

        case 6:
            cargaArchivoConsumosRandom(ARCHI_CONSUMOS);
            printf("\nSE CARGARON LOS CONSUMOS CORRECTAMENTE");
            getch();
            break;

        case 0:
            system("color 2F");
            break;
        }


    }
    while(opcion!=0);


}

void menuAlta()
{



    int opcion;
    do
    {
        system("cls");
        printf("\n\t\t\t\t\t\t\tALTA\n");
        printf("\n====================================================================================================================");
        printf("\n<1> ALTA CLIENTE");
        printf("\n<2> ALTA CONSUMO");
        printf("\n<0> REGRESAR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);
        switch(opcion)
        {
        case 1:

            cargaArchivoClientes(ARCHI_CLIENTES);
            break;

        case 2: ;

            int nroCliente;
            printf("\nINGRESE NRO DE CLIENTE: ");
            fflush(stdin);
            scanf("%d", &nroCliente);
            cargarArchivoDeConsumos(ARCHI_CONSUMOS, nroCliente);
            break;

        case 0:

            break;
        }



    }
    while(opcion!=0);

}

void menuBaja()
{
    int opcion;
    int numeroCliente;




    printf("\nINGRESE NUMERO DE CLIENTE: ");
    fflush(stdin);
    scanf("%d", &numeroCliente);

    do
    {
        system("cls");
        printf("\n\t\t\t\t\t\t\tBAJA\n");
        printf("\n====================================================================================================================");
        printf("\n<1> BAJA CLIENTE");
        printf("\n<2> BAJA CONSUMO");
        printf("\n<0> REGRESAR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            bajaCliente(ARCHI_CLIENTES, numeroCliente);
            break;

        case 2:
            darDeBajaConsumoPorFecha(ARCHI_CONSUMOS, numeroCliente);
            break;

        case 0:

            break;
        }



    }
    while(opcion!=0);


}



void menuEditar()
{


    char dni[10];
    printf("\nINGRESE DNI: ");
    fflush(stdin);
    gets(dni);


    modificaStCliente(ARCHI_CLIENTES, dni);

}





void menuConsultaCliente()
{
    int opcion;
    int nroCliente;
    printf("\nINGRESE NRO DE CLIENTE: ");
    fflush(stdin);
    scanf("%d", &nroCliente);
    do
    {
        system("cls");
        printf("\n\t\t\t\t\t\t\tCONSULTA\n");
        printf("\n====================================================================================================================");
        printf("\n<1> BUSCAR CONSUMO POR FECHA");
        printf("\n<2> TOTAL DE CONSUMOS");
        printf("\n<0> REGRESAR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);
        switch(opcion)
        {
        case 1:

            buscarConsumoPorFechaYLoMuestra(ARCHI_CONSUMOS, nroCliente);
            getch();
            break;

        case 2:;
            stConsumos con3[DIM_CONSUMOS];
            int vConsumos3 = 0;
            vConsumos3 = pasaArchivoAArregloConsumos(ARCHI_CONSUMOS, con3, DIM_CONSUMOS);

            muestraConsumosPorNroCliente(con3, vConsumos3, nroCliente);
            getch();
            break;

        case 0:

            break;
        }

    }
    while(opcion!=0);
}

void menuConsultaEmpleado()
{
    int nroCliente;
    int opcion;
    do
    {
        system("cls");
        printf("\n\t\t\t\t\t\t\tCONSULTA\n");
        printf("\n====================================================================================================================");
        printf("\n<1> CONSUMO DE CLIENTE POR FECHA");
        printf("\n<2> TOTAL DE CONSUMOS DE CLIENTE");
        printf("\n<3> TOTAL DE CONSUMOS DE TODOS LOS CLIENTES");
        printf("\n<0> REGRESAR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);
        switch(opcion)
        {
        case 1:
            printf("\nINGRESE NRO DE CLIENTE: ");
            fflush(stdin);
            scanf("%d", &nroCliente);
            buscarConsumoPorFechaYLoMuestra(ARCHI_CONSUMOS, nroCliente);
            getch();
            break;

        case 2:
            printf("\nINGRESE NRO DE CLIENTE: ");
            fflush(stdin);
            scanf("%d", &nroCliente);

            stConsumos con[DIM_CONSUMOS];
            int vConsumos = 0;
            vConsumos = pasaArchivoAArregloConsumos(ARCHI_CONSUMOS, con, DIM_CONSUMOS);

            muestraConsumosPorNroCliente(con, vConsumos, nroCliente);
            getch();
            break;

        case 3:;
            stConsumos con2[DIM_CONSUMOS];
            int vConsumos2 = 0;
            vConsumos2 = pasaArchivoAArregloConsumos(ARCHI_CONSUMOS, con2, DIM_CONSUMOS);

            muestraArregloConsumos(con2, vConsumos2);

            system("pause");
            break;

        case 0:

            break;
        }

    }
    while(opcion!=0);
}

void menuListadoDeClientes()
{
    int opcion;
    do
    {
        system("cls");
        printf("\n\t\t\t\t\t\t\tLISTADO\n");
        printf("\n====================================================================================================================");
        printf("\n<1> LISTADO CLIENTES EN ALTA ACTIVA");
        printf("\n<2> LISTADO CLIENTES DADOS DE BAJA");
        printf("\n<3> LISTADO  DE TODOS LOS CLIENTES (ALTA Y BAJA)");
        printf("\n<4> BUSCAR UN CLIENTE");
        printf("\n<0> REGRESAR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);
        switch(opcion)
        {
        case 1:
            printf("\n\t\t\t\t\t\tCLIENTES EN ALTA ACTIVA");
            printf("\n====================================================================================================================");
            muestraArchivoClientesEnAltaActiva(ARCHI_CLIENTES, 0);
            getch();
            break;

        case 2:
            printf("\n\t\t\t\t\t\tCLIENTES EN BAJA");
            printf("\n====================================================================================================================");
            muestraArchivoClientesEnBaja(ARCHI_CLIENTES, 1);
            getch();
            break;

        case 3:
            menuOrdenamientoClientes();
            break;

        case 4: ;
            int nroCliente;
            printf("\nINGRESE NRO DE CLIENTE A BUSCAR: ");
            fflush(stdin);
            scanf("%d", &nroCliente);
            buscaUnClienteYLoMuestra(ARCHI_CLIENTES, nroCliente);


            break;

        case 0:

            break;
        }

    }
    while(opcion!=0);
}

void menuOrdenamientoClientes()
{
    stCliente arrayClientes[100];
    int vClientes=0;
    vClientes=pasaArchivoAArreglo(ARCHI_CLIENTES, arrayClientes, 100);
    int opcion;
    do
    {
        system("cls");
        printf("\n\t\t\t\t\t\t\tLISTADO CLIENTES");
        printf("\n====================================================================================================================");
        printf("\nCOMO DESAR ORDENAR LOS DATOS?");
        printf("\n<1> POR APELLIDO");
        printf("\n<2> POR DNI");
        printf("\n<3> POR NUMERO DE CLIENTE");
        printf("\n<0> REGRESAR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);
        switch(opcion)
        {
        case 1:
            printf("\n<<<<TOTAL DE REGISTROS: %d>>>>\n", vClientes);
            ordenamientoApellido(arrayClientes, vClientes);
            muestraArregloClientes(vClientes, arrayClientes);
            getch();

            break;

        case 2:
            ordenamientoDni(arrayClientes, vClientes);
            printf("\n<<<<TOTAL DE REGISTROS: %d>>>>\n", vClientes);
            muestraArregloClientes(vClientes, arrayClientes);
            getch();

            break;

        case 3:
            ordenamientoNroCliente(arrayClientes, vClientes);
            printf("\n<<<<TOTAL DE REGISTROS: %d>>>>\n", vClientes);
            muestraArregloClientes(vClientes, arrayClientes);
            getch();

            break;

        case 0:

            break;
        }

    }
    while(opcion!=0);
}



