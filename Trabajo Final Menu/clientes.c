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

stCliente cargaUnCliente(){
    stCliente a;


    system("cls");

    printf("\nINGRESE NUMERO DE CLIENTE QUE DESEA: ");
    fflush(stdin);
    scanf("%d", &a.nroCliente);

    printf("\nINGRESE NOMBRE: ");
    fflush(stdin);
    gets(a.nombre);

    printf("\nINGRESE APELLIDO: ");
    fflush(stdin);
    gets(a.apellido);

    printf("\nINGRESE DNI: ");

    fflush(stdin);
    gets(a.dni);

    printf("\nINGRESE EMAIL: ");
    fflush(stdin);
    gets(a.email);

    printf("\nINGRESE MOVIL: ");
    fflush(stdin);
    gets(a.movil);

    printf("\nINGRESE DOMICILIO: ");
    fflush(stdin);
    gets(a.domicilio);

    printf("\nHA SIDO DADO DE ALTA CORRECTAMENTE....");
    getch();


    return a;
}

void muestraUnCliente(stCliente a){


    printf("\n ID CLIENTE:...: %d", a.id);
    printf("\n NRO CLIENTE:..: %d", a.nroCliente);
    printf("\n NOMBRE........: %s", a.nombre);
    printf("\n APELLIDO......: %s", a.apellido);
    printf("\n DNI...........: %s", a.dni);
    printf("\n EMAIL.........: %s", a.email);
    printf("\n MOVIL.........: %s", a.movil);
    printf("\n DOMICILIO.....: %s", a.domicilio);
    printf("\n---------------------------------------------------");

}

void cargaArchivoClientes(char nombreArchivo [])
{

    stCliente a;
    int existeDni=-1;
    int existeNroCliente=-1;
    int existeEmail=-1;
    int existeMovil=-1;
    char opcion=0;
    int static id;
    id = ultimoId(nombreArchivo);

    FILE *archi = fopen(nombreArchivo, "r+b");

    if(archi)
    {

        do
        {
            system("cls");
            id++;

            while(existeNroCliente!=0){
                system("cls");
                printf("\nINGRESE NRO DE CLIENTE: ");
                fflush(stdin);
                scanf("%d", &a.nroCliente);
                existeNroCliente=buscaNroDeClienteEnArchivo(archi, a.nroCliente);
                if(existeNroCliente==1){
                    printf("\nERROR - EL NRO DE CLIENTE YA EXISTE NO SE PUEDE CARGAR\n");
                    getch();
                }
            }


            system("cls");
            printf("\nINGRESE NOMBRE: ");
            fflush(stdin);
            gets(a.nombre);
            validacionNomOApeGeneral(a.nombre);

            system("cls");
            printf("\nINGRESE APELLIDO: ");
            fflush(stdin);
            gets(a.apellido);
            validacionNomOApeGeneral(a.apellido);

            while(existeDni!=0){
                system("cls");
                printf("\nINGRESE DNI: ");
                fflush(stdin);
                gets(a.dni);
                validacionGeneralDni(a.dni);
                existeDni=buscaDniEnArchivo(archi, a.dni);
                if(existeDni==1){
                    printf("\nERROR - EL DNI YA EXISTE NO SE PUEDE CARGAR\n");
                    getch();
                }
            }



            while(existeEmail!=0){
                system("cls");
                printf("\nINGRESE EMAIL: ");
                fflush(stdin);
                gets(a.email);
                existeEmail=buscaEmailEnArchivo(archi, a.email);
                if(existeMovil==1){
                    printf("\nERROR - EL EMAIL YA EXISTE NO SE PUEDE CARGAR\n");
                    getch();
                }
            }


            while(existeMovil!=0){
                system("cls");
                printf("\nINGRESE MOVIL: ");
                fflush(stdin);
                gets(a.movil);
                validacionTelGeneral(a.movil);
                existeMovil=buscaMovilEnArchivo(archi, a.movil);
                if(existeMovil==1){
                    printf("\nERROR - EL MOVIL YA EXISTE NO SE PUEDE CARGAR\n");
                    getch();
                }
            }


            system("cls");
            printf("\nINGRESE DOMICILIO: ");
            fflush(stdin);
            gets(a.domicilio);



            a.id=id;
            a.eliminado=0;
            if(existeDni==0 && existeEmail==0 && existeMovil==0 && existeNroCliente==0){
                fseek(archi, 0, SEEK_END);
                fwrite(&a, sizeof(stCliente), 1, archi);
                printf("\nHA SIDO DADO DE ALTA CORRECTAMENTE....");
            }
            existeDni=-1;
            existeNroCliente=-1;
            existeEmail=-1;
            existeMovil=-1;


            printf("\n\nESC PARA SALIR / CUALQUIER TECLA PARA CARGAR OTRO CLIENTE...\n");
            opcion = getch();
        }

        while(opcion!=27);
        fclose(archi);
    }
}

