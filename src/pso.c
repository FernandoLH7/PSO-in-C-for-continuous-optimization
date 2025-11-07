#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// CONSTANTES

#define X_MAX  5.12 // límite superior del espacio de búsqueda
#define X_MIN  -5.12 // límite inferior del espacio de búsqueda

#define V_MAX   10.0 // límite superior de la velocidad
#define V_MIN  -10.0 // límite inferior de la velocidad

#define P 10 // número de partículas en el enjambre

#define R 3 // dimensiones del problema a resolver

#define W 0.729 // factor de inercia
#define F1 2.05 // factor cognitivo
#define F2 2.05 // factor social

// VARIABLES GLOBALES

double x[P][R]; // posición de cada partícula

double v[P][R]; // velocidad de cada partícula

double b[P][R]; // mejor posición personal de cada partícula

double g[R]; // mejor posición global del enjambre
double g_fitness; // fitness de la mejor posición global (solución del problema)

// DECLARACIÓN DE FUNCIONES

void inicializar_particulas();
void inicializar_mejor_global(double b[P][R]);

void evaluar_fitness_poblacion(double x[P][R], double fit[P]);
double fitness(double x[R]);
void actualizar_mejor_solucion_b(double x[P][R], double b[P][R], double fitness[P]);
void actualizar_mejor_global(double b[P][R]);

void actualizar_velocidad(double w, double f1, double f2);
void actualizar_posicion();

// FUNCIONES DEL ALGORITMO

// Función que inicializa las posiciones y las velocidades de las partículas
// También inicializa la mejor posición personal de cada partícula
void inicializar_particulas() {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            // Posición aleatoria en [X_MIN, X_MAX]
            x[i][j] = X_MIN + (X_MAX - X_MIN) * drand48();
            // Velocidad aleatoria en [V_MIN, V_MAX]
            v[i][j] = V_MIN + (V_MAX - V_MIN) * drand48();
            // Inicializa la mejor posición personal igual a la posición inicial
            b[i][j] = x[i][j];
        }
    }
}

// Función que inicializa la mejor solución global del enjambre
void inicializar_mejor_global(double b[P][R]) {
    // Evaluar fitness de cada mejor personal
    double fit_b[P];
    evaluar_fitness_poblacion(b, fit_b);

    // Tomar como global la mejor (mínimo fitness)
    int indice_mejor = 0;
    double mejor_fit = fit_b[0];

    for(int i = 1; i < P; i++) {
        if(fit_b[i] < mejor_fit) { // Cambiar '<' por '>' si se quiere maximizar
            mejor_fit = fit_b[i];
            indice_mejor = i;
        }
    }

    // Guardar la mejor solución encontrada
    for(int j = 0; j < R; j++) {
        g[j] = b[indice_mejor][j];
    }
    g_fitness = mejor_fit;
}



// Función que calcula el fitness de cada partícula
void evaluar_fitness_poblacion(double x[P][R], double fit[P]) {
    int i;

    for(i = 0; i < P; i++) {
        fit[i] = fitness(x[i]); // se calcula y se guarda el fitness de cada partícula
    }
}

// Función que calcula el fitness (en este caso es la función esfera)
double fitness(double x[R]) {
    int i;

    double suma = 0; // variable que acumula el resultado

    for(i = 0; i < R; i++) {
        suma += x[i] * x[i]; // sumar el cuadrado de cada elemento
    }

    return suma;
}

// Función que comprueba y actualiza la mejor solución personal de cada partícula
void actualizar_mejor_solucion_b(double x[P][R], double b[P][R], double fitness[P]) {
    int i;

    // Evaluar el fitness de la mejor posición personal actual
    double fit_b[P];
    evaluar_fitness_poblacion(b, fit_b);

    for(i = 0; i < P; i++) {
        // comparar el fitness de la posicion actual con el de la mejor posicion
        if(fitness[i] < fit_b[i]) { // Cambia '<' por '>' si se quiere maximizar
            for(int j = 0; j < R; j++) {
                b[i][j] = x[i][j]; // se guarda la nueva mejor posición
            }
        }
    }
}

// Función que comprueba y actualiza la mejor solución global del enjambre
void actualizar_mejor_global(double b[P][R]) {
    double fit_b[P];
    evaluar_fitness_poblacion(b, fit_b);

    // Buscar si alguna mejor personal mejora la global
    for(int i = 0; i < P; i++) {
        if(fit_b[i] < g_fitness) { // Cambia '<' por '>' si se quiere maximizar
            for(int j = 0; j < R; j++) {
                g[j] = b[i][j]; // se guarda la nueva mejor posición global
            }
            g_fitness = fit_b[i]; // se actualiza el fitness de la mejor posición global
        }
    }
}



// Función que actualiza la velocidad de cada partícula
void actualizar_velocidad(double w, double f1, double f2) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            // fórmula de actualización de la velocidad
            v[i][j] = w * v[i][j]
                    + f1 * drand48() * (b[i][j] - x[i][j])
                    + f2 * drand48() * (g[j] - x[i][j]);

            // se comprueba que la velocidad no se salga de los límites
            if (v[i][j] < V_MIN) {
                v[i][j] = V_MIN;
                continue;
            } 
            if (v[i][j] > V_MAX) {
                v[i][j] = V_MAX;
            }
        }
    }
}

// Función que actualiza la posición de cada partícula
void actualizar_posicion() {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            // se desplaza la partícula según su velocidad
            x[i][j] += v[i][j];

            // se comprueba que la posición no se salga de los límites
            if (x[i][j] < X_MIN) {
                x[i][j] = X_MIN ;
                continue;
            } 
            if (x[i][j] > X_MAX) {
                x[i][j] = X_MAX;
            }
        }
    }
}

int main() {
    // semilla para numeros aleatorios
    srand48(time(NULL));

    int max_iter = 100; // número de iteraciones
    double fit[P]; // vector que contiene el fitness de cada particula

    // inicializar las partículas
    inicializar_particulas();

    // inicializar la mejor solución global
    inicializar_mejor_global(b);

    for(int iter = 0; iter < max_iter; iter++) {
        // calcular el fitness inicial
        evaluar_fitness_poblacion(x, fit);

        // actualizar la mejor solución personal
        actualizar_mejor_solucion_b(x, b, fit);

        // actualizar la mejor solución global
        actualizar_mejor_global(b);

        // actualizar velocidades y posiciones
        actualizar_velocidad(W, F1, F2);
        actualizar_posicion();

        // se muestra la mejor solución global y su fitness cada 10 iteraciones
        if (iter % 10 == 0 || iter == max_iter - 1) {
			printf("Iter %4d | Mejor fitness = %.4f | ", iter, g_fitness);
            printf("Mejor posición: [");
            for (int d = 0; d < R; ++d) {
                printf(" %.4f", g[d]);
                if (d < R - 1) {
                    printf(",");
                }
            }
            printf(" ]\n");
        }
    }

    // se muestra la mejor solución encontrada al problema
    printf("\nMejor fitness encontrado: %.4f\n", g_fitness);
	printf("Mejor posición: [");
	for (int d = 0; d < R; ++d) {
		printf(" %.4f", g[d]);
		if (d < R - 1) {
            printf(",");
        }
	}
	printf(" ]\n");
}
