#include <application.h>
#include <stdexcept>

int main(int argc, char** argv) {
  try {
    Application app;
    app.run();
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return -1;
  } catch (...) {
    std::cerr << "Unknown exception occurred" << std::endl;
    return -1;
  }

  return 0;
}