////////////////////////////////////////////////////////
///////////FUNCIONES DE VALIDACION DE ALAN//////////////
////////////////////////////////////////////////////////

int validacionStDni(char dni[]){
  int flag=0;
  int i=0;
    while (dni[i]!='\0' && flag == 0){
        if (isdigit(dni[i])){// recorro posicion por posicion y verifico si es un digito del 0 al 9
             i++;
        }else {
        flag = 1;
        }

     }

  return flag;
}

int validacionConAtoi (char dni[]){
  int flag=0;
  int num = atoi(dni);

  if(num <10000000 || num > 100000000){
    flag = 1;
  }
    return flag;
}

void validacionGeneralDni (char dni[]){
 int flag1=0;// creo 2 flags que van a tomar los valores que devuelvan las otras funciones
 int flag2=0;

    flag1 = validacionStDni(dni);// flag1 es igual a lo que retorna la funcion
    flag2 = validacionConAtoi(dni);// flag2 es igual a lo que retorna la funcion
    while (flag1 == 1 || flag2 == 1){ // si alguna de las 2 flag esta en 1, el dni es incorrecto
            //system("cls");
        printf("\nERROR- INGRESE DNI: ");
        gets(dni);
        flag1 = validacionStDni(dni);// valido hasta que el dni sea correcto
        flag2 = validacionConAtoi(dni);
        }

}

int validacionNomOApe (char nom[]){
    int i=0;                         //creo subindice
    int flag=0;                      // creo bandera
    int mayus=0;                     // contador de mayusculas
    int espacio=0;                   // contador de espacios
 while (nom[i]!='\0' && flag ==0){   //si no es final de cadena y flag es 0, entro
      if (nom[i]==' '){
        espacio++;                   // si algun caracter el espacio, incremento contador
      }else if (isupper(nom[i])){
      mayus++;                       // si algun caracter el mayuscula, incremento contador
      }else if(isalpha(nom[i]) || isupper(nom[0])) // si el caracter el letra o la posicion 0 tiene mayuscula
      flag = 0;
      else {
      flag = 1;
      }
    i++;
 }
 i=0;
 while (nom[i]!= '\0'){   // valido que el string no tengo ningun numero
    if (isdigit(nom[i])){
        flag = 1;
    }
    i++;
 }

 if (espacio>2 || mayus>3 || i<3){ //si el string tiene mas de 2 espacios, mas de 3 mayusculas o la cantidad es menor a 3 flag 1
    flag = 1;
 }
  return flag; // retorno flag
}

void validacionNomOApeGeneral (char nom[]){
    int flag =0;                                // creo bandera
    flag = validacionNomOApe(nom);              // bandera es lo que devulve la otra funcion
    while(flag == 1){                           // si flag es 1, hay error
        printf("\nERROR-INGRESE NUEVAMENTE: ");
        gets(nom);
        flag = validacionNomOApe(nom);          // vuelvo a validar

    }

}

int validacionTelIsdigit(char tel[]){
  int i=0;
  int flag =0;

  while (tel[i]!='\0' && flag==0){
    if(isdigit(tel[i])){
         i++;
    }else{
    flag =1;
    }

  }
  return flag;
}

