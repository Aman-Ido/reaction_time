/* 
 *  this file will contains files that will use std::chrono for time management or create a timer
 * */


/* 
 * class for class definitions
 * */
class cxx_timer {
  public:
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    void start_timer ();

    void stop_timer ();

    int get_time_seconds ();

    int get_time_milliseconds ();

    long get_time_microseconds ();
};


/* 
 *  class - definitions
 * */


/* 
 *  method - void cxx_timer::start ()
 *    -- method to start the timer
 * */
void cxx_timer::start_timer () {
  auto l_start = std::chrono::steady_clock::now ();



  this -> start = l_start;
}

/* 
 *  method - void cxx_timer::stop ()
 *      -- method to stop the timer
 * */
void cxx_timer::stop_timer () {
  auto l_end = std::chrono::steady_clock::now ();

  this -> end = l_end;
}


/* 
 *  method - int get_time_seconds ()
 *    -- method to get the time in seconds
 * */
int cxx_timer::get_time_seconds () {
  std::chrono::duration result = std::chrono::duration_cast <std::chrono::seconds> (this -> end - this -> start);

  return result.count();
}

/* 
 *  method - int get_time_milliseconds ()
 *    -- method to get the time in milliseconds
 * */
int cxx_timer::get_time_milliseconds () {
  std::chrono::duration result = std::chrono::duration_cast <std::chrono::milliseconds> (this -> end - this -> start);

  return result.count ();
}


/* 
 *  method - long get_time_microseconds ()
 *    -- method to get time in microseconds
 * */
long cxx_timer::get_time_microseconds () {
  std::chrono::duration result = std::chrono::duration_cast <std::chrono::microseconds> (this -> end - this -> start);


  return result.count ();
}
