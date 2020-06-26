#include <iostream>
#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <nlohmann/json.hpp>


using json = nlohmann::json;


int
main()
{
  std::stringstream buffer;
  // std::cout << "sdfvdfsv" << ' ' << 3 << ' ' << 6.2 << ' ' << '4';
  // buffer << "\nsdfvdfsv" << ' ' << 3 << ' ' << 6.2 << ' ' << '4';
  // std::cout << buffer.str() << '\n';

  curlpp::Easy myRequest;
  try
  {
    curlpp::Cleanup myCleanup;
    myRequest.setOpt(curlpp::Options::Url(
      "http://freenit.hal9000.home.meka.rs:5000/api/v0/users"
    ));
    curlpp::options::WriteStream ws(&buffer);
    myRequest.setOpt(ws);
    myRequest.perform();
    // std::cout << "buffer: " << buffer.str() << "\n\n";
    auto statusCode = curlpp::Infos::ResponseCode::get(myRequest);
    if (statusCode >= 400)
    {
      std::cerr << "Error: " << statusCode << "\n";
      return 1;
    }
  }
  catch (const curlpp::RuntimeError &e)
  {
    std::cerr << "Runtime error: " << e.what() << '\n';
    return 2;
  }
  catch (const curlpp::LogicError &e)
  {
    std::cerr << "Logic error: " << e.what() << '\n';
    return 3;
  }

  auto jsonData = json::parse(buffer.str());
  std::cout << jsonData["data"].dump(2) << '\n';

  return 0;
}
