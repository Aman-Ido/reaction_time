/* 
  this file will hold the functions for button - in SDL2/C
*/
#ifndef XX_IMAGE_MANAGER
#include "xx_image_manager.h"
#endif

#ifndef BM_MGR
#include "bm_mgr.h"
#endif

#define XX_BUTTON 1030


enum Button_Actions {
  Pressed,
  Hovered,
  None,
};

typedef struct {
  SDL_Rect btn_size;
  
  /* 
    I also want my buttons to have images - strings
  */
  char btn_text[30]; // this is for the button - no need to allocate or free this
  
  xx_image_manager* image;
  
  SDL_Point mouse_pos;
  
  // colors
  SDL_Color border_color;
  SDL_Color hover_color;
  SDL_Color click_color;
  
  SDL_Point padding; // x - horizontal and y - vertical
  
  enum Button_Actions btn_state;
  
  SDL_Point btn_active_translate; 
  /* 
    when button is pressed, add 5 pixels to x and 5 pixels to y 
  */
  
  int return_value;
} xx_button;

// functions - declarations
void xx_render_button_text (SDL_Renderer* i_renderer, xx_button* btn, bm_mgr* text, int x, int y);
int xx_set_button_text (xx_button* btn, bm_mgr* text, char* btn_msg);
int xx_set_button_image (SDL_Renderer* i_renderer, xx_button* btn, char* img_path);
void xx_render_button_image (SDL_Renderer* i_renderer, xx_button* btn, int x, int y);
void xx_free_button (xx_button* i_btn);

int xx_button_listen (SDL_Renderer* i_renderer, xx_button* btn, SDL_Event e);


// functions - definitions

/* 
  void xx_render_button (SDL_Renderer* i_renderer, xx_button* btn);
    - this function renders the button
*/
void xx_render_button_text (SDL_Renderer* i_renderer, xx_button* btn, bm_mgr* text, int x, int y) {
  btn -> btn_size.x = x;
  btn -> btn_size.y = y;
  
  // rendering the text of the button
  /* 
    for now adding only 1, in future, we will probably have btn -> pad (SDL_Rect);
  */
  
  // bm_render (i_renderer, text, btn -> btn_text, x + btn -> padding.x, y + btn -> padding.y);
  
  
  if (btn -> btn_state == Hovered) {
    // change the color of the text
    SDL_SetTextureColorMod (text -> map, btn -> hover_color.r, btn -> hover_color.g, btn -> hover_color.b);
    
    // rendering text
    bm_render (i_renderer, 
      text, 
      btn -> btn_text, 
      btn -> btn_size.x + btn -> padding.x, 
      btn -> btn_size.y + btn -> padding.y);
    
    // change border color
    SDL_SetRenderDrawColor (i_renderer, btn -> hover_color.r, btn -> hover_color.g, btn -> hover_color.b,
      btn -> hover_color.a);
  } else if (btn -> btn_state == Pressed) {
    // change the color of the text
    SDL_SetTextureColorMod (text -> map, btn -> click_color.r, btn -> click_color.g, btn -> click_color.b);
    
    // updating the translation
    btn -> btn_active_translate.x = btn -> btn_size.x + 5; // this '5' value may set to variable in the future
    btn -> btn_active_translate.y = btn -> btn_size.y + 5; 
    
    // updating the btn -> size.x and btn -> size.y
    btn -> btn_size.x = btn -> btn_active_translate.x;
    btn -> btn_size.y = btn -> btn_active_translate.y;
    
    // rendering text
    bm_render (i_renderer, 
        text, 
        btn -> btn_text, 
        btn -> btn_size.x + btn -> padding.x, 
        btn -> btn_size.y + btn -> padding.y);
    
    // change border color
    SDL_SetRenderDrawColor (i_renderer, btn -> click_color.r, btn -> click_color.g, btn -> click_color.b,
      btn -> click_color.a);
  } else {
    // change the color of the text
    SDL_SetTextureColorMod (text -> map, btn -> border_color.r, btn -> border_color.g, btn -> border_color.b);
    
    // rendering text
    bm_render (i_renderer, 
        text, 
        btn -> btn_text, 
        btn -> btn_size.x + btn -> padding.x, 
        btn -> btn_size.y + btn -> padding.y);
    
    // change border color
    SDL_SetRenderDrawColor (i_renderer, btn -> border_color.r, btn -> border_color.g, btn -> border_color.b,
      btn -> border_color.a);
  }
  
  // render the box of the button
  SDL_RenderDrawRect (i_renderer, &btn -> btn_size);
}

