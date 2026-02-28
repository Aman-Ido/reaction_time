/* 
  xx_grid.h
    - this file will have the main grid system (in future)
    
    
    * But for now
      - it will have 2 functions to draw grid on the screen
*/

/* 
  function - declarations
*/
void xx_draw_grid_lines (SDL_Renderer* i_renderer, size_t max_width, size_t max_height, size_t scale);
void xx_draw_grid_dots (SDL_Renderer* i_renderer, size_t max_width, size_t max_height, size_t scale);


/* 
  function - definitions
*/

/* 
  function - void xx_draw_grid_lines (SDL_Renderer*, size_t, size_t, size_t)
      - it will draw lines for grids (in red color);
*/
void xx_draw_grid_lines (SDL_Renderer* i_renderer, size_t max_width, size_t max_height, size_t scale) {
  /*
    temp references
  */
  const int n_x = max_width / scale;
  const int n_y = max_height / scale;
  
  SDL_SetRenderDrawColor (i_renderer, 255, 0, 0, 255);
  
  for (int i = 0; i < n_x; i++) {
    SDL_RenderDrawLine (i_renderer, i * scale, 0, i * scale, max_height);
  }
  
  for (int j = 0; j < n_y; j++) {
    SDL_RenderDrawLine (i_renderer, 0, j * scale, max_width, j * scale);
  }
}


/* 
  function - void xx_draw_grid_dots (SDL_Renderer*, size_t, size_t, size_t);
      - it will draw points on the screen (in red color)
*/
void xx_draw_grid_dots (SDL_Renderer* i_renderer, size_t max_width, size_t max_height, size_t scale) {
  /* 
    temp references
  */
  const int n_x = max_width / scale;
  const int n_y = max_height / scale;
  
  SDL_SetRenderDrawColor (i_renderer, 255, 0, 0, 255);
  
  for (int i = 0; i < n_x; i++) {
    for (int j = 0; j < n_y; j++) {
      SDL_RenderDrawPoint (i_renderer, i * scale, j * scale);
    } 
  }
  
}