#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string>

using namespace std;

enum class COLORES { VACIO = 0, ROJO, MAGENTA, NARANJA, AMARILLO, VERDE, CIAN, AZUL, VIOLETA };
enum class DIFICULTAD { FACIL = 1, NORMAL, HARDCORE };

/*
* Quería aclarar que parte de la consigna la interprete de la mejor forma que pude entenderlo
* y las que no pude interpretar, las intente hacer de la manera en la que se me fueron ocurriendo
* Por ejemplo: El tema de que cada jugador tenia un papel distinto, no lo llegue a captar del todo
* entonces lo que hice fue hacer que la CPU fuera como un master y genera el código para ambos jugadores
* de forma distinta y aleatoria, esto no se si cambio el objetivo del juego un poco, puesto que ahora
* se convirtió en un carrera entre dos jugadores por descifrar el código de colores, con puntos y 2 fases
* la primera fase trata de adivinar los colores y la segunda de adivinar las posiciones de esos colores.
* nada, quería dejar este comentario acá primero para guiarme en mi enfoque y después para aclarar un poco lo
* que me fue ocurriendo mientras leía las consignas.
*/

void main()
{
	srand(time(NULL));

	// Constantes
	const int constIntentos = 100;
	const int constColor = 6;
	// Arrays
	COLORES arrayColorJugadorUno[constColor] = {}; // Este array contiene los colores que el jugador 1 va descubriendo.
	COLORES arrayColorJugadorDos[constColor] = {}; // Este array contiene los colores que el jugador 2 va descubriendo.
	COLORES arrayClaveUno[constColor] = {}; // Este array contiene el codigo de colores, para el jugador 1.
	COLORES arrayClaveDos[constColor] = {}; // Este array contiene el codigo de colores, para el jugador 2.
	bool arrayPosicionJugadorUno[constColor] = { false, false, false, false, false }; // Este array lo uso para verificar si el jugador 1 descubrio todas las posiciones.
	bool arrayPosicionJugadorDos[constColor] = { false, false, false, false, false }; // Este array lo uso para verificar si el jugador 2 descubrio todas las posiciones.
	char arrayClaveCharJugadorUno[constIntentos] = {}; // Este array lo uso como interfaz para que el usuario sepa como van ambos jugadores.
	char arrayClaveCharJugadorDos[constIntentos] = {}; // Este array lo uso como interfaz para que el usuario sepa como van ambos jugadores.
	// Enteros
	COLORES aux;
	DIFICULTAD auxDif;
	int cantColor = 4; // Es la cantidad de colores que habra en el codigo. (SE PUEDE CONFIGURAR EN EL MENU DE OPCIONES).
	int numeroColor = 0;
	int numeroPosicion = 0;
	int intentos = 12; // Son los turnos totales. (SE PUEDE CONFIGURAR EN EL MENU DE OPCIONES).
	int cantIntentosJugador = 12; // Son los turnos que tiene el jugador 1. (SE PUEDE CONFIGURAR EN EL MENU DE OPCIONES).
	int cantIntentosJugadorDos = 12; // Son los turnos que tiene el jugador 2. (SE PUEDE CONFIGURAR EN EL MENU DE OPCIONES).
	int puntosJugador = 0; // Los puntos que lleva el jugador 1.
	int puntosJugadorDos = 0; // Los puntos que lleva el jugador 2.
	int puntoPrimeraFase = 20; // Son los puntos totales que se necesitan para terminar la primera fase del juego.
	int puntos = 40; // Son los puntos totales que se necesitan para terminar el juego. (SE PUEDE CONFIGURAR EN EL MENU DE OPCIONES).
	int opcion = 0;
	int contador = 0;
	int contadorDos = 0;
	// Booleanos
	bool EsCPU = false; // Marca cuando la logica de la cpu debe aplicarse.
	bool EsValido = true; // Lo uso para validar que ningun color se repita, cuando genero el codigo.
	bool EsCorrecto = false; // Lo uso para saber si el color elegido es correcto o no.
	bool PosicionCorrectas = false; // Lo uso para saber si la posicion elegida es correcta o no.
	bool PosicionesCorrectas = false; // Lo uso para saber si el jugador 1 adivino todas las posiciones.
	bool PosicionesCorrectasDos = false; // Lo uso para saber si el jugador 2 adivino todas las posiciones.
	bool seguir = true; // Esto esta presente en el menu y en el juego y me indica cuando salgo del menu o cuando termina el juego.
	bool EsJugador = true; // Lo uso para saber a que jugador le toca jugar.
	bool auxOpcion = true;
	bool SeguirJugadorUno = false; // Me permite saber si el jugador 1 abandono o no el juego.
	bool SeguirJugadorDos = false; // Me permite saber si el jugador 2 abandono o no el juego.
	bool TerminarJuego = false; // Me permite saber si el juego se termino o no.
	//String
	string nombreColorUno = "";
	string nombreColorDos = "";
	string jugadorUno = "[JUGADOR 1]";
	string jugadorDos = "[JUGADOR 2]";
	string nombreDificultad = "[PERSONALIZADA]";
	string ganador = "";

	do
	{
		system("cls");
		cout << "*********************************************************************" << endl;
		cout << "*                       [MASTERMIND]                                *" << endl;
		cout << "*********************************************************************" << endl;

		cout << "\n --- MENU DE INICIO ---" << endl;
		cout << "1 - EMPEZAR JUEGO\n2 - CONFIGURAR JUEGO\n" << endl;

		// Cuando se ingresa un caracter que no sea int, no se por que entra en bucle infinito, no supe como solucionarlo.
		do
		{
			cout << "SELECCION : ";
			cin >> opcion;
			opcion = (int)opcion;

		} while (opcion < 1 || opcion > 2);

		if (opcion == 2)
		{
			system("cls");
			cout << "*********************************************************************" << endl;
			cout << "*                       [MASTERMIND]                                *" << endl;
			cout << "*********************************************************************" << endl;

			cout << "\n --- MENU PARA CONFIGURAR EL JUEGO ---" << endl;
			cout << "1 - DIFICULTAD (POR DEFECTO FACIL)\n2 - CANTIDAD DE TURNOS (POR DEFECTO 12)\n3 - CANTIDAD DE PUNTOS PARA GANAR (POR DEFECTO DEPENDE DE LA DIFICULTAD)\n4 - VOLVER\n" << endl;

			do
			{

				cout << "SELECCION : ";
				cin >> opcion;

			} while (opcion < 1 || opcion > 4);

			switch (opcion)
			{
			// MODO DE DIFICULTAD
			case 1:

				system("cls");
				cout << "*********************************************************************" << endl;
				cout << "*                       [MASTERMIND]                                *" << endl;
				cout << "*********************************************************************" << endl;

				cout << "\n --- MENU DE DIFICULTADES ---" << endl;
				cout << "[ADVERTENCIA]\n-Si elije un nivel, configuraciones previas como los puntos para ganar y los turnos se adecuaran a la dificultad." << endl;
				cout << "\n1 - FACIL\n2 - NORMAL\n3 - HARDCORE\n4 - VOLVER\n" << endl;
				do
				{

					cout << "SELECCION : ";
					cin >> opcion;

				} while (opcion < 1 || opcion > 4);

				auxDif = (DIFICULTAD)opcion;
				switch (auxDif)
				{
				case DIFICULTAD::FACIL:
					cantColor = 4;
					puntoPrimeraFase = 20;
					puntos = 40;
					cantIntentosJugador = 12;
					cantIntentosJugadorDos = 12;
					intentos = 12;
					nombreDificultad = "[FACIL]";
					break;
				case DIFICULTAD::NORMAL:
					cantColor = 5;
					puntoPrimeraFase = 25;
					puntos = 50;
					cantIntentosJugador = 14;
					cantIntentosJugadorDos = 14;
					intentos = 14;
					nombreDificultad = "[NORMAL]";
					break;
				case DIFICULTAD::HARDCORE:
					cantColor = 6;
					puntoPrimeraFase = 30;
					puntos = 60;
					cantIntentosJugador = 16;
					cantIntentosJugadorDos = 16;
					intentos = 16;
					nombreDificultad = "[HARDCORE]";
					break;
				default:
					break;
				}

				break;
			// CANTIDAD DE TURNOS
			case 2:
				system("cls");
				cout << "*********************************************************************" << endl;
				cout << "*                       [MASTERMIND]                                *" << endl;
				cout << "*********************************************************************" << endl;

				cout << "\n --- MENU DE TURNOS ---" << endl;
				cout << "INGRESE CUANTOS TURNOS HABRA EN EL JUEGO (MINIMO DE 12 - MAX 100)." << endl;
				do
				{

					cout << "SELECCION : ";
					cin >> opcion;

				} while (opcion < 12 || opcion > 100);

				cantIntentosJugador = opcion;
				cantIntentosJugadorDos = opcion;
				intentos = opcion;

				break;
			// CANTIDAD DE PUNTOS PARA GANAR
			case 3:
				system("cls");
				cout << "*********************************************************************" << endl;
				cout << "*                       [MASTERMIND]                                *" << endl;
				cout << "*********************************************************************" << endl;

				cout << "\n --- MENU DE PUNTOS ---" << endl;
				cout << "INGRESE CUANTOS PUNTOS HABRA EN EL JUEGO PARA GANARLO (MINIMO DE 20)." << endl;
				do
				{

					cout << "SELECCION : ";
					cin >> opcion;

				} while (opcion < 20);

				puntos = opcion;
				puntoPrimeraFase = puntos / 2;

				break;
			default:
				break;
			}
		}
		else
		{
			seguir = false;
		}

	} while (seguir);


	// Le doy valores vacio a mi array de char.
	for (int i = 0; i < intentos; i++)
	{
		arrayClaveCharJugadorUno[i] = ' ';
		arrayClaveCharJugadorDos[i] = ' ';
	}

	// Le doy valores al array que contiene la clave para el jugador 1.
	for (int i = 0; i < cantColor; i++)
	{
		// Valido que no se repita ningun color e inserto el color en la posicion correspondiente.
		do
		{
			aux = (COLORES)(rand() % 8 + 1);
			for (int i = 0; i < cantColor; i++)
			{
				if (arrayClaveUno[i] == aux)
				{
					EsValido = true;
					break;
				}
				else if (arrayClaveUno[i] == COLORES::VACIO)
				{
					arrayClaveUno[i] = aux;
					EsValido = false;
					break;
				}
			}
		} while (EsValido);
	}

	// Le doy valores al array que contiene la clave para el jugador 2.
	for (int i = 0; i < cantColor; i++)
	{
		// Valido que no se repita ningun color e inserto el color en la posicion correspondiente.
		do
		{
			aux = (COLORES)(rand() % 8 + 1);
			for (int i = 0; i < cantColor; i++)
			{
				if (arrayClaveDos[i] == aux)
				{
					EsValido = true;
					break;
				}
				else if (arrayClaveDos[i] == COLORES::VACIO)
				{
					arrayClaveDos[i] = aux;
					EsValido = false;
					break;
				}
			}
		} while (EsValido);
	}

	seguir = true;
	// Inicio del juego
	do
	{
		// Abandono el jugador 1.
		if (SeguirJugadorUno)
		{
			EsJugador = false;
		}
		// Abandono el jugador 2.
		else if (SeguirJugadorDos)
		{
			EsJugador = true;
		}

		// Ambos jugadores se fueron.
		if (SeguirJugadorDos && SeguirJugadorUno)
		{
			TerminarJuego = true;
		}

		// JUGADOR NUMERO 1
		if (!TerminarJuego)
		{
			if (EsJugador)
			{
				//PRIMERA FASE, DESCUBRIR LOS COLORES
				if (puntosJugador < puntoPrimeraFase)
				{
					system("cls");
					cout << "*********************************************************************" << endl;
					cout << "*                       [MASTERMIND]                                *" << endl;
					cout << "*********************************************************************" << endl;

					// "Hud" para mostrar cuando el Jugador y el jugador 2 responde incorrectamente o responde correctamente.
					cout << "\nDIFICULTAD DEL CODIGO : " << nombreDificultad << endl;
					cout << "\nPUNTOS : " << puntosJugador << " - RESPUESTAS " << jugadorUno << " : ";
					for (int i = 0; i < intentos; i++)
					{
						if (arrayClaveCharJugadorUno[i] != ' ')
						{
							cout << " " << arrayClaveCharJugadorUno[i];
						}

						if (i == intentos - 1)
						{
							// Muestro info por pantalla si el jugador 1, abandono el juego.
							if (SeguirJugadorUno)
							{
								cout << (SeguirJugadorUno == true ? "  -> EL " + jugadorUno + " ABANDONO" : "") << endl;
							}
							else
							{
								cout << (puntosJugador == puntoPrimeraFase ? "  -> EL " + jugadorUno + " TERMINO PRIMERA FASE" : "") << endl;
							}							
						}
					}

					cout << "PUNTOS : " << puntosJugadorDos << " - RESPUESTAS " << jugadorDos << " : ";
					for (int i = 0; i < intentos; i++)
					{
						if (arrayClaveCharJugadorDos[i] != ' ')
						{
							cout << " " << arrayClaveCharJugadorDos[i];
						}

						if (i == intentos - 1)
						{
							// Muestro info por pantalla si el jugador 2, abandono el juego.
							if (SeguirJugadorDos)
							{
								cout << (SeguirJugadorDos == true ? "  -> EL " + jugadorDos + " ABANDONO" : "") << endl;
							}
							else
							{
								cout << (puntosJugadorDos == puntoPrimeraFase ? "  -> EL " + jugadorDos + " TERMINO PRIMERA FASE" : "") << endl;
							}							
						}
					}

					// HUD para el jugador 1
					cout << "\n" << jugadorUno << " TURNOS RESTANTES [" << cantIntentosJugador << "] - COLOR USADO ANTES " << (nombreColorUno == "" ? "[NINGUNO]" : nombreColorUno);


					// Este es mi menu de opciones, para el jugador 1.
					cout << "\n" << jugadorUno << " ELIJA UN COLOR :\n1 - ROJO\n2 - MAGENTA\n3 - NARANJA\n4 - AMARILLO\n5 - VERDER\n6 - CIAN\n7 - AZUL\n8 - VIOLETA" << endl;
					do
					{
						cout << "SELECCION : ";
						cin >> opcion;
					} while (opcion < 1 || opcion > 8);
				}
				// SEGUNDA FASE, DESCRUBRIR LAS POSICIONES DE LOS COLORES
				else
				{
					system("cls");
					cout << "*********************************************************************" << endl;
					cout << "*                       [MASTERMIND]                                *" << endl;
					cout << "*********************************************************************" << endl;

					// "Hud" para mostrar cuando el Jugador y el jugador 2 responde incorrectamente o responde correctamente.
					cout << "\nDIFICULTAD DEL CODIGO : " << nombreDificultad << endl;
					cout << "\nPUNTOS : " << puntosJugador << " - RESPUESTAS " << jugadorUno << " : ";
					for (int i = 0; i < intentos; i++)
					{
						if (arrayClaveCharJugadorUno[i] != ' ')
						{
							cout << " " << arrayClaveCharJugadorUno[i];
						}

						if (i == intentos - 1)
						{
							// Muestro info por pantalla si el jugador 1, abandono el juego.
							if (SeguirJugadorUno)
							{
								cout << (SeguirJugadorUno == true ? "  -> EL " + jugadorUno + " ABANDONO" : "") << endl;
							}
							else
							{
								cout << (puntosJugador == puntoPrimeraFase ? "  -> EL " + jugadorUno + " TERMINO PRIMERA FASE" : "") << endl;
							}
						}
					}

					cout << "PUNTOS : " << puntosJugadorDos << " - RESPUESTAS " << jugadorDos << " : ";
					for (int i = 0; i < intentos; i++)
					{
						if (arrayClaveCharJugadorDos[i] != ' ')
						{
							cout << " " << arrayClaveCharJugadorDos[i];
						}

						if (i == intentos - 1)
						{
							// Muestro info por pantalla si el jugador 2, abandono el juego.
							if (SeguirJugadorDos)
							{
								cout << (SeguirJugadorDos == true ? "  -> EL " + jugadorDos + " ABANDONO" : "") << endl;
							}
							else
							{
								cout << (puntosJugadorDos == puntoPrimeraFase ? "  -> EL " + jugadorDos + " TERMINO PRIMERA FASE" : "") << endl;
							}
						}
					}

					// HUD para el jugador 1.
					cout << "\n" << jugadorUno << " TURNOS RESTANTES [" << cantIntentosJugador << "] ";

					// Muestro el orden en que el jugador va posicionado correctamente los colores.
					cout << "\nCOLORES POSICIONADOS : " << endl;
					for (int i = 0; i < cantColor; i++)
					{
						if (arrayPosicionJugadorUno[i])
						{
							switch (arrayColorJugadorUno[i])
							{
							case COLORES::ROJO:
								nombreColorUno = "[ROJO]";
								break;
							case COLORES::MAGENTA:
								nombreColorUno = "[MAGENTA]";
								break;
							case COLORES::NARANJA:
								nombreColorUno = "[NARANJA]";
								break;
							case COLORES::AMARILLO:
								nombreColorUno = "[AMARILLO]";
								break;
							case COLORES::VERDE:
								nombreColorUno = "[VERDE]";
								break;
							case COLORES::CIAN:
								nombreColorUno = "[CIAN]";
								break;
							case COLORES::AZUL:
								nombreColorUno = "[AZUL]";
								break;
							case COLORES::VIOLETA:
								nombreColorUno = "[VIOLETA]";
								break;
							}

							cout << " " << i + 1 << " - " << nombreColorUno << "\n";
						}
					}

					// Muestro el orden en que el jugador fue sacando los colores.
					cout << "\nCOLORES DESCUBIERTOS" << endl;
					for (int i = 0; i < cantColor; i++)
					{
						// Solo va a mostrar los colores que aun no se sabe su posicion.
						if (!arrayPosicionJugadorUno[i])
						{
							switch (arrayColorJugadorUno[i])
							{
							case COLORES::ROJO:
								nombreColorUno = "[ROJO]";
								break;
							case COLORES::MAGENTA:
								nombreColorUno = "[MAGENTA]";
								break;
							case COLORES::NARANJA:
								nombreColorUno = "[NARANJA]";
								break;
							case COLORES::AMARILLO:
								nombreColorUno = "[AMARILLO]";
								break;
							case COLORES::VERDE:
								nombreColorUno = "[VERDE]";
								break;
							case COLORES::CIAN:
								nombreColorUno = "[CIAN]";
								break;
							case COLORES::AZUL:
								nombreColorUno = "[AZUL]";
								break;
							case COLORES::VIOLETA:
								nombreColorUno = "[VIOLETA]";
								break;
							}
							cout << " " << (int)arrayColorJugadorUno[i] << " - " << nombreColorUno << "\n";
						}
					}

					cout << "\n" << jugadorUno << " ELIJA UN COLOR (DE LOS DESCUBIERTOS) Y LA POSICION DONDE CREE QUE ESTA." << endl;
					do
					{
						auxOpcion = true;

						cout << "NUMERO DE COLOR : ";
						cin >> numeroColor;

						// Voy a validar que el jugador no pueda elejir un numero de color que antes ya habia elegido.
						for (int i = 0; i < cantColor; i++)
						{
							// voy descontando los indice donde la posicion ha sido descubierta.
							if (!arrayPosicionJugadorUno[i])
							{
								if ((int)arrayColorJugadorUno[i] == numeroColor)
								{
									auxOpcion = false;

									break;
								}
							}
						}

					} while (auxOpcion);

					do
					{
						cout << "NUMERO DE POSICION (1-" << cantColor  << "): ";
						cin >> numeroPosicion;
					} while (numeroPosicion < 1 || numeroPosicion > cantColor);

				}

				EsCPU = true;

			}
			// JUGADOR NUMERO 2
			else if (!EsJugador)
			{
				//PRIMERA FASE, DESCUBRIR LOS COLORES
				if (puntosJugadorDos < puntoPrimeraFase)
				{
					system("cls");
					cout << "*********************************************************************" << endl;
					cout << "*                       [MASTERMIND]                                *" << endl;
					cout << "*********************************************************************" << endl;

					// "Hud" para mostrar cuando el Jugador y el jugador 2 responde incorrectamente o responde correctamente.
					cout << "\nDIFICULTAD DEL CODIGO : " << nombreDificultad << endl;
					cout << "\nPUNTOS : " << puntosJugador << " - RESPUESTAS " << jugadorUno << " : ";
					for (int i = 0; i < intentos; i++)
					{
						if (arrayClaveCharJugadorUno[i] != ' ')
						{
							cout << " " << arrayClaveCharJugadorUno[i];
						}

						if (i == intentos - 1)
						{
							// Muestro info por pantalla si el jugador 1, abandono el juego.
							if (SeguirJugadorUno)
							{
								cout << (SeguirJugadorUno == true ? "  -> EL " + jugadorUno + " ABANDONO" : "") << endl;
							}
							else
							{
								cout << (puntosJugador == puntoPrimeraFase ? "  -> EL " + jugadorUno + " TERMINO PRIMERA FASE" : "") << endl;
							}
						}
					}

					cout << "PUNTOS : " << puntosJugadorDos << " - RESPUESTAS " << jugadorDos << " : ";
					for (int i = 0; i < intentos; i++)
					{
						if (arrayClaveCharJugadorDos[i] != ' ')
						{
							cout << " " << arrayClaveCharJugadorDos[i];
						}

						if (i == intentos - 1)
						{
							// Muestro info por pantalla si el jugador 2, abandono el juego.
							if (SeguirJugadorDos)
							{
								cout << (SeguirJugadorDos == true ? "  -> EL " + jugadorDos + " ABANDONO" : "") << endl;
							}
							else
							{
								cout << (puntosJugadorDos == puntoPrimeraFase ? "  -> EL " + jugadorDos + " TERMINO PRIMERA FASE" : "") << endl;
							}
						}
					}

					// HUD para el jugador 2.
					cout << "\n" <<  jugadorDos << " TURNOS RESTANTES [" << cantIntentosJugadorDos << "] - COLOR USADO ANTES " << (nombreColorDos == "" ? "[NINGUNO]" : nombreColorDos);

					// Este es mi menu de opciones.
					cout << "\n" << jugadorDos << " ELIJA UN COLOR :\n1 - ROJO\n2 - MAGENTA\n3 - NARANJA\n4 - AMARILLO\n5 - VERDER\n6 - CIAN\n7 - AZUL\n8 - VIOLETA" << endl;
					do
					{
						cout << "SELECCION : ";
						cin >> opcion;
					} while (opcion < 1 || opcion > 8);
				}
				// SEGUNDA FASE, DESCRUBRIR LAS POSICIONES DE LOS COLORES
				else
				{
					system("cls");
					cout << "*********************************************************************" << endl;
					cout << "*                       [MASTERMIND]                                *" << endl;
					cout << "*********************************************************************" << endl;

					// "Hud" para mostrar cuando el Jugador y el jugador 2 responde incorrectamente o responde correctamente.
					cout << "\nDIFICULTAD DEL CODIGO : " << nombreDificultad << endl;
					cout << "\nPUNTOS : " << puntosJugador << " - RESPUESTAS " << jugadorUno << " : ";
					for (int i = 0; i < intentos; i++)
					{
						if (arrayClaveCharJugadorUno[i] != ' ')
						{
							cout << " " << arrayClaveCharJugadorUno[i];
						}

						if (i == intentos - 1)
						{
							// Muestro info por pantalla si el jugador 1, abandono el juego.
							if (SeguirJugadorUno)
							{
								cout << (SeguirJugadorUno == true ? "  -> EL " + jugadorUno + " ABANDONO" : "") << endl;
							}
							else
							{
								cout << (puntosJugador == puntoPrimeraFase ? "  -> EL " + jugadorUno + " TERMINO PRIMERA FASE" : "") << endl;
							}
						}
					}

					cout << "PUNTOS : " << puntosJugadorDos << " - RESPUESTAS " << jugadorDos << " : ";
					for (int i = 0; i < intentos; i++)
					{
						if (arrayClaveCharJugadorDos[i] != ' ')
						{
							cout << " " << arrayClaveCharJugadorDos[i];
						}

						if (i == intentos - 1)
						{
							// Muestro info por pantalla si el jugador 2, abandono el juego.
							if (SeguirJugadorDos)
							{
								cout << (SeguirJugadorDos == true ? "  -> EL " + jugadorDos + " ABANDONO" : "") << endl;
							}
							else
							{
								cout << (puntosJugadorDos == puntoPrimeraFase ? "  -> EL " + jugadorDos + " TERMINO PRIMERA FASE" : "") << endl;
							}
						}
					}

					// HUD para el jugador 2, solo lo veria el en teoria.
					cout << jugadorDos << " TURNOS RESTANTES [" << cantIntentosJugadorDos << "]" << endl;

					// Muestro el orden en que el jugador va posicionado correctamente los colores.
					cout << "\nCOLORES POSICIONADOS : " << endl;
					for (int i = 0; i < cantColor; i++)
					{
						if (arrayPosicionJugadorDos[i])
						{
							switch (arrayColorJugadorDos[i])
							{
							case COLORES::ROJO:
								nombreColorDos = "[ROJO]";
								break;
							case COLORES::MAGENTA:
								nombreColorDos = "[MAGENTA]";
								break;
							case COLORES::NARANJA:
								nombreColorDos = "[NARANJA]";
								break;
							case COLORES::AMARILLO:
								nombreColorDos = "[AMARILLO]";
								break;
							case COLORES::VERDE:
								nombreColorDos = "[VERDE]";
								break;
							case COLORES::CIAN:
								nombreColorDos = "[CIAN]";
								break;
							case COLORES::AZUL:
								nombreColorDos = "[AZUL]";
								break;
							case COLORES::VIOLETA:
								nombreColorDos = "[VIOLETA]";
								break;
							}

							cout << " " << i + 1 << " - " << nombreColorDos << "\n";
						}
					}

					// Muestro el orden en que el jugador fue sacando los colores.
					cout << "\nCOLORES DESCUBIERTOS" << endl;
					for (int i = 0; i < cantColor; i++)
					{
						// Solo va a mostrar los colores que aun no se sabe su posicion.
						if (!arrayPosicionJugadorDos[i])
						{
							switch (arrayColorJugadorDos[i])
							{
							case COLORES::ROJO:
								nombreColorDos = "[ROJO]";
								break;
							case COLORES::MAGENTA:
								nombreColorDos = "[MAGENTA]";
								break;
							case COLORES::NARANJA:
								nombreColorDos = "[NARANJA]";
								break;
							case COLORES::AMARILLO:
								nombreColorDos = "[AMARILLO]";
								break;
							case COLORES::VERDE:
								nombreColorDos = "[VERDE]";
								break;
							case COLORES::CIAN:
								nombreColorDos = "[CIAN]";
								break;
							case COLORES::AZUL:
								nombreColorDos = "[AZUL]";
								break;
							case COLORES::VIOLETA:
								nombreColorDos = "[VIOLETA]";
								break;
							}
							cout << " " << (int)arrayColorJugadorDos[i] << " - " << nombreColorDos << "\n";
						}
					}

					cout << "\n" << jugadorDos << " ELIJA UN COLOR (DE LOS DESCUBIERTOS) Y LA POSICION DONDE CREE QUE ESTA." << endl;
					do
					{
						auxOpcion = true;

						cout << "NUMERO DE COLOR : ";
						cin >> numeroColor;

						// Voy a validar que el jugador no pueda elejir un numero de color que antes ya habia elegido.
						for (int i = 0; i < cantColor; i++)
						{
							// voy descontando los indice donde la posicion ha sido descubierta.
							if (!arrayPosicionJugadorDos[i])
							{
								if ((int)arrayColorJugadorDos[i] == numeroColor)
								{
									auxOpcion = false;

									break;
								}
							}
						}

					} while (auxOpcion);

					do
					{
						cout << "NUMERO DE POSICION (1-" << cantColor << "): ";
						cin >> numeroPosicion;
					} while (numeroPosicion < 1 || numeroPosicion > cantColor);

				}

				EsCPU = true;
			}


			// CPU, logica de la cpu.
			if (EsCPU)
			{
				//CPU, logica para el jugador 1.
				if (EsJugador)
				{
					//PRIMERA FASE, DESCUBRIR LOS COLORES
					if (puntosJugador < puntoPrimeraFase)
					{
						aux = (COLORES)opcion;
						auxOpcion = true;
						EsCorrecto = false;

						// Valido si el color seleccionado esta presente en el array clave y en el array color.
						for (int i = 0; i < cantColor; i++)
						{
							// En el caso de que el jugador haya seleccionado un color ya existente, este lo tomara como incorrecto.
							if (arrayColorJugadorUno[i] == aux)
							{
								auxOpcion = false;
							}
						}
						// array clave, solo lo valido en el caso en donde el color seleccionado no sea uno repetido, si se repite EsCorrecto = false.
						if (auxOpcion)
						{
							for (int i = 0; i < cantColor; i++)
							{
								if (arrayClaveUno[i] == aux)
								{
									arrayColorJugadorUno[contador] = aux;
									EsCorrecto = true;
									puntosJugador += (puntos / (cantColor * 2));
									contador++;
								}

								// En el caso de que el color eleijo sea correcto, salgo del for.
								if (EsCorrecto)
								{
									break;
								}
							}
						}

						// Le doy valor a mi array de char que contiene las respuesta que lleva el jugador.
						for (int i = 0; i < intentos; i++)
						{
							if (arrayClaveCharJugadorUno[i] == ' ')
							{
								if (EsCorrecto)
								{
									arrayClaveCharJugadorUno[i] = 'O';									
								}
								else
								{
									arrayClaveCharJugadorUno[i] = 'X';
								}

								break;
							}
						}

						switch (aux)
						{
						case COLORES::ROJO:
							nombreColorUno = "[ROJO]";
							break;
						case COLORES::MAGENTA:
							nombreColorUno = "[MAGENTA]";
							break;
						case COLORES::NARANJA:
							nombreColorUno = "[NARANJA]";
							break;
						case COLORES::AMARILLO:
							nombreColorUno = "[AMARILLO]";
							break;
						case COLORES::VERDE:
							nombreColorUno = "[VERDE]";
							break;
						case COLORES::CIAN:
							nombreColorUno = "[CIAN]";
							break;
						case COLORES::AZUL:
							nombreColorUno = "[AZUL]";
							break;
						case COLORES::VIOLETA:
							nombreColorUno = "[VIOLETA]";
							break;
						}

						system("cls");
						// Respuesta del CPU.
						cout << (EsCorrecto == true ? "EL COLOR ELEGIDO POR EL JUGADOR ES CORRECTO 'O'..." : "EL COLOR ELEGIDO POR EL JUGADOR NO ES CORRECTO 'X'...");
						Sleep(3500);

					}
					// SEGUNDA FASE, DESCRUBRIR LAS POSICIONES DE LOS COLORES
					else
					{
						// El CPU va a recorrer el arrayColor para validar la posiciones.
						int auxContador = 0;
						for (int i = 0; i < cantColor; i++)
						{
							// Primero busco el color que eligio el jugador para validar la posicion despues.
							if ((int)arrayColorJugadorUno[i] == numeroColor)
							{
								aux = arrayColorJugadorUno[i];
								auxContador = i;
							}
						}

						for (int i = 0; i < cantColor; i++)
						{
							// Segundo valido la posicion del color obtenido antes.
							if (aux == arrayClaveUno[i])
							{
								// Con un boolean devuelvo si la posicion es correcta o no.
								if (i == (numeroPosicion - 1))
								{
									arrayPosicionJugadorUno[i] = true;
									// Voy guardando los colores en la posicion ordenadamente.
									aux = arrayColorJugadorUno[i];
									arrayColorJugadorUno[i] = arrayClaveUno[i];
									// Voy ordenando los colores del arrayColorJugador intercambiando posiciones
									arrayColorJugadorUno[auxContador] = aux;
									PosicionCorrectas = true;
									puntosJugador += (puntos / (cantColor * 2));
								}
								else
								{
									arrayPosicionJugadorUno[i] = false;
									PosicionCorrectas = false;
								}

								break;
							}
						}

						system("cls");
						// Respuesta del CPU.
						cout << (PosicionCorrectas == true ? "LA POSICION QUE EL [JUGADOR] ELIGIO ES CORRECTA" : "LA POSICION QUE EL [JUGADOR] ELIGIO NO ES CORRECTA") << endl;
						Sleep(3500);
					}

					cantIntentosJugador--;

					if (puntosJugador < puntos)
					{
						cout << "\nCPU PREGUNTA : " << jugadorUno << " DESEA SEGUIR JUGANDO ? 1-SI/2-NO" << endl;
						do
						{
							cout << "SELECCION : ";
							cin >> opcion;

						} while (opcion < 1 || opcion > 2);

						if (opcion == 2)
						{
							SeguirJugadorUno = true;
						}
						else
						{
							SeguirJugadorUno = false;
							EsJugador = false;
						}
					}
					system("cls");
				}
				//CPU, logica para el jugador 2.
				else
				{
					//PRIMERA FASE, DESCUBRIR LOS COLORES
					if (puntosJugadorDos < puntoPrimeraFase)
					{
						aux = (COLORES)opcion;
						auxOpcion = true;
						EsCorrecto = false;

						// Valido si el color seleccionado esta presente en el array clave y en el array color.
						for (int i = 0; i < cantColor; i++)
						{
							// En el caso de que el jugador haya seleccionado un color ya existente, este lo tomara como incorrecto.
							if (arrayColorJugadorDos[i] == aux)
							{
								auxOpcion = false;
							}
						}
						// array clave, solo lo valido en el caso en donde el color seleccionado no sea uno repetido, si se repite EsCorrecto = false.
						if (auxOpcion)
						{
							for (int i = 0; i < cantColor; i++)
							{
								if (arrayClaveDos[i] == aux)
								{

									arrayColorJugadorDos[contadorDos] = aux;
									EsCorrecto = true;
									puntosJugadorDos += (puntos / (cantColor * 2));
									contadorDos++;

								}

								// En el caso de que el color eleijo sea correcto, salgo del for.
								if (EsCorrecto)
								{
									break;
								}
							}
						}

						// Le doy valor a mi array de char que contiene las respuesta que lleva el jugador.
						for (int i = 0; i < intentos; i++)
						{
							if (arrayClaveCharJugadorDos[i] == ' ')
							{
								if (EsCorrecto)
								{
									arrayClaveCharJugadorDos[i] = 'O';									
								}
								else
								{
									arrayClaveCharJugadorDos[i] = 'X';
								}

								break;
							}
						}

						switch (aux)
						{
						case COLORES::ROJO:
							nombreColorDos = "[ROJO]";
							break;
						case COLORES::MAGENTA:
							nombreColorDos = "[MAGENTA]";
							break;
						case COLORES::NARANJA:
							nombreColorDos = "[NARANJA]";
							break;
						case COLORES::AMARILLO:
							nombreColorDos = "[AMARILLO]";
							break;
						case COLORES::VERDE:
							nombreColorDos = "[VERDE]";
							break;
						case COLORES::CIAN:
							nombreColorDos = "[CIAN]";
							break;
						case COLORES::AZUL:
							nombreColorDos = "[AZUL]";
							break;
						case COLORES::VIOLETA:
							nombreColorDos = "[VIOLETA]";
							break;
						}

						system("cls");
						// Respuesta del CPU.
						cout << (EsCorrecto == true ? "EL COLOR ELEGIDO POR EL JUGADOR ES CORRECTO 'O'..." : "EL COLOR ELEGIDO POR EL JUGADOR NO ES CORRECTO 'X'...");
						Sleep(3500);

					}
					// SEGUNDA FASE, DESCRUBRIR LAS POSICIONES DE LOS COLORES
					else
					{
						// El CPU va a recorrer el arrayColor para validar la posiciones.
						int auxContador = 0;
						for (int i = 0; i < cantColor; i++)
						{
							// Primero busco el color que eligio el jugador para validar la posicion despues.
							if ((int)arrayColorJugadorDos[i] == numeroColor)
							{
								aux = arrayColorJugadorDos[i];
								auxContador = i;
							}
						}

						for (int i = 0; i < cantColor; i++)
						{
							// Segundo valido la posicion del color obtenido antes.
							if (aux == arrayClaveDos[i])
							{
								// Con un boolean devuelvo si la posicion es correcta o no.
								if (i == (numeroPosicion - 1))
								{
									arrayPosicionJugadorDos[i] = true;
									// Voy guardando los colores en la posicion ordenadamente.
									aux = arrayColorJugadorDos[i];
									arrayColorJugadorDos[i] = arrayClaveDos[i];
									// Voy ordenando los colores del arrayColorJugador intercambiando posiciones
									arrayColorJugadorDos[auxContador] = aux;
									PosicionCorrectas = true;
									puntosJugadorDos += (puntos / (cantColor * 2));
								}
								else
								{
									arrayPosicionJugadorDos[i] = false;
									PosicionCorrectas = false;
								}

								break;
							}
						}

						system("cls");
						// Respuesta del CPU.
						cout << (PosicionCorrectas == true ? "LA POSICION QUE EL [JUGADOR] ELIGIO ES CORRECTA" : "LA POSICION QUE EL [JUGADOR] ELIGIO NO ES CORRECTA") << endl;
						Sleep(3500);
					}

					cantIntentosJugadorDos--;

					if (puntosJugadorDos < puntos)
					{
						cout << "\nCPU PREGUNTA : " << jugadorDos << " DESEA SEGUIR JUGANDO ? 1-SI/2-NO" << endl;
						do
						{
							cout << "SELECCION : ";
							cin >> opcion;

						} while (opcion < 1 || opcion > 2);

						if (opcion == 2)
						{							
							SeguirJugadorDos = true;
						}
						else
						{
							SeguirJugadorDos = false;
							EsJugador = true;
						}
					}
					system("cls");
				}

			}

			// Valido las posiciones para saber si el jugador 1 adivino las posiciones de todos los colores.
			for (int i = 0; i < cantColor; i++)
			{
				if (arrayPosicionJugadorUno[i])
				{
					PosicionesCorrectas = true;
				}
				else
				{
					// En caso de tener un false, el array significa que aun no termino de descubrir todas las posiciones.
					PosicionesCorrectas = false;
					break;
				}
			}

			// Valido las posiciones para saber si el jugador 2 adivino las posiciones de todos los colores.
			for (int i = 0; i < cantColor; i++)
			{
				if (arrayPosicionJugadorDos[i])
				{
					PosicionesCorrectasDos = true;
				}
				else
				{
					// En caso de tener un false, el array significa que aun no termino de descubrir todas las posiciones.
					PosicionesCorrectasDos = false;
					break;
				}
			}
		} // If para terminar el juego.


		// Valido condicion para ganar o perder.		
		if (TerminarJuego) // Si ambos se van del juego.
		{
			ganador = "[ABANDONO DE AMBOS]";;
			seguir = false;
		}
		else if(PosicionesCorrectas) // Si el jugador 1 termina el juego completo.
		{
			ganador = jugadorUno;
			seguir = false;
		}
		else if(PosicionesCorrectasDos) // Si el jugador 2 termina el juego completo.
		{
			ganador = jugadorDos;
			seguir = false;
		}
		else if (puntosJugador == puntos) // Si el jugador 1 alcanza los puntos maximos.
		{
			ganador = jugadorUno;
			seguir = false;
		}
		else if (puntosJugadorDos == puntos) // Si el jugador 2 alcanza los puntos maximos.
		{
			ganador = jugadorDos;
			seguir = false;
		}
		else if (cantIntentosJugador == 0 && cantIntentosJugadorDos == 0) // Si ambos jugadores se quedan sin turnos para jugar.
		{
			ganador = "[NINGUNO]";
			seguir = false;
		}

	} while (seguir);

	// Acá muestro las estadisticas del juego, de ambos jugadores.
	system("cls");
	cout << "**********************************************************************" << endl;
	cout << "*                       [MASTERMIND]                                 *" << endl;
	cout << "*                                                                    *" << endl;
	cout << "* - [INFORMACION DEL JUGADOR 1]                                      * " << endl;
	cout << "* - PUNTOS OBTENIDOS : " << puntosJugador << "                                            *" << endl;
	cout << "* - INTENTOS USADOS : " << (intentos - cantIntentosJugador) << "                                              *" << endl;
	cout << "* - INTENTOS RESTANTES : " << cantIntentosJugador << "                                           *" << endl;
	cout << "* - EL JUGADOR LOGRO DESIFRAR EL CODIGO : " << (puntosJugador >= puntoPrimeraFase ? "SI" : "NO") << "                         *" << endl;
	cout << "* - EL JUGADOR LOGRO DESIFRAR LAS POSICIONES : " << (PosicionesCorrectas == true ? "SI" : "NO") << "                    *" << endl;
	cout << "*                                                                    *" << endl;
	cout << "*                                                                    *" << endl;
	cout << "* - [INFORMACION DEL JUGADOR 2]                                      * " << endl;
	cout << "* - PUNTOS OBTENIDOS : " << puntosJugadorDos << "                                             *" << endl;
	cout << "* - INTENTOS USADOS : " << (intentos - cantIntentosJugadorDos) << "                                              *" << endl;
	cout << "* - INTENTOS RESTANTES : " << cantIntentosJugadorDos << "                                          *" << endl;
	cout << "* - EL JUGADOR LOGRO DESIFRAR EL CODIGO : " << (puntosJugadorDos >= puntoPrimeraFase ? "SI" : "NO") << "                         *" << endl;
	cout << "* - EL JUGADOR LOGRO DESIFRAR LAS POSICIONES : " << (PosicionesCorrectasDos == true ? "SI" : "NO") << "                    *" << endl;
	cout << "*                                                                    *" << endl;
	cout << "*                                                                    *" << endl;
	cout << "* - EL JUGADOR GANADOR ES :  " << ganador << "                              *" << endl;
	cout << "*                                                                    *" << endl;
	cout << "**********************************************************************" << endl;

	system("pause");
}