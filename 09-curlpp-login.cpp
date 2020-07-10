#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <nlohmann/json.hpp>


using json = nlohmann::json;


class YesNo
{
  public:
    explicit YesNo(bool yn) : yesno(yn) {}
    std::string operator()() const
    {
        return yesno ? "Yes" : "No";
    }
    friend std::ostream &operator<<(std::ostream &strm, const YesNo &yn)
    {
        strm << yn();
        return strm;
    }

  private:
    bool yesno;
};


struct MyCookie
{
  static std::map<std::string, MyCookie *> cookies;
  MyCookie(const std::string &_name)
  {
    name = _name;
    cookies[name] = this;
  }
  std::string name;
  std::string value;
  std::string domain;
  std::string path;
  time_t expires;
  bool tail;
  bool secure;

  static void print()
  {
    for (auto const &cookie : cookies)
    {
      std::cout << cookie.first << ": " << cookie.second->value << '\n';
    }
  }
};
std::map<std::string, MyCookie *> MyCookie::cookies;


std::ostream &
operator<<(std::ostream &strm, const MyCookie &cook)
{
  strm << "Cookie: '" << cook.name << "' (secure: " << YesNo(cook.secure) << ", tail: "
    << YesNo(cook.tail) << ") for domain: '" << cook.domain << "', "
    << "path: '" << cook.path << "'.\n";
  strm << "Value: '" << cook.value << "'.\n";
  strm << "Expires: '" << ctime(&cook.expires) << "'.\n";
  return strm;
}


std::vector<std::string> &
split_cookie_str(const std::string &str, std::vector<std::string> &in)
{
  std::string part;
  std::istringstream strm(str);
  while (getline(strm, part, '\t')) { in.push_back(part); }
  return in;
}


std::vector<std::string>
splitCookieStr(const std::string &str)
{
  std::vector<std::string> split;
  split_cookie_str(str, split);
  return split;
}


std::vector<std::string> &
splitCookieStr(const std::string &str, std::vector<std::string> &in)
{
  return split_cookie_str(str, in);
}


int StrToInt(const std::string &str)
{
  std::istringstream strm(str);
  int i = 0;
  if (!(strm >> i)) {
    throw curlpp::RuntimeError("Unable to convert string '" + str + "' to integer!");
  }
  return i;
}


MyCookie *
MakeCookie(const std::string &str_cookie)
{
  std::vector<std::string> vC = splitCookieStr(str_cookie);
  auto cook = new MyCookie(vC[5]);

  cook->domain = vC[0];
  cook->tail = vC[1] == "TRUE";
  cook->path = vC[2];
  cook->secure = vC[3] == "TRUE";
  cook->expires = StrToInt(vC[4]);
  cook->value = vC[6];

  return cook;
}


class RestApi
{
  protected:
    static const std::string _urlBase;
    curlpp::Easy _request;
};

const std::string RestApi::_urlBase = "http://freenit.hal9000.home.meka.rs:5000/api/v0";


class LoginApi : public RestApi
{
  public:
    json login(const std::string &email, const std::string &password)
    {
      try
      {
        std::stringstream url;
        std::stringstream buffer;
        json body;
        body["email"] = email.data();
        body["password"] = password.data();
        url << _urlBase << "/auth/login";
        curlpp::Cleanup cleanup;
        _request.setOpt(curlpp::Options::Url(url.str()));
        curlpp::options::WriteStream ws(&buffer);
        _request.setOpt(ws);
        std::list<std::string> header;
        header.push_back("Content-Type: application/json");
        header.push_back("Accept: application/json");
        _request.setOpt(new curlpp::options::HttpHeader(header));
        // _request.setOpt(new curlpp::options::Verbose(true));
        _request.setOpt(curlpp::options::CookieList("Set-Cookie: FREENIT=TRUE"));

        auto const &bodyRaw = body.dump();
        _request.setOpt(new curlpp::options::PostFields(bodyRaw.data()));
        _request.setOpt(new curlpp::options::PostFieldSize(bodyRaw.size()));

        _request.perform();
        auto statusCode = curlpp::Infos::ResponseCode::get(_request);
        if (statusCode >= 400)
        {
          std::cerr << "Error: " << statusCode << "\n";
          exit(1);
        }

        std::list<std::string> cookies;
        curlpp::infos::CookieList::get(_request, cookies);
        for (auto const &cookie : cookies) { MakeCookie(cookie); }
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
  LoginApi loginApi;
  auto response = loginApi.login("admin@example.com", "Sekrit");
  // std::cout << response.dump(2) << '\n';
  MyCookie::print();
  // std::cout << *(MyCookie::cookies["access_token_cookie"]) << '\n';
  // try
  // {
    // StrToInt("sdfvdsfvd");
  // }
  // catch (const curlpp::RuntimeError &e)
  // {
    // std::cerr << "Runtime error: " << e.what() << '\n';
    // exit(4);
  // }
  return 0;
}
