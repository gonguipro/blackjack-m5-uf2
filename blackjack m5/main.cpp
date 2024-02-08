#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <ctime>
using namespace std;

// Función para obtener un valor aleatorio de una carta
int obtenerValorCarta() {
	return rand() % 9 + 2; // Cartas del 2 al 10
}

// Función para obtener el valor de un AS (1 u 11)
int obtenerValorAs() {
	cout << "¿Quieres que el AS sea 1 o 11?: ";
	int eleccion;
	do {
		cin >> eleccion;
		if (eleccion != 1 && eleccion != 11) {
			cout << "Opción no válida. Elige 1 o 11." << endl;
		}
	} while (eleccion != 1 && eleccion != 11);
	return eleccion;
}

// Función para determinar si un valor es un AS
bool esAs(int valor) {
	return valor == 1;
}

// Función para mostrar las cartas y el total
void mostrarEstado(int totalJugador, int totalCroupier, bool mostrarTodo) {
	cout << "\nTus cartas: " << totalJugador << endl;

	if (mostrarTodo) {
		cout << "Cartas del croupier: " << totalCroupier << endl;
	}
	else {
		cout << "Carta del croupier: " << (esAs(totalCroupier) ? 1 : totalCroupier) << endl;
	}
}

int main()
{
	//Titulo del juego y color.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
	cout << "   /$$$$$$$ /$$       /$$$$$$   /$$$$$$ /$$   /$$    /$$$$$  /$$$$$$   /$$$$$$ /$$   /$$\n"
		"  | $$__  $| $$      /$$__  $$ /$$__  $| $$  /$$/   |__  $$ /$$__  $$ /$$__  $| $$  /$$/\n"
		"  | $$  \\ $| $$     | $$  \\ $$| $$  \\__| $$ /$$/       | $$| $$  \\ $$| $$  \\__| $$ /$$/ \n"
		"  | $$$$$$$| $$     | $$$$$$$$| $$     | $$$$$/        | $$| $$$$$$$$| $$     | $$$$$/ \n"
		"  | $$__  $| $$     | $$__  $$| $$     | $$  $$   /$$  | $$| $$__  $$| $$     | $$  $$ \n"
		"  | $$  \\ $| $$     | $$  | $$| $$    $| $$\\  $$ | $$  | $$| $$  | $$| $$    $| $$\\  $$\n"
		"  | $$$$$$$| $$$$$$$| $$  | $$|  $$$$$$| $$ \\  $$|  $$$$$$/| $$  | $$|  $$$$$$| $$ \\  $$\n"
		"  |_______/|________|__/  |__/ \\______/|__/  \\__/ \\______/ |__/  |__/\\______/ |__/  \\__/\n"

		" \n \n \n \n                                     by john victoria \n";

	SetConsoleTextAttribute(hConsole, 7);

	//Hacemos que el usuario pulse 1 para pasar al juego.
	int opcion;

	cout << "Pulse 1 para continuar: " << endl;
	cin >> opcion;

	// Dentro del WHILE va la lógica del juego
	while (opcion == 1)
	{
		srand(time(0)); // Semilla para la generación de números aleatorios

		// Inicialización de variables
		int totalJugador = 0;
		int totalCroupier = 0;

		// Repartir cartas al jugador
		totalJugador += obtenerValorCarta();
		totalJugador += obtenerValorCarta();

		// Repartir carta al croupier
		totalCroupier += obtenerValorCarta();

		// Mostrar las cartas iniciales
		mostrarEstado(totalJugador, totalCroupier, false);

		// Turno del jugador
		char eleccion;
		do {
			cout << "Quieres una nueva carta? (s/n): ";
			cin >> eleccion;

			if (eleccion == 's') {
				int nuevaCarta = obtenerValorCarta();
				totalJugador += (esAs(nuevaCarta) ? obtenerValorAs() : nuevaCarta);
				mostrarEstado(totalJugador, totalCroupier, false);
			}

		} while (eleccion == 's' && totalJugador < 21);

		// Turno del croupier
		while (totalCroupier < 17) {
			int nuevaCarta = obtenerValorCarta();
			totalCroupier += (esAs(nuevaCarta) ? obtenerValorAs() : nuevaCarta);
		}

		// Mostrar resultados
		mostrarEstado(totalJugador, totalCroupier, true);

		// Determinar el resultado del juego
		if (totalJugador == 21 && totalCroupier != 21) {
			cout << "Has ganado. Has alcanzado 21." << endl;
		}
		else if (totalJugador <= 21 && totalCroupier > 21) {
			cout << "Has ganado. La banca se paso de 21." << endl;
		}
		else if (totalJugador == totalCroupier && totalJugador <= 21) {
			cout << "Empate. Ambos tienen la misma puntuacion." << endl;
		}
		else if (totalJugador > 21) {
			cout << "Has perdido. Te has pasado de 21." << endl;
		}
		else if (totalCroupier <= 21 && totalCroupier >= totalJugador) {
			cout << "Has perdido. La banca tiene una puntuacion mayor." << endl;
		}
		else {
			cout << "Ganaste. La banca se pasó de 21." << endl;
		}
		break;
	}

	return 0;
}
