
#include "cub3d.h"

void ray(float x, float y, int ang)
{

}

/*
// Tamaño del mapa
#define MAP_WIDTH 8
#define MAP_HEIGHT 8

// Definimos un mapa 2D (1 son paredes, 0 son espacios vacíos)
int mapa[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

// Estructura para la posición del jugador
typedef struct {
    float x, y;       // Posición del jugador en el mapa
    float dirX, dirY; // Dirección de vista del jugador
} Jugador;

// Algoritmo de raycasting usando DDA
void raycast(Jugador jugador) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        // Calcular el ángulo del rayo para cada columna en la pantalla
        float cameraX = 2 * x / (float)MAP_WIDTH - 1; // Coordenada X en el espacio de la cámara
        float rayDirX = jugador.dirX + cameraX;       // Dirección del rayo en X
        float rayDirY = jugador.dirY;                 // Dirección del rayo en Y

        // Posición inicial en la cuadrícula del mapa
        int mapX = (int)jugador.x;
        int mapY = (int)jugador.y;

        // Distancia del rayo en ambas direcciones
        float sideDistX, sideDistY;

        // Longitud del rayo desde una x o y hasta la siguiente celda
        float deltaDistX = fabs(1 / rayDirX);
        float deltaDistY = fabs(1 / rayDirY);

        // Dirección en la que se mueve el rayo (1 o -1) y la distancia a la próxima intersección en esa dirección
        int stepX, stepY;
        
        // Calcular stepX y stepY, así como sideDistX y sideDistY
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (jugador.x - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - jugador.x) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (jugador.y - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - jugador.y) * deltaDistY;
        }

        // Realizar el DDA para encontrar la intersección del rayo con una pared
        int hit = 0;  // ¿Se encontró una pared?
        int side;     // Si fue una intersección en el eje X o Y

        while (hit == 0) {
            // Saltar a la siguiente celda en el eje X o Y
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            // Verificar si el rayo ha alcanzado una pared
            if (mapa[mapX][mapY] == 1) hit = 1;
        }

        // Calcular la distancia al punto de impacto
        float distancia;
        if (side == 0) {
            distancia = (mapX - jugador.x + (1 - stepX) / 2) / rayDirX;
        } else {
            distancia = (mapY - jugador.y + (1 - stepY) / 2) / rayDirY;
        }

        // Imprimir la distancia calculada para cada rayo
        printf("Rayo %d: distancia a la pared = %f\n", x, distancia);
    }
}

int main() {
    // Definir la posición inicial del jugador
    Jugador jugador;
    jugador.x = 4.0f;
    jugador.y = 4.0f;
    jugador.dirX = -1.0f; // Mirando hacia la izquierda (eje X negativo)
    jugador.dirY = 0.0f;

    // Realizar el raycasting desde la posición del jugador
    raycast(jugador);

    return 0;
}
*/