#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


/*
 * {
 *   "jedan": "dva",
 *   "broj": 1,
 *   "niz": [
 *     "nekoliko",
 *     "stvari"
 *   ],
 *   "objekat": {
 *     "nestovani": "objekat"
 *   }
 * }
 */


/*
 * {
 *   "pi": 3.14,
 *   "answer": {
 *     "everything": 42
 *   },
 *   "niz": [ 1, 2, 3 ]
 * }
 */

int
main()
{
  json j;
  j["pi"] = 3.14;
  j["answer"]["everything"] = 42;
  j["niz"] = {1, 2, 3};
  std::cout << j.dump(2) << "\n\n";

  auto j2 = R"(
    {
      "broj": 3,
      "cvrc": {
        "nested": "nesto",
        "opala": "cupala"
      }
    }
  )"_json;
  std::cout << j2.dump(2) << "\n\n";

  std::string s = "{ \"jedan\": 2 }";
  auto j3 = json::parse(s);
  std::cout << j3["jedan"] << "\n";
  std::cout << j3.dump(2) << "\n\n";
  return 0;
}
