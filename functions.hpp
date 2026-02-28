/* 
 * this program will only have functions
 * timer [0] is for the game count
 * timer [1] is for the random count
 * */
void store_result (Bundle_Manager* i_bun) {

  i_bun -> timer [0].stop_timer ();

  i_bun -> result -> push_back (i_bun -> timer [0].get_time_milliseconds ());
}
