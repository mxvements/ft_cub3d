
## git submodules
codam's minilibx
git@github.com:42Paris/minilibx-linux.git
mxvements' libft and gnl

## Summary of Key Commands to work with submodules:
+ Add a submodule: git submodule add <repository-url> <path>
+ Initialize submodules: git submodule init
+ Update submodules: git submodule update
+ Update submodules to latest commit: git submodule update --remote
+ Clone with submodules: git clone --recurse-submodules <repository-url>
+ Remove a submodule: git submodule deinit <path-to-submodule>, git rm <path-to-submodule>, rm -rf <path-to-submodule>

<!-- https://lodev.org/cgtutor/raycasting.html -->


## Resources
+ https://github.com/mcombeau/cub3D
+ https://github.com/Saxsori/ray-cast

# TODO:
- LU -> comprobar bien los mapas
  - los colores deben tener proteccion isascii && isdigit y tiene que estar entre 0..255 (letras dan error, negativos dan error)
   
- EDU -> precision para ver siempre la pared dentro de la pared

- poner solo un cuadrado del minimapa, limitando lo que vemos, definir el tamaño segun la posicion del player (actualizar info el minimap start_x)

- revisar leaks
- norminette