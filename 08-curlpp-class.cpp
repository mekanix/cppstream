#include <iostream>
#include <string>
#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <nlohmann/json.hpp>


using json = nlohmann::json;


class RestApi
{
  protected:
    static const std::string _urlBase;
    curlpp::Easy _request;
};

const std::string RestApi::_urlBase = "http://freenit.hal9000.home.meka.rs:5000/api/v0";


class UserApi : public RestApi
{
  public:
    json fetch(const unsigned &id)
    {
      try
      {
        std::stringstream url;
        std::stringstream buffer;
        url << _urlBase << "/users/" << id;
        curlpp::Cleanup cleanup;
        _request.setOpt(curlpp::Options::Url(url.str()));
        curlpp::options::WriteStream ws(&buffer);
        _request.setOpt(ws);
        _request.perform();
        auto statusCode = curlpp::Infos::ResponseCode::get(_request);
        if (statusCode >= 400)
        {
          std::cerr << "Error: " << statusCode << "\n";
          exit(1);
        }

        return json::parse(buffer.str());
      }
      catch (const curlpp::RuntimeError &e)
      {
        std::cerr << "Runtime error: " << e.what() << '\n';
        exit(2);
      }
      catch (const curlpp::LogicError &e)
      {
        std::cerr << "Logic error: " << e.what() << '\n';
        exit(3);
      }
    }

    json fetchAll()
    {
      try
      {
        std::stringstream url;
        std::stringstream buffer;
        url << _urlBase << "/users";
        curlpp::Cleanup cleanup;
        _request.setOpt(curlpp::Options::Url(url.str()));
        curlpp::options::WriteStream ws(&buffer);
        _request.setOpt(ws);
        _request.perform();
        auto statusCode = curlpp::Infos::ResponseCode::get(_request);
        if (statusCode >= 400)
        {
          std::cerr << "Error: " << statusCode << "\n";
          exit(1);
        }

        return json::parse(buffer.str());
      }
      catch (const curlpp::RuntimeError &e)
      {
        std::cerr << "Runtime error: " << e.what() << '\n';
        exit(2);
      }
      catch (const curlpp::LogicError &e)
      {
        std::cerr << "Logic error: " << e.what() << '\n';
        exit(3);
      }
    }
};


int
main()
{
  UserApi userApi;
  auto response = userApi.fetch(1);
  std::cout << response.dump(2) << '\n';
  return 0;
}