int validacionTelCantidadDigit (char tel[]){
    int i=0;
    int flag=0;

      while (tel[i]!= '\0' && flag == 0){
          i++;
        }
        if (i<9 || i>13){
            flag = 1;
        }

    return flag;
}

void validacionTelGeneral(char tel[]){
    int flag =0;//creo 2 banderas para las 2 funciones
    int flag2=0;
    flag = validacionTelIsdigit(tel);//llamo a las 2 funciones de validacion
    flag2 = validacionTelCantidadDigit(tel);
    while(flag == 1 || flag2==1){//si alguna bandera vale 1 entra al ciclo
        printf("\nERROR-INGRESE NUEVAMENTE: ");
        gets(tel);
        flag = validacionTelIsdigit(tel);// vuelve a validar
        flag2= validacionTelCantidadDigit(tel);
    }

}

//FUNCION QUE ME MUESTRA TODOS LOS CLIENTES (BAJA Y ALTA)
void muestraArchivoClientes(char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    stCliente a;

    if(archi)
    {
        while(fread(&a, sizeof(stCliente), 1, archi)>0)
        {
            muestraUnCliente(a);
        }
        fclose(archi);
    }
}
//FUNCION QUE MUESTRA SOLO LOS CLIENTES EN ALTA ACTIVA
void muestraArchivoClientesEnAltaActiva(char nombreArchivo[], int c)
{
    FILE * archi = fopen(ARCHI_CLIENTES, "rb");
    stCliente a;

    if(archi)
    {
        while(fread(&a, sizeof(stCliente), 1, archi)>0)
        {
            if(a.eliminado==0)
            {
                muestraUnCliente(a);
            }
        }
        fclose(archi);
    }
}
//FUNCION QUE MUESTRA SOLO LOS CLIENTES EN BAJA
void muestraArchivoClientesEnBaja(char nombreArchivo[], int c)
{
    FILE * archi = fopen(ARCHI_CLIENTES, "rb");
    stCliente a;

    if(archi)
    {
        while(fread(&a, sizeof(stCliente), 1, archi)>0)
        {
            if(a.eliminado==1)
            {
                muestraUnCliente(a);
            }
        }
        fclose(archi);
    }
}

//FUNCION QUE SE ENCARGA DE BUSCAR UN CLIENTE EN PARTICULAR TOMANDO POR PARAMETRO EL NRO DE CLIENTE
void buscaUnClienteYLoMuestra(char nombreArchivo[], int nroCliente){
    stCliente a;
    FILE *archi = fopen(nombreArchivo, "rb");
    int existe;
    int pos;

    if(archi){
        existe=buscaNroDeClienteEnArchivo(archi, nroCliente);//CONTROLO QUE EL NRO DE CLIENTE EXISTA
        if(existe==1){
            pos=devuelvePosicionArchivoPorNroCliente(nombreArchivo, nroCliente);//MEDIANTE LA FUNCION DEVUELVEPOS... OBTENGO LA POSICION DEL REGISTRO Y MEDIANTE EL FSEEK ME POSICIONO USO (POS-1) PORQUE SINO LEO EL REGISTRO QUE LE SIGUE
            fseek(archi, sizeof(stCliente)*(pos-1), 0);
            fread(&a, sizeof(stCliente), 1, archi);
            muestraUnCliente(a);
            getch();

        }else{
            printf("\nERROR - EL NRO DE CLIENTE NO EXISTE\n");
            getch();
        }
        fclose(archi);
    }
}

//FUNCION QUE RETORNA EL ULTIMO ID PARA PODER HACER EL AUTOINCREMENTO DEL ID EN EL ARCHIVO
int ultimoId(char nombreArchivo[])
{
    int id=0;
    stCliente a;
    FILE *archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        fseek(archi, -1*(sizeof(stCliente)), SEEK_END);
        if(fread(&a, sizeof(stCliente), 1, archi)>0)
        {
            id=a.id;
        }
        fclose(archi);
    }
    return id;
}

