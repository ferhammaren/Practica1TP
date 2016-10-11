/*
 * Hecho por||Coded by||Laved af||プログラムした作: 
 * Fernanda Meza
 * https://github.com/ferhammaren
 * Incluye todo para presentarlo bonito, don't fuck it up darling!
 */

/* 
 * File:   main.c
 * Author: fer
 *
 * Created on October 9, 2016, 12:35 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int row, col, menuOption = 0, c; //Variables para guardar las filas y columnas de tu terminal.

    char gradosDescripciones[3][15] = {"Licenciatura", "Maestria", "Doctorado"};
    //Arreglos pertenecientes a los expositores
    int numerosExpositores[50], gradosAcademicos[50], expositoresRegistrados = 0;
    char nombresExpositores[200][50], instituciones[200][50], temas[200][50], magistral[3][50];

    initscr();
    getmaxyx(stdscr, row, col); //esta funcion guarda cuantas filas y columnas del output standard hay
    //Para imprimir en el centro de la pantalla, a col dividilo entre 2 y restale aproximadamente el numero de caracteres
    //de lo que vas a imprimir

    do {
        clear(); //limpiamos la pantalla cada que entremos al menu
        mvprintw(2, col / 2 - 19, "CONTROL DE EXPOSITORES");
        mvprintw(4, col / 2 - 19, "[1] Registro de expositores"); //le puse el mismo valor de x aqui para que salga
        //alineado con la linea de arriba
        mvprintw(5, col / 2 - 19, "[2] Modificación de datos del expositor");
        mvprintw(6, col / 2 - 19, "[3] Bajas de expositor");
        mvprintw(7, col / 2 - 19, "[4] Consultas");
        mvprintw(8, col / 2 - 19, "[5] Salir del programa\n");
        scanw("%d", &menuOption);

        switch (menuOption) {
            case 1:
                // <editor-fold defaultstate="collapsed" desc="Registro de expositores">
                clear();
                //voy a declarar aquí las variables para que sea un poquito mas manejable, pero mas abajo se usan otra vez
                //also, importante: No puedes hacer declaraciones después de labels (goto o en este caso
                //casos), te va a marcar error. Para solucionar esto, puse el clear primero!

                //int ex1=0; variable para controlar la salida de esta opción. Así puedes regresar a
                //seguir registrando a alguien en caso de que te bote porque se repita el numero.
                int a;

                int numIdentificacion = -1, searchId = -1, gradoAcademico = -1; //recuerda, nombres descriptivos!
                char nombre[200] = "", institucion[100] = "", temaExpo[200] = "", magistral1 = 'n';

                //do{ comienza ciclo para que no se regrese al menú si ingresaste el mismo numero
                mvprintw(2, col / 2 - 17, "REGISTRO DE EXPOSITORES");
                mvprintw(3, col / 2 - 17, "Número de identificación de expositor: ");
                scanw("%d", &numIdentificacion);

                if (numIdentificacion != -1) //validación de que se haya ingresado un numero
                {
                    //hacemos la búsqueda de expositores
                    for (a = 0; a < expositoresRegistrados; a++) {
                        if (numerosExpositores[a] == numIdentificacion)
                            searchId = a;
                    }
                    if (searchId == -1 || expositoresRegistrados == 0) {
                        numerosExpositores[expositoresRegistrados] = numIdentificacion;
                        mvprintw(4, col / 2 - 17, "Nombre del expositor: ");
                        getstr(nombre); //fgets si lee las cadenas con espacios, scanw no
                        strcpy(nombresExpositores[expositoresRegistrados], nombre);

                        //aquí si voy a usar lo del ciclo por si bota. Vamos a seleccionar el grado
                        //académico con un numero, para tener los tipos de grado normalizados.
                        //Lo que se va a hacer es que se va a guardar el numero y cuando haya que
                        //imprimirlo, solamente vamos a tomar el numero del arreglo de gradosDescripcion
                        //PERO esto tiene el potencial de que lo use Navarro para matar tu programa. Entonces,
                        //hacemos una validación!
                        int cicloGrado = -1; //declaramos la variable para controlar el ciclo
                        do {
                            //limpiamos pantalla para que se vea bonito
                            clear();
                            //imprimimos todo donde iba: 
                            mvprintw(2, col / 2 - 17, "REGISTRO DE EXPOSITORES");
                            mvprintw(3, col / 2 - 17, "Número de identificación de expositor: %d", numIdentificacion);
                            mvprintw(4, col / 2 - 17, "Nombre del expositor: %s", nombre);
                            mvprintw(5, col / 2 - 17, "Grado Académico ");
                            mvprintw(6, col / 2 - 10, "[1] Licenciatura");
                            mvprintw(7, col / 2 - 10, "[2] Maestría");
                            mvprintw(8, col / 2 - 10, "[3] Doctorado\n");
                            scanw("%d", &gradoAcademico);
                            if (gradoAcademico < 0 || gradoAcademico > 2) {
                                mvprintw(9, col / 2 - 17, "ERROR: Grado académico invalido");
                                getch();
                            } else {
                                gradosAcademicos[expositoresRegistrados] = gradoAcademico - 1;
                                cicloGrado = 0;
                            }
                        } while (cicloGrado != 0);
                        mvprintw(9, col / 2 - 17, "Institución del expositor: ");
                        refresh();
                        getstr(institucion);
                        strcpy(instituciones[expositoresRegistrados], institucion);
                        mvprintw(10, col / 2 - 17, "Tema de la conferencia: ");
                        refresh();
                        getstr(temaExpo);
                        strcpy(temas[expositoresRegistrados], temaExpo);
                        //hacemos otra vez lo que hicimos con los grados académicos, pero esta vez
                        //para saber si la conferencia es o no es magistral
                        cicloGrado = -1; //reiniciamos el control del ciclo
                        do {
                            //limpiamos pantalla para que se vea bonito
                            clear();
                            //imprimimos todo donde iba: 
                            mvprintw(2, col / 2 - 17, "REGISTRO DE EXPOSITORES");
                            mvprintw(3, col / 2 - 17, "Numero de identificación de expositor: %d", numIdentificacion);
                            mvprintw(4, col / 2 - 17, "Nombre del expositor: %s", nombre);
                            mvprintw(5, col / 2 - 17, "Grado Académico: %s", gradosDescripciones[gradosAcademicos[expositoresRegistrados]]); //Imprimimos el grado que ya habiamos puesto
                            mvprintw(6, col / 2 - 17, "Institución del expositor: %s", institucion);
                            mvprintw(7, col / 2 - 17, "Tema de la conferencia: %s", temaExpo);
                            mvprintw(8, col / 2 - 17, "Es conferencia magistral [s/n]: ");
                            scanw("%c", &magistral1);
                            if (magistral1 == 's' || magistral1 == 'n' || magistral1 == 'S' || magistral1 == 'N') {

                                switch (magistral1) {
                                        //hacemos nuestro case ignorar mayusculas o minusculas
                                    case 's':
                                    case 'S':
                                        strcpy(magistral[expositoresRegistrados], "Si");
                                        break;
                                    case 'n':
                                    case 'N':
                                        strcpy(magistral[expositoresRegistrados], "No");
                                        break;
                                }
                                cicloGrado = 0;
                            } else {
                                mvprintw(9, col / 2 - 17, "ERROR: Opción invalida");

                            }
                        } while (cicloGrado != 0);
                        expositoresRegistrados++;
                        mvprintw(10, col / 2 - 17, "Registro completado con exito\n");
                    } else {
                        mvprintw(4, col / 2 - 17, "ERROR: Número repetido\n");

                    }

                } else {
                    mvprintw(4, col / 2 - 17, "ERROR: No se ingreso un numero\n");

                }
                //   }while(ex1!=1) fin del ciclo por si ingresaste el numero repetido. Comentado por si 
                //lo quieres poner, could be nice
                getch();
                // </editor-fold>
                break;
            case 2:
                // <editor-fold defaultstate="collapsed" desc="Modificacion">
                clear();
                //vamo a reiniciar las variables
                strcpy(nombre, " ");
                strcpy(institucion, " ");
                strcpy(temaExpo, " ");
                magistral1 = ' ';
                int searchId2 = -1, b, numeroABuscar = -1, menu2Sw = -1;
                if (expositoresRegistrados > 0) {
                    mvprintw(2, col / 2 - 19, "MODIFICACION DE EXPOSITORES");
                    mvprintw(3, col / 2 - 19, "Introduce el numero a buscar: ");
                    scanw("%d", &numeroABuscar);
                    for (b = 0; b < expositoresRegistrados; b++) {
                        if (numerosExpositores[b] == numeroABuscar)
                            searchId2 = b;
                    }
                    if (searchId2 >= 0) {
                        //SI lo encontramos, presentamos los datos y las opciones para modificar
                        do {
                            clear();
                            mvprintw(2, col / 2 - 19, "MODIFICACION DE EXPOSITORES");
                            mvprintw(3, col / 2 - 19, "Expositor #%d", numerosExpositores[searchId2]);
                            mvprintw(4, col / 2 - 19, "Nombre: %s", nombresExpositores[searchId2]);
                            mvprintw(5, col / 2 - 19, "Grado Academico: %s", gradosDescripciones[gradosAcademicos[searchId2]]);
                            mvprintw(6, col / 2 - 19, "Institucion: %s", instituciones[searchId2]);
                            mvprintw(7, col / 2 - 19, "Tema de la exposicion: %s", temas[searchId2]);
                            mvprintw(8, col / 2 - 19, "Es magistral: %s", magistral[searchId2]);
                            mvprintw(10, col / 2 - 15, "[1] Modificar nombre");
                            mvprintw(11, col / 2 - 15, "[2] Modificar grado academico");
                            mvprintw(12, col / 2 - 15, "[3] Modificar institucion");
                            mvprintw(13, col / 2 - 15, "[4] Modificar tema");
                            mvprintw(14, col / 2 - 15, "[5] Modificar magistral");
                            mvprintw(15, col / 2 - 15, "[6] Regresar");
                            scanw("%d", &menu2Sw);
                            switch (menu2Sw) {
                                case 1:
                                    //<editor-fold defaultstate="collapsed" desc="Modificacion del nombre">
                                    clear();
                                    mvprintw(2, col / 2 - 19, "MODIFICACION DE EXPOSITORES");
                                    mvprintw(3, col / 2 - 19, "Introduce el nuevo nombre: ");
                                    getstr(nombre);
                                    strcpy(nombresExpositores[searchId2], nombre);
                                    //</editor-fold>
                                    break;
                                case 2:
                                    //<editor-fold defaultstate="collapsed" desc="Modificacion de grado academico">
                                    clear();
                                    int cicloGrado = -1, gradoAcademico = -1;
                                    do {
                                        mvprintw(2, col / 2 - 19, "MODIFICACION DE EXPOSITORES")
                                        mvprintw(3, col / 2 - 19, "Grado Académico ");
                                        mvprintw(4, col / 2 - 16, "[1] Licenciatura");
                                        mvprintw(5, col / 2 - 16, "[2] Maestría");
                                        mvprintw(6, col / 2 - 16, "[3] Doctorado\n");
                                        scanw("%d", &gradoAcademico);
                                        if (gradoAcademico < 0 || gradoAcademico > 2) {
                                            mvprintw(8, col / 2 - 16, "ERROR: Grado académico invalido");
                                            getch();
                                        } else {
                                            gradosAcademicos[searchId2] = gradoAcademico - 1;
                                            cicloGrado = 0;
                                        }
                                    } while (cicloGrado != 0);
                                    //</editor-fold>
                                    break;
                                case 3:
                                    //<editor-fold defaultstate="collapsed" desc="Modificacion de la institucion">
                                    clear();
                                    mvprintw(2, col / 2 - 19, "MODIFICACION DE EXPOSITORES");
                                    mvprintw(3, col / 2 - 19, "Introduce la institucion: ");
                                    getstr(institucion);
                                    strcpy(instituciones[searchId2], institucion);
                                    //</editor-fold>
                                    break;
                                case 4:
                                    //<editor-fold defaultstate="collapsed" desc="Modificacion del tema">
                                    clear();
                                    mvprintw(2, col / 2 - 19, "MODIFICACION DE EXPOSITORES");
                                    mvprintw(3, col / 2 - 19, "Introduce el tema de la exposicion: ");
                                    scanw("%s", &nombre);
                                    gets(temaExpo);
                                    strcpy(temas[searchId2], temaExpo);
                                    //</editor-fold>
                                    break;
                                case 5:
                                    //<editor-fold defaultstate="collapsed" desc="Modificar si es magistral">
                                    do {
                                        clear();
                                        mvprintw(2, col / 2 - 19, "MODIFICACION DE EXPOSITORES");
                                        cicloGrado = -1; //reiniciamos el control del ciclo
                                        mvprintw(3, col / 2 - 17, "Es conferencia magistral [s/n]: ");
                                        scanw("%c", &magistral1);
                                        if (magistral1 == 's' || magistral1 == 'n' || magistral1 == 'S' || magistral1 == 'N') {

                                            switch (magistral1) {
                                                    //hacemos nuestro case ignorar mayusculas o minusculas
                                                case 's':
                                                case 'S':
                                                    strcpy(magistral[searchId2], "Si");
                                                    break;
                                                case 'n':
                                                case 'N':
                                                    strcpy(magistral[searchId2], "No");
                                                    break;
                                            }
                                            cicloGrado = 0;
                                        } else {
                                            mvprintw(5, col / 2 - 17, "ERROR: Opción invalida");
                                        }
                                    } while (cicloGrado != 0);
                                    //</editor-fold>
                                    break;
                                case 6:
                                    break;
                                default:
                                      mvprintw(4, col / 2 - 19, "ERROR: Opcion invalida");
                                    break;
                            }
                        } while (menu2Sw != 6);
                    } else {
                        mvprintw(4, col / 2 - 19, "ERROR: No existe ese expositor");
                    }
                } else {
                    mvprintw(2, col / 2 - 19, "ERROR: No hay expositores registrados");
                }
                getch();
                //</editor-fold>
                break;
            case 3:
                // <editor-fold defaultstate="collapsed" desc="Bajas">
                clear();
                getch();
                //</editor-fold>
                break;
            case 4:
                // <editor-fold defaultstate="collapsed" desc="Consultas">
                clear();
                getch();
                //</editor-fold>
                break;
            case 5:
                clear();
                break;
            default:
                clear();
                mvprintw(2, col / 2 - 19, "Error: Opción inválida."); //muy importante!! 
                getch();
                break;


        }

    } while (menuOption != 5);
    refresh();
    endwin();
    return 0;
}

