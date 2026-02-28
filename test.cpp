#include <iostream>
#include <vector>

class One {
  public:
    std::vector <int>* ptr;

    One () {
      this -> ptr = nullptr;
    }


    ~One () {
      if (this -> ptr != nullptr) {
        delete this -> ptr;
        this -> ptr = nullptr;
      }
    }
};


int main () {
  One* b = new One;

  b -> ptr = new std::vector <int>;


  // b -> ptr -> push_back (10);
  // b -> ptr -> push_back (11);

  // std::cout << "Output " << b -> ptr[0] << std::endl;


  delete b;

  return 0;
}