//FUNCION QUE ME DEVUELTA LA POSICION DE UN REGISTRO EN EL ARCHIVO INGRESANDO POR PARAMETRO EL DNI
int devuelvePosicionArchivo(char nombreArchivo[], char dni[])
{
    stCliente a;
    int flag=0;
    int i=0;
    FILE *archi = fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(flag==0 && fread(&a, sizeof(stCliente), 1, archi)>0)
        {
            if(strcmpi(dni, a.dni)==0)
            {
                flag=1;
            }
            i++;
        }
        fclose(archi);
    }
    return i;
}

//FUNCION QUE ME DEVUELTA LA POSICION DE UN REGISTRO EN EL ARCHIVO INGRESANDO POR PARAMETRO EL NRO DE CLIENTE
int devuelvePosicionArchivoPorNroCliente(char nombreArchivo[], int nroCliente)
{
    stCliente a;
    int flag=0;
    int i=0;
    FILE *archi = fopen(ARCHI_CLIENTES, "rb");
    if(archi)
    {
        while(flag==0 && fread(&a, sizeof(stCliente), 1, archi)>0)
        {
            if(nroCliente == a.nroCliente)
            {
                flag=1;
            }
            i++;
        }
        fclose(archi);
    }
    return i;
}

///////////////////////////////////////////////////////////////////////////////////////
////////////////FUNCIONES PARA VALIDAR QUE LOS DATOS NO EXISTAN////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

int buscaNroDeClienteEnArchivo(FILE *archi, int nroCliente)
{
    stCliente a;
    int flag=0;
    rewind(archi);
    if(archi)
    {
        while(flag==0 && fread(&a, sizeof(stCliente), 1, archi)>0)
        {
            if(nroCliente == a.nroCliente)
            {
                flag=1;
            }
        }
        //fclose(archi);
    }
    return flag;
}

int buscaDniEnArchivo(FILE *archi, char dni[])
{
    stCliente a;
    int flag=0;
    rewind(archi);
    if(archi)
    {
        while(flag==0 && fread(&a, sizeof(stCliente), 1, archi)>0)
        {
            if(strcmpi(dni, a.dni)== 0)
            {
                flag=1;
            }
        }
        //fclose(archi);

    }
    return flag;
}

int buscaEmailEnArchivo(FILE *archi, char email[])
{
    stCliente a;
    int flag=0;
    rewind(archi);
    if(archi)
    {
        while(flag==0 && fread(&a, sizeof(stCliente), 1, archi)>0)
        {
            if(strcmpi(email, a.email)== 0)
            {
                flag=1;
            }
        }
        //fclose(archi);

    }
    return flag;
}

int buscaMovilEnArchivo(FILE *archi, char movil[])
{
    stCliente a;
    int flag=0;
    rewind(archi);
    if(archi)
    {
        while(flag==0 && fread(&a, sizeof(stCliente), 1, archi)>0)
        {
            if(strcmpi(movil, a.movil)== 0)
            {
                flag=1;
            }
        }
        //fclose(archi);

    }
    return flag;
}