/* 
  void xx_render_button_image (SDL_Renderer* i_renderer, xx_button* btn);
    - this function will render the button but with an image
*/
void xx_render_button_image (SDL_Renderer* i_renderer, xx_button* btn, int x, int y) {
  // btn -> btn_size.x = x + btn -> padding.x;
  // btn -> btn_size.y = y + btn -> padding.y;
  
  btn -> btn_size.x = x;
  btn -> btn_size.y = y;
  
  
  // change button border color here
  if (btn -> btn_state == Hovered) {
   // change border color
    SDL_SetRenderDrawColor (i_renderer, btn -> hover_color.r, btn -> hover_color.g, btn -> hover_color.b,
      btn -> hover_color.a);
  } else if (btn -> btn_state == Pressed) {
    // updating the translation
    btn -> btn_active_translate.x = btn -> btn_size.x + 5; // this '5' value may set to variable in the future
    btn -> btn_active_translate.y = btn -> btn_size.y + 5; 
    
    // updating the btn -> size.x and btn -> size.y
    btn -> btn_size.x = btn -> btn_active_translate.x;
    btn -> btn_size.y = btn -> btn_active_translate.y;
    
    // change border color
    SDL_SetRenderDrawColor (i_renderer, btn -> click_color.r, btn -> click_color.g, btn -> click_color.b,
      btn -> click_color.a);
  } else {
    // change border color
    SDL_SetRenderDrawColor (i_renderer, btn -> border_color.r, btn -> border_color.g, btn -> border_color.b,
      btn -> border_color.a);
  }
  
  // rendering the image first
  xx_render_image (i_renderer, btn -> image, btn -> btn_size.x + btn -> padding.x, btn -> btn_size.y + btn -> padding.y);
  
  // rendering the button outline
  SDL_RenderDrawRect (i_renderer, &btn -> btn_size);
}


/* 
  int xx_set_button_text (SDL_Renderer* i_renderer, xx_button* btn, bm_mgr* text);
    - this function will set the button text
    - like I can get the text and set the width - height, of the button
    - also allocate bm_mgr
*/
int xx_set_button_text (xx_button* btn, bm_mgr* text, char* btn_msg) {
  int message_size = xx_strlen (btn_msg);
    
  // btn -> btn_size.w = l_single_char_size * message_size;
  
  if (text -> zoom < 0) {
    btn -> btn_size.w = (text -> z_chang * message_size) + (btn -> padding.x * 2); // padding.w * 2,  because that is the offset
    btn -> btn_size.h = text -> z_chang + ( btn -> padding.y * 2); // padding.h * 2
  } else {
    
    btn -> btn_size.w = (text -> dest.w * message_size) + ( btn -> padding.x * 2 ); // padding.w * 2,  because that is the offset
    btn -> btn_size.h = text -> dest.h + ( btn -> padding.y * 2 ) ; // padding.h * 2
  }
  
  
  
  // copying the inputted string to this
  xx_strcpy (btn -> btn_text, btn_msg);
  
  return 1;
}


/* 
  function - free everything of the button
*/
void xx_free_button (xx_button* i_btn) {
  if (i_btn -> image != NULL) {
    xx_free_image (i_btn -> image);
    i_btn -> image = NULL;
  }
}

/* 
  function - to set up the button with an image
    - it will allocate xx_image_manager
    - set the width and height
*/
int xx_set_button_image (SDL_Renderer* i_renderer, xx_button* btn, char* img_path) {
  btn -> image = (xx_image_manager*) calloc  (1, sizeof(xx_image_manager));
  if (btn -> image == NULL) {
    printf ("\t ! xx_set_button_image () -> Failed, Memory Allocate, xx_image_manager\n");
    return 0;
  } else {
    printf ("\t * xx_set_button_image () -> success, Memory allocation, xx_image_manager \n");
  }
  
  // loading the image
  if (!xx_load_image (i_renderer, btn -> image, img_path)) {
    printf ("\t ! xx_set_buttont_image () -> Failed, Image Loading, xx_image_manager\n");
    return 0;
  } else {
    printf ("\t * xx_set_button_image () -> Success, Image Loading, \n\t\t - %s\n", img_path);
  }
  
  btn -> btn_size.w = btn -> image -> width + (btn -> padding.x * 2);
  btn -> btn_size.h = btn -> image -> height + (btn -> padding.y * 2);
  
  return 1;
}

/* 
  function - to listen for inputs
    - it will take SDL_Event as input as well 
*/
int xx_button_listen (SDL_Renderer* i_renderer, xx_button* btn, SDL_Event e) {
  if (e.type == SDL_MOUSEMOTION) {
    SDL_GetMouseState (&btn -> mouse_pos.x, &btn -> mouse_pos.y); // getting the mouse state
    
    if (SDL_PointInRect(&btn -> mouse_pos, &btn -> btn_size)) {
      btn -> btn_state = Hovered;
    } else {
      btn -> btn_state = None;
    }
  }
  
  // if a button is pressed
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    // and if the mouse point is inside of the button (while being pressed)
    if (SDL_PointInRect (&btn -> mouse_pos, &btn -> btn_size)) {
      btn -> btn_state = Pressed;
      btn -> return_value = 1;
      return 1;
    }
  }
  
  if (e.type == SDL_MOUSEBUTTONUP) {
    btn -> btn_state = None;
    btn -> return_value = -1;
    return -1;
  }
  
  return 0;
}
