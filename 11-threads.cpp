#include <iostream>
#include <string>
#include <thread>
#include <nlohmann/json.hpp>


using json = nlohmann::json;


class AsyncWorker
{
  public:
    AsyncWorker(const std::string &url, json &result) : _result{result}
    {
      _url = url;
      t = std::thread(&AsyncWorker::_process, this);
    }
    ~AsyncWorker()
    {
      t.join();
    }

  protected:
    std::thread t;
    std::string _url;

  private:
    json &_result;
    void _process()
    {
      std::cout << "Getting from url: " << _url << "\n";
      _result["cvrc"] = "mrc";
    }
};


int
main()
{
  json users;
  json blogs;
  {
    AsyncWorker worker1("http://my.dev:5000/api/v0/blogs", users);
    AsyncWorker worker2("http://my.dev:5000/api/v0/users", blogs);
  }
  std::cout << "Main thread\n";
  std::cout << "Users: " << users.dump(2) << "\n";
  std::cout << "Blogs: " << blogs.dump(2) << "\n";
  return 0;
}
