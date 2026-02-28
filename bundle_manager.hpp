/* 
 * this file will have classes for bundle manager
 * */
class Bundle_Manager {
  public:
    bm_mgr* font;
    xx_color* global_color;
    xx_window_manager* window;
    xx_button* btn;

    cxx_timer* timer;

    SDL_Point* mouse_position;
    
    bool _quit_ = false;

    Bundle_Manager ();

    ~Bundle_Manager ();

    void allocate_memory ();

    void free_memory ();
};

Bundle_Manager::Bundle_Manager () {
  this -> font = nullptr;
  this -> global_color = nullptr;
  this -> window = nullptr;
  this -> btn = nullptr;
  this -> mouse_position = nullptr;
  this -> timer = nullptr;
}


Bundle_Manager::~Bundle_Manager () {
  free_memory ();
}


void Bundle_Manager::allocate_memory () {
  this -> font = new bm_mgr [1];
  if (this -> font == nullptr) {
    std::cout << "Memory Allocation, failed : this -> font" << std::endl;
  }
  
  this -> global_color = new xx_color [1];
  if (this -> global_color == nullptr) {
    std::cout << "Memory allocation, failed : this -> global_color" << std::endl;
  }
  
  this -> window = new xx_window_manager [1];
  if (this -> window == nullptr) {
    std::cout << "Memory allocation, failed : this -> window" << std::endl;
  }
  
  this -> btn = new xx_button [3];
  if (this -> btn == nullptr) {
    std::cout << "Memory allocation, failed : this -> btn" << std::endl;
  }

  this -> mouse_position = new SDL_Point [1];
  if (this -> mouse_position == nullptr) {
    std::cout << "Memory allocation, failed : this -> mouse_position" << std::endl;
  }

  this -> timer = new cxx_timer [2];
  if (this -> timer == nullptr) {
    std::cout << "Memory allocation, failed : this -> timer" << std::endl;
  }
}

void Bundle_Manager::free_memory () {
  if (this -> font != nullptr) {
    delete [] this -> font;
    this -> font = nullptr;
  }
  
  // if (this -> global_color != nullptr) {
    // delete [] this -> global_color;
    // this -> global_color = nullptr;
  // }
  
  if (this -> window != nullptr) {
    delete [] this -> window;
    this -> window = nullptr;
  }

  if (this -> mouse_position != nullptr) {
    delete [] this -> mouse_position;
    this -> mouse_position = nullptr;
  }

  if (this -> timer != nullptr) {
    delete [] this -> timer;
    this -> timer = nullptr;
  }
}