//FUNCION PARA MODIFICAR TODOS LOS DATOS DEL CLIENTE INGRESANDO EL DNI
void modificaStCliente(char nombreArchivo[], char dni[])
{
    FILE *archi = fopen(nombreArchivo, "r+b");
    stCliente a;
    int pos;
    int existe;
    int opcion;
    if(archi)
    {
        existe = buscaDniEnArchivo(archi, dni);//Verifico que el dni ingresado exista
        if(existe==1)
        {
            pos=devuelvePosicionArchivo(ARCHI_CLIENTES, dni);//me devuelve la posicion en donde se encuentra el registro que quiero modificar
            fseek(archi, sizeof(stCliente)*(pos-1), 0);
            fread(&a, sizeof(stCliente), 1, archi);
            do
            {
                system("cls");
                printf("\n\t\t\t\t\t\t\tEDITAR\n");
                printf("\n====================================================================================================================");
                printf("\n QUE DESEA EDITAR?\n");
                printf("\n<1> NOMBRE");
                printf("\n<2> APELLIDO");
                printf("\n<3> DNI");
                printf("\n<4> EMAIL");
                printf("\n<5> DOMICILIO");
                printf("\n<6> MOVIL");
                printf("\n<7> NUMERO DE CLIENTE");
                printf("\n<0> REGRESAR\n");

                printf("\nINGRESE UNA OPCION: ");
                scanf("%d", &opcion);
                switch(opcion)
                {
                case 1:
                    printf("\nINGRESE NUEVO NOMBRE: ");//le pido que ingrese el nuevo nombre
                    fflush(stdin);
                    gets(a.nombre);
                    fseek(archi, sizeof(stCliente)*(-1), SEEK_CUR);//me vuelvo a posicionar en el registro que quiero que escriba
                    fwrite(&a, sizeof(stCliente), 1, archi);
                    printf("\n<<SE HA MODIFICADO CORRECTAMENTE>>\n");
                    muestraUnCliente(a);
                    getch();
                    break;

                case 2:

                    printf("\nINGRESE NUEVO APELLIDO: ");
                    fflush(stdin);
                    gets(a.apellido);
                    fseek(archi, sizeof(stCliente)*(pos-1), 0);
                    fwrite(&a, sizeof(stCliente), 1, archi);
                    printf("\n<<SE HA MODIFICADO CORRECTAMENTE>>\n");
                    muestraUnCliente(a);
                    getch();

                    break;

                case 3:
                    printf("\nINGRESE NUEVO DNI: ");
                    fflush(stdin);
                    gets(a.dni);
                    fseek(archi, sizeof(stCliente)*(pos-1), 0);
                    fwrite(&a, sizeof(stCliente), 1, archi);
                    printf("\n<<SE HA MODIFICADO CORRECTAMENTE>>\n");
                    muestraUnCliente(a);
                    getch();
                    break;

                case 4:
                    printf("\nINGRESE NUEVO EMAIL: ");
                    fflush(stdin);
                    gets(a.email);
                    fseek(archi, sizeof(stCliente)*(pos-1), 0);
                    fwrite(&a, sizeof(stCliente), 1, archi);
                    printf("\n<<SE HA MODIFICADO CORRECTAMENTE>>\n");
                    muestraUnCliente(a);
                    getch();
                    break;

                case 5:
                    printf("\nINGRESE NUEVO DOMICILIO: ");
                    fflush(stdin);
                    gets(a.domicilio);
                    fseek(archi, sizeof(stCliente)*(pos-1), 0);
                    fwrite(&a, sizeof(stCliente), 1, archi);
                    printf("\n<<SE HA MODIFICADO CORRECTAMENTE>>\n");
                    muestraUnCliente(a);
                    getch();
                    break;

                case 6:
                    printf("\nINGRESE NUEVO MOVIL: ");
                    fflush(stdin);
                    gets(a.movil);
                    fseek(archi, sizeof(stCliente)*(pos-1), 0);
                    fwrite(&a, sizeof(stCliente), 1, archi);
                    printf("\n<<SE HA MODIFICADO CORRECTAMENTE>>\n");
                    muestraUnCliente(a);
                    getch();
                    break;

                case 7:
                    printf("\nINGRESE NUEVO NRO DE CLIENTE: ");
                    fflush(stdin);
                    scanf("%d", &a.nroCliente);
                    fseek(archi, sizeof(stCliente)*(pos-1), 0);
                    fwrite(&a, sizeof(stCliente), 1, archi);
                    printf("\n<<SE HA MODIFICADO CORRECTAMENTE>>\n");
                    muestraUnCliente(a);
                    getch();
                    break;

                case 0:

                    break;
                }

            }
            while(opcion!=0);


        }else{
            printf("\n ERROR - DNI NO PERTENECE A NINGUN CLIENTE\n");
            getch();
        }
        fclose(archi);
    }
}


