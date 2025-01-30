
#include "../includes/cub3d.h"

void ray(t_cub *data)
{
    for (int x = 0; x < data->map->cols; x++) {
        // Calcular el ángulo del rayo para cada columna en la pantalla
        float cameraX = 2 * x / (float)data->map->cols - 1; // Coordenada X en el espacio de la cámara
        float rayDirX = data->map->player->dirX + data->map->player->dirX * cameraX ;       // Dirección del rayo en X
        float rayDirY = data->map->player->dirY + data->map->player->dirY * cameraX;                 // Dirección del rayo en Y
        // printf("valor de ray dir -> %f .\n", rayDirY);

        // Posición inicial en la cuadrícula del mapa
        int mapX = (int)data->map->player->x;
        int mapY = (int)data->map->player->y;
	    // printf("jugador x->%d, y->%d\n", mapX, mapY);


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
            sideDistX = (data->map->player->x - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->map->player->x) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            // printf("datay -> %f , mapaY -> %d , deltaDistY -> %f .\n", data->player->y, mapY, deltaDistY);
            sideDistY = (data->map->player->y - mapY) * deltaDistY;
        } else {
            stepY = 1;
            // printf("datay -> %f , mapaY -> %d , deltaDistY -> %f .\n", data->player->y, mapY, deltaDistY);
            sideDistY = (mapY + 1.0 - data->map->player->y) * deltaDistY;
        }

        // Realizar el DDA para encontrar la intersección del rayo con una pared
        int hit = 0;  // ¿Se encontró una pared?
        int side;     // Si fue una intersección en el eje X o Y


        while (hit == 0) {
            // Saltar a la siguiente celda en el eje X o Y
            // printf("sideDis y-> %f.\n", sideDistY);
            // printf("sideDis x-> %f.\n", sideDistX);
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
	        // printf("map aqui-> %d y %d.\n", mapX, mapY);

            // Verificar si el rayo ha alcanzado una pared
            if (data->map->map[mapX][mapY] == '1') 
                hit = 1;
        }

        // Calcular la distancia al punto de impacto
        float distancia;
        if (side == 0) {
            distancia = (mapX - data->map->player->x + (1 - stepX) / 2) / rayDirX;
        } else {
            distancia = (mapY - data->map->player->y + (1 - stepY) / 2) / rayDirY;
        }

        // Imprimir la distancia calculada para cada rayo
        printf("Rayo %d: distancia a la pared = %f\n", x, distancia);
    }
}
