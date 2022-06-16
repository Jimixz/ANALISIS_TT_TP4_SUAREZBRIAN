//#include <iostream>
//#include <time.h>
//#include <Windows.h>
//#include <string>
//
//using namespace std;
//
//enum class COLORES { VACIO = 0, ROJO, MAGENTA, NARANJA, AMARILLO, VERDE, CIAN, AZUL, VIOLETA };
//
//void main()
//{
//	srand(time(NULL));
//
//	// Constantes
//	const int cantColor = 5;
//	const int intentos = 10;
//	// Arrays
//	COLORES arrayColorJugador[cantColor] = {};
//	COLORES arrayClave[cantColor] = {};
//	bool arrayPosicionColor[cantColor] = { false, false, false, false, false };
//	char arrayClaveCharJugador[intentos] = {};
//	// Enteros
//	COLORES aux;
//	int numeroColor = 0;
//	int numeroPosicion = 0;
//	int cantIntentosJugador = 15;
//	int puntosCPU = 0;
//	int puntosJugador = 0;
//	int opcion = 0;
//	int contador = 0;
//	// Booleanos
//	bool EsValido = true;
//	bool EsCorrecto = false;
//	bool PosicionCorrectas = false;
//	bool PosicionesCorrectas = false;
//	bool seguir = true;
//	bool EsJugador = true;
//	bool auxOpcion = true;
//	//String
//	string nombreColor = "";
//
//	// Le doy valores vacio a mi array de char.
//	for (int i = 0; i < intentos; i++)
//	{
//		arrayClaveCharJugador[i] = ' ';
//	}
//
//	// Le doy valores al array que contiene la clave.
//	for (int i = 0; i < cantColor; i++)
//	{
//		// Valido que no se repita ningun color e inserto el color en la posicion correspondiente.
//		do
//		{
//			aux = (COLORES)(rand() % 8 + 1);
//			for (int i = 0; i < cantColor; i++)
//			{
//				if (arrayClave[i] == aux)
//				{
//					EsValido = true;
//					break;
//				}
//				else if (arrayClave[i] == COLORES::VACIO)
//				{
//					arrayClave[i] = aux;
//					EsValido = false;
//					break;
//				}
//			}
//		} while (EsValido);
//	}
//
//	// Inicio del juego
//	do
//	{
//
//		// Esta condicion me indica si va el jugador o la cpu.
//		if (EsJugador)
//		{
//			cout << "*********************************************************************" << endl;
//			cout << "*                       [MASTERMIND]                                *" << endl;
//			cout << "*********************************************************************" << endl;
//
//			// "Hud" para mostrar cuando el Jugador y la CPU responde incorrectamente o responde correctamente.
//			cout << "\n[CPU] PUNTOS : " << puntosCPU << endl;
//			cout << "[JUGADOR] TURNOS RESTANTES [" << cantIntentosJugador << "] - COLOR USADO ANTES " << (nombreColor == "" ? "[NINGUNO]" : nombreColor) << " - PUNTOS [" << puntosJugador << "] - RESPUESTAS JUGADOR : ";
//			for (int i = 0; i < intentos; i++)
//			{
//				if (arrayClaveCharJugador[i] != ' ')
//				{
//					cout << " " << arrayClaveCharJugador[i];
//				}
//
//				if (i == intentos - 1)
//				{
//					cout << (puntosJugador == 25 ? "  -> EL JUGADOR TERMINO" : "") << endl;
//				}
//			}
//
//			//PRIMERA FASE, DESCUBRIR LOS COLORES
//			if (puntosJugador != 25)
//			{
//				// Este es mi menu de opciones.
//				cout << "\n[JUGADOR] ELIJA UN COLOR :\n1 - ROJO\n2 - MAGENTA\n3 - NARANJA\n4 - AMARILLO\n5 - VERDER\n6 - CIAN\n7 - AZUL\n8 - VIOLETA" << endl;
//				do
//				{
//					cout << "SELECCION : ";
//					cin >> opcion;
//				} while (opcion < 1 || opcion > 8);
//			}
//			// SEGUNDA FASE, DESCRUBRIR LAS POSICIONES DE LOS COLORES
//			else
//			{
//				system("cls");
//				cout << "*********************************************************************" << endl;
//				cout << "*                       [MASTERMIND]                                *" << endl;
//				cout << "*********************************************************************" << endl;
//
//				// "Hud" para mostrar cuando el Jugador y la CPU responde incorrectamente o responde correctamente.
//				cout << "\n[CPU] PUNTOS : " << puntosCPU << endl;
//				cout << "[JUGADOR] TURNOS RESTANTES [" << cantIntentosJugador << "] - PUNTOS [" << puntosJugador << "]" << endl;
//				
//				// Muestro el orden en que el jugador va posicionado correctamente los colores.
//				cout << "\nCOLORES POSICIONADOS : " << endl;
//				for (int i = 0; i < cantColor; i++)
//				{
//					if (arrayPosicionColor[i])
//					{
//						switch (arrayColorJugador[i])
//						{
//						case COLORES::ROJO:
//							nombreColor = "[ROJO]";
//							break;
//						case COLORES::MAGENTA:
//							nombreColor = "[MAGENTA]";
//							break;
//						case COLORES::NARANJA:
//							nombreColor = "[NARANJA]";
//							break;
//						case COLORES::AMARILLO:
//							nombreColor = "[AMARILLO]";
//							break;
//						case COLORES::VERDE:
//							nombreColor = "[VERDE]";
//							break;
//						case COLORES::CIAN:
//							nombreColor = "[CIAN]";
//							break;
//						case COLORES::AZUL:
//							nombreColor = "[AZUL]";
//							break;
//						case COLORES::VIOLETA:
//							nombreColor = "[VIOLETA]";
//							break;
//						}	
//
//						cout << " " << i + 1 << " - " << nombreColor << "\n";
//					}
//				}
//
//				// Muestro el orden en que el jugador fue sacando los colores.
//				cout << "\nCOLORES DESCUBIERTOS" << endl;
//				for (int i = 0; i < cantColor; i++)
//				{
//					// Solo va a mostrar los colores que aun no se sabe su posicion.
//					if (!arrayPosicionColor[i])
//					{
//						switch (arrayColorJugador[i])
//						{
//						case COLORES::ROJO:
//							nombreColor = "[ROJO]";
//							break;
//						case COLORES::MAGENTA:
//							nombreColor = "[MAGENTA]";
//							break;
//						case COLORES::NARANJA:
//							nombreColor = "[NARANJA]";
//							break;
//						case COLORES::AMARILLO:
//							nombreColor = "[AMARILLO]";
//							break;
//						case COLORES::VERDE:
//							nombreColor = "[VERDE]";
//							break;
//						case COLORES::CIAN:
//							nombreColor = "[CIAN]";
//							break;
//						case COLORES::AZUL:
//							nombreColor = "[AZUL]";
//							break;
//						case COLORES::VIOLETA:
//							nombreColor = "[VIOLETA]";
//							break;
//						}
//						cout << " " << (int)arrayColorJugador[i] << " - " << nombreColor << "\n";
//					}
//				}
//
//				cout << "\n[JUGADOR] ELIJA UN COLOR (DE LOS DESCUBIERTOS) Y LA POSICION DONDE CREE QUE ESTA." << endl;
//				do
//				{
//					auxOpcion = true;
//
//					cout << "NUMERO DE COLOR : ";
//					cin >> numeroColor;
//
//					// Voy a validar que el jugador no pueda elejir un numero de color que antes ya habia elegido.
//					for (int i = 0; i < cantColor; i++)
//					{
//						// voy descontando los indice donde la posicion ha sido descubierta.
//						if (!arrayPosicionColor[i])
//						{
//							if ((int)arrayColorJugador[i] == numeroColor)
//							{
//							    auxOpcion = false;								
//
//								break;
//							}
//						}
//					}
//
//				} while (auxOpcion);
//
//				do
//				{
//					cout << "NUMERO DE POSICION (1-5): ";
//					cin >> numeroPosicion;
//				} while (numeroPosicion < 1 || numeroPosicion > 5);
//
//				system("pause");
//				
//			}
//
//			
//			EsJugador = false;
//
//		}
//		else if (!EsJugador)
//		{
//			//PRIMERA FASE, DESCUBRIR LOS COLORES
//			if (puntosJugador != 25)
//			{
//				aux = (COLORES)opcion;
//				auxOpcion = true;
//				EsCorrecto = false;
//
//				// Valido si el color seleccionado esta presente en el array clave y en el array color.
//				for (int i = 0; i < cantColor; i++)					
//				{
//					// En el caso de que el jugador haya seleccionado un color ya existente, este lo tomara como incorrecto.
//					if (arrayColorJugador[i] == aux)
//					{
//						auxOpcion = false;
//					}
//				}
//				// array clave, solo lo valido en el caso en donde el color seleccionado no sea uno repetido, si se repite EsCorrecto = false.
//				if (auxOpcion)
//				{
//					for (int i = 0; i < cantColor; i++)
//					{
//						if (arrayClave[i] == aux)
//						{
//
//							arrayColorJugador[contador] = aux;
//							EsCorrecto = true;
//							puntosJugador += 5;
//							contador++;
//
//						}
//
//						// En el caso de que el color eleijo sea correcto, salgo del for.
//						if (EsCorrecto)
//						{
//							break;
//						}
//					}
//				}
//
//				// Le doy valor a mi array de char que contiene las respuesta que lleva el jugador.
//				for (int i = 0; i < intentos; i++)
//				{
//					if (arrayClaveCharJugador[i] == ' ')
//					{
//						if (EsCorrecto)
//						{
//							arrayClaveCharJugador[i] = 'O';
//						}
//						else
//						{
//							arrayClaveCharJugador[i] = 'X';
//							puntosCPU += 4;
//						}
//
//						break;
//					}
//				}
//
//				switch (aux)
//				{
//				case COLORES::ROJO:
//					nombreColor = "[ROJO]";
//					break;
//				case COLORES::MAGENTA:
//					nombreColor = "[MAGENTA]";
//					break;
//				case COLORES::NARANJA:
//					nombreColor = "[NARANJA]";
//					break;
//				case COLORES::AMARILLO:
//					nombreColor = "[AMARILLO]";
//					break;
//				case COLORES::VERDE:
//					nombreColor = "[VERDE]";
//					break;
//				case COLORES::CIAN:
//					nombreColor = "[CIAN]";
//					break;
//				case COLORES::AZUL:
//					nombreColor = "[AZUL]";
//					break;
//				case COLORES::VIOLETA:
//					nombreColor = "[VIOLETA]";
//					break;
//				}
//
//				system("cls");
//				// Respuesta del CPU.
//				cout << (EsCorrecto == true ? "EL COLOR ELEGIDO POR EL JUGADOR ES CORRECTO 'O'..." : "EL COLOR ELEGIDO POR EL JUGADOR NO ES CORRECTO 'X'...");
//				Sleep(3500);
//				system("cls");
//
//			}
//			// SEGUNDA FASE, DESCRUBRIR LAS POSICIONES DE LOS COLORES
//			else
//			{
//				// El CPU va a recorrer el arrayColor para validar la posiciones.
//				int auxContador = 0;
//				for (int i = 0; i < cantColor; i++)
//				{
//					// Primero busco el color que eligio el jugador para validar la posicion despues.
//					if ((int)arrayColorJugador[i] == numeroColor)
//					{
//						aux = arrayColorJugador[i];
//						auxContador = i;
//					}
//				}
//
//				for (int i = 0; i < cantColor; i++)
//				{
//					// Segundo valido la posicion del color obtenido antes.
//					if (aux == arrayClave[i])
//					{
//						// Con un boolean devuelvo si la posicion es correcta o no.
//						if (i == (numeroPosicion - 1))
//						{
//							arrayPosicionColor[i] = true;
//							// Voy guardando los colores en la posicion ordenadamente.
//							aux = arrayColorJugador[i];	
//							arrayColorJugador[i] = arrayClave[i];
//							// Voy ordenando los colores del arrayColorJugador intercambiando posiciones
//							arrayColorJugador[auxContador] = aux;
//							PosicionCorrectas = true;
//						}
//						else
//						{
//							arrayPosicionColor[i] = false;
//							PosicionCorrectas = false;
//							puntosCPU += 4;
//						}
//
//						break;
//					}
//				}
//
//				system("cls");
//				// Respuesta del CPU.
//				cout << (PosicionCorrectas == true? "LA POSICION QUE EL [JUGADOR] ELIGIO ES CORRECTA" : "LA POSICION QUE EL [JUGADOR] ELIGIO NO ES CORRECTA") << endl;
//				Sleep(3500);
//				system("cls");
//			}
//
//			cantIntentosJugador--;
//		
//			EsJugador = true;
//
//		}
//
//		// Valido las posiciones para saber si el jugador adivino las posiciones de todos los colores.
//		for (int i = 0; i < cantColor; i++)
//		{
//			if (arrayPosicionColor[i])
//			{
//				PosicionesCorrectas = true;
//			}
//			else
//			{
//				PosicionesCorrectas = false;
//				break;
//			}
//		}
//
//		// Valido condicion para ganar o perder.
//		if (puntosJugador == 25 && PosicionesCorrectas || puntosCPU > 25)
//		{
//			seguir = false;
//		}
//		else if (cantIntentosJugador == 0)
//		{
//			seguir = false;
//		}
//
//	} while (seguir);
//
//	// Si el jugador adivino las posiciones gana puntos extran, en caso contrario los gana la CPU.
//	if (PosicionesCorrectas)
//	{
//		puntosJugador += 15;
//	}
//	else
//	{
//		puntosCPU += 15;
//	}
//
//	system("cls");
//	cout << "**********************************************************************" << endl;
//	cout << "*                       [MASTERMIND]                                 *" << endl;
//	cout << "*                                                                    *" << endl;
//	cout << "* - [INFORMACION DEL JUGADOR]                                        * " << endl;
//	cout << "* - PUNTOS OBTENIDOS : " << puntosJugador << "                                            *" << endl;
//	cout << "* - INTENTOS USADOS : " << cantIntentosJugador << "                                              *" << endl;
//	cout << "* - INTENTOS RESTANTES : " << (intentos - cantIntentosJugador) << "                                          *" << endl;
//	cout << "* - EL JUGADOR LOGRO DESIFRAR EL CODIGO : " << (puntosJugador == 25? "SI":"NO") << "                         *" << endl;
//	cout << "* - EL JUGADOR LOGRO DESIFRAR LAS POSICIONES : " << (PosicionCorrectas == true ? "SI" : "NO") << "                    *" << endl;
//	cout << "*                                                                    *" << endl;
//	cout << "*                                                                    *" << endl;
//	cout << "* - [INFORMACION DEL CPU]                                            * " << endl;
//	cout << "* - PUNTOS OBTENIDOS : " << puntosCPU << "                                            *" << endl;
//	cout << "**********************************************************************" << endl;
//
//	system("pause");
//}