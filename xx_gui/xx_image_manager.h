/* 
  this file will only have the information for image rendering and image loading
  
  using SDL_image
*/
#define XX_IMAGE_MANAGER 1010


typedef struct {
  SDL_Texture* texture = NULL;
  int width = 0;
  int height = 0;
} xx_image_manager;

/* 
  function - declarations
*/
void xx_free_image (xx_image_manager* i_img);
int xx_load_image (SDL_Renderer* i_renderer, xx_image_manager* i_img, char* path); // returns 1 - success
void xx_render_image (SDL_Renderer* i_renderer, xx_image_manager* i_img, int x, int y);

/* function - definitions */

/* 
  function to destroy and null point the loaded image
*/
void xx_free_image (xx_image_manager* i_img) {
  if (i_img -> texture != NULL) {
    SDL_DestroyTexture (i_img -> texture);
    i_img -> texture = NULL;
    i_img -> width = 0;
    i_img -> height = 0;
  }
}


/* 
  function - to load the image
    - will autotmatically load the image 
    - and set the width and height
*/
int xx_load_image (SDL_Renderer* i_renderer, xx_image_manager* i_img, char* path) {
  xx_free_image (i_img); // freeing the previously loaded image
  
  // loading the image using SDL_image
  i_img -> texture = IMG_LoadTexture (i_renderer, path);
  if (i_img -> texture == NULL) {
    printf ("\t ! IMG_LoadTexture - %s\n ", IMG_GetError ());
    return 0;
  } else {
    printf ("\t * IMG_LoadTexture - Success, %s\n", path);
  }
  
  // querying the texture to get width and height
  SDL_QueryTexture (i_img -> texture, NULL, NULL, &i_img -> width, &i_img -> height);
  
  return 1;
}

/* 
  function - render the image
*/
void xx_render_image (SDL_Renderer* i_renderer, xx_image_manager* i_img, int x, int y) {
  SDL_Rect l_rect = {x, y, i_img -> width, i_img -> height};
  SDL_RenderCopy (i_renderer, i_img -> texture, NULL, &l_rect);
}