//FUNCION PARA DAR DE BAJA UN CLIENTE POR EL NRO DE CLIENTE
void bajaCliente(char nombreArchivo[], int nroCliente)
{
    stCliente a;
    char opcion;
    int pos;
    int existe;
    FILE *archi = fopen(ARCHI_CLIENTES, "r+b");
    if(archi)
    {
        pos = devuelvePosicionArchivoPorNroCliente(ARCHI_CLIENTES, nroCliente);
        fseek(archi, sizeof(stCliente)*(pos-1), 0);
        if(fread(&a, sizeof(stCliente), 1, archi)>0)
        {
            a.eliminado = 1;
        }
        existe=buscaNroDeClienteEnArchivo(archi, nroCliente);
        if(existe==1)
        {
            printf("\nESTA SEGURO QUE QUIERE DARSE DE BAJA? s/n: ");
            fflush(stdin);
            scanf("%c", &opcion);
            if(opcion == 115)
            {
                fseek(archi, sizeof(stCliente)*(pos-1), 0);
                fwrite(&a, sizeof(stCliente), 1, archi);

            }
        }
        else
        {
            printf("\nERROR - EL CLIENTE NO EXISTE");
            getch();
        }
        fclose(archi);
    }
}


//FUNCION PARA PASAR DE ARCHIVO A ARREGLO Y ASI PODER ORDENAR
int pasaArchivoAArreglo(char nombreArchivo[], stCliente arrayC[], int dim)
{
    int i=0;
    stCliente a;
    FILE *archi=fopen(nombreArchivo, "rb");
    if(archi)
    {
        while(i<dim && fread(&a, sizeof(stCliente), 1, archi) > 0)
        {
            arrayC[i]=a;
            i++;
        }
        fclose(archi);
    }
    return i;
}


//FUNCIONES PARA ORDENAMIENTO
int buscaPosicionMenorsStClientePorApellido(stCliente arrayC[], int v, int pos)
{
    int posMenor=pos;
    pos++;
    while(pos<v)
    {
        if(strcmpi(arrayC[pos].apellido, arrayC[posMenor].apellido)<0)
        {
            posMenor=pos;
        }
        pos++;
    }
    return posMenor;
}

int buscaPosicionMenorsStClientePoDni(stCliente arrayC[], int v, int pos)
{
    int posMenor=pos;
    pos++;
    while(pos<v)
    {
        if(strcmpi(arrayC[pos].dni, arrayC[posMenor].dni)<0)
        {
            posMenor=pos;
        }
        pos++;
    }
    return posMenor;
}

int buscaPosicionMenorsStClientePoNroCliente(stCliente arrayC[], int v, int pos)
{
    int posMenor=pos;
    pos++;
    while(pos<v)
    {
        if(arrayC[pos].nroCliente < arrayC[posMenor].nroCliente)
        {
            posMenor=pos;
        }
        pos++;
    }
    return posMenor;
}

void intercambioStCliente (stCliente *a, stCliente *b)
{
    stCliente aux=*a;
    *a=*b;
    *b=aux;
}

void ordenamientoApellido(stCliente array[], int v)
{
    int posMenor;
    int i=0;
    while(i<v-1)
    {
        posMenor=buscaPosicionMenorsStClientePorApellido(array, v, i);
        intercambioStCliente(&array[posMenor], &array[i]);
        i++;
    }
}

void ordenamientoDni(stCliente array[], int v)
{
    int posMenor;
    int i=0;
    while(i<v-1)
    {
        posMenor=buscaPosicionMenorsStClientePoDni(array, v, i);
        intercambioStCliente(&array[posMenor], &array[i]);
        i++;
    }
}

void ordenamientoNroCliente(stCliente array[], int v)
{
    int posMenor;
    int i=0;
    while(i<v-1)
    {
        posMenor=buscaPosicionMenorsStClientePoNroCliente(array, v, i);
        intercambioStCliente(&array[posMenor], &array[i]);
        i++;
    }
}

//FUNCION PARA MOSTRAR EL ARREGLO
void muestraArregloClientes(int v, stCliente a[])
{
    for(int i=0; i<v; i++)
    {
        muestraUnCliente(a[i]);
    }
}



