/* 
 * In this Program we are going to make a reaction time something using following libraries
 * SDL
 * chrono
 * and maybe fstream
 * */
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <cstring>
#include <random>
#include <vector>
#include <chrono>
#include <thread>
// #include <SDL2/SDL_mixer.h>

#include "./xx_gui/xx_string.h"
#include "./xx_gui/bm_mgr.h"
#include "./cxx_timer.hpp"
#include "./xx_gui/xx_window_manager.h"
#include "./xx_gui/xx_color.h"
#include "./xx_gui/xx_button.h"

#include "bundle_manager.hpp"

// function average_time
int average_time (std::vector <int> i_value) {
  int result = 0;
  for (auto &i : i_value) {
    result += i;
  }

  int r_result = result / 5;

  return r_result;
}

int main (int argc, char** argv) {
  SDL_Init (SDL_INIT_VIDEO);
  IMG_Init (IMG_INIT_PNG);
  
  
  Bundle_Manager* bun = new Bundle_Manager [1];
  
  bun -> allocate_memory ();
  
  // creating color value
  bun -> global_color = xx_create_color (); // default colors

  // setting up color values
  bun -> global_color -> none -> r = 0;
  bun -> global_color -> none -> g = 0;
  bun -> global_color -> none -> b = 0;
  bun -> global_color -> none -> a = 255;
  
  bun -> global_color -> hover -> r = 255;
  bun -> global_color -> hover -> g = 0;
  bun -> global_color -> hover -> b = 0;
  bun -> global_color -> hover -> a = 255;
  // setting up window
  xx_strcpy (bun -> window -> window_title, (char*) "Reaction::Timer"); // title
  bun -> window -> width = 640; // width
  bun -> window -> height = 640; // height
  
  // creating window
  xx_create_window_renderer (bun -> window);
  
  // creating / setting up the bm_mgr font
  bm_set_zoom (bun -> font, -32);
  bm_load (bun -> window -> renderer, bun -> font, (char*) "./assets/consolas48.png");
  
  // creating button
  bun -> btn[0].padding.x = 85;
  bun -> btn[0].padding.y = 100;
  xx_set_button_text (&bun -> btn[0], bun -> font, (char*) "press when color is changed");

  // creating input buttons 
  // 1 - start game 
  // 2 - end game - quit
  bun -> btn[1].padding.x = 10;
  bun -> btn[1].padding.y = 10;
  xx_set_button_text (&bun -> btn[1], bun -> font, (char*) "Start The Test");

  bun -> btn[2].padding.x = 10;
  bun -> btn[2].padding.y = 10;
  xx_set_button_text (&bun -> btn[2], bun -> font, (char*) "Quit the Text");

  // setting up the random setting
  std::random_device rd;
  std::mt19937 eng(rd());

  std::uniform_int_distribution <int> dist(2, 6);

  int num = dist (eng);

  std::vector <int> result;


  
  /* 
   * switches for showing or not showing anything
   * */
  bool show_program = false;
  int t_test = 0;
  const int MAX_TEXT = 5; // only 4 tests
  bool game_running = false;
  
  // main lop
  SDL_Event e;
  
  while (!bun -> _quit_) {
    while (SDL_PollEvent (&e)) {
      if (e.type == SDL_QUIT) {
        bun -> _quit_ = true;
      }
      
      xx_button_listen (bun -> window -> renderer, &bun -> btn[0], e);

      xx_button_listen (bun -> window -> renderer, &bun -> btn[1], e);
      xx_button_listen (bun -> window -> renderer, &bun -> btn[2], e);

      if (show_program && game_running) {
        if (bun -> btn[0].return_value == 1) {

          // if the button is pressed
          // change color
          bun -> btn[0].border_color = * bun -> global_color -> none;

          // bun -> btn[0].return_value = 0;

          
          // change the button message
          xx_set_button_text (&bun -> btn[0], bun -> font, (char*) "press when color is changed");

          // stop the timer
          bun -> timer [0].stop_timer ();

          // check the result - push back to the vector
          result.push_back (bun -> timer [0].get_time_milliseconds ());
          show_program = false; // close the lid or the running of the program

          num = dist (eng); // put new random number in
          bun -> timer [1].start_timer (); // start the clock once again (waiting timer )

          t_test = t_test + 1; // this variable to to check if the test has reached it's limit 5

          // if the t_test variable has reached or is equal to max we will quit this window
          if (t_test == MAX_TEXT) {
            game_running = false;
            show_program = true;
          }
        }

      }

      if (!game_running) {
        if (bun -> btn [1].return_value == 1) {
          result.clear ();
          game_running = true;
          show_program = false;
          bun -> timer [1].start_timer ();
          t_test = 0;
        }
        if (bun -> btn [2].return_value == 1) {
          bun -> _quit_ = true;
        }
      }
    }
    /* 
     *  this is the main game rendering
     * */
    SDL_SetRenderDrawColor (bun -> window -> renderer, 255, 255, 255, 255);
    SDL_RenderClear (bun -> window -> renderer);
    SDL_SetRenderDrawColor (bun -> window -> renderer, 255, 255, 255, 255);


    if (game_running) {
      
      if (!show_program) {
        // generate random value
          bun -> timer [1].stop_timer ();
          if (bun -> timer [1].get_time_seconds() >= num) {
            
            // bun -> timer [1].stop_timer ();
            bun -> timer [0].start_timer ();

            show_program = true;

            bun -> btn[0].border_color = * bun -> global_color -> hover;
            xx_set_button_text (bun -> btn, bun -> font, (char*) "********* Press ***********");

          }

          
          // rendering the text here
          for (int i = 0; i < (int) result.size(); i++) {
            bm_set_color (bun -> font, 119, 119, 119);
            int l_val = result [i];
            bm_render (bun -> window -> renderer, bun -> font, (char*)std::to_string(l_val).c_str(), 10, 450 + ( i * bun -> font -> z_chang));
          }     
      }

      xx_render_button_text (bun -> window -> renderer, &bun -> btn[0], bun -> font, 10, 10);
    } else {
      for (int i = 0; i < (int) result.size() ; i++) {
        bm_set_color (bun -> font, 120, 120, 120);
        bm_render (bun -> window -> renderer, bun -> font, (char*) std::to_string (result[i]).c_str(), 10, 10 + (i * bun -> font -> z_chang));
      }

      // calculating
      int result_value = average_time (result);

      // rendering
      bm_set_color (bun -> font, 130, 130, 120);
      std::string r_string = std::to_string (result_value) + " ms";
      bm_render (bun -> window -> renderer, bun -> font, (char*) r_string.c_str(), 250, 10);

      if (!game_running) {
        xx_render_button_text (bun -> window -> renderer, &bun -> btn[1], bun -> font, 10, 500);
        xx_render_button_text (bun -> window -> renderer, &bun -> btn[2], bun -> font, 350, 500); 
      }

    }


    SDL_RenderPresent (bun -> window -> renderer);
    
  }
  
  // freeing everything
  xx_free_button (bun -> btn);
  bm_free (bun -> font);
  
  xx_free_color (bun -> global_color);
  
  xx_destroy_window_renderer (bun -> window);
  
  
  bun -> free_memory ();
  
  
  
  delete [] bun;
  
  
  IMG_Quit ();
  SDL_Quit ();


  return 0;
}
