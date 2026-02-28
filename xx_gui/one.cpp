#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "xx_string.h"
#include "xx_color.h"
#include "xx_input.h"
#include "xx_button.h"

int main (int argc, char** argv) {

  printf ("Printing out the size of the strings \n");

  printf ("The size of xx_input is %lld\n", sizeof(xx_input));
  printf ("The size of xx_button is %lld\n", sizeof(xx_button));
  printf ("The size of xx_color is %lld\n", sizeof(xx_color));

  return 0;
}
