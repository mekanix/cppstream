#include <iostream>
#include <thread>


class AsyncWorker
{
  public:
    AsyncWorker() { t = std::thread(&AsyncWorker::_process, this); }
    ~AsyncWorker() { t.join(); }

  protected:
    std::thread t;

  private:
    void _process() { std::cout << "Hello threaded World!\n"; }
};


int
main()
{
  auto worker = new AsyncWorker();
  delete worker;
  return 0;
}
