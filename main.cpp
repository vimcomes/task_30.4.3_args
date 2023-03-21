// Module 30.4 task 3
#include <iostream>
#include <cpr/cpr.h>
#include <map>
#include <vector>

void getRequest (std::map<std::string, std::string> &arguments)
{
    std::string url = "http://httpbin.org/get?";
    for (std::map<std::string, std::string>::iterator it = arguments.begin();;)
    {
        url += (it->first + "=" + it->second);
        it++;
        if (it != arguments.end()) {
            url += "&";
        } else { break; }
    }
    cpr::Response response = cpr::Get(cpr::Url(url));
    if (response.status_code == 200)
    {
        std::cout << response.text;
    } else {
        std::cerr << "Request failed: " << response.status_code << std::endl;
    }

}

void postRequest (std::map<std::string, std::string> &arguments)
{
    std::vector<cpr::Pair> vec;
    for (std::map<std::string, std::string>::iterator it = arguments.begin(); it != arguments.end(); it++ )
    {
        cpr::Pair pair(it->first, it->second);
        vec.push_back(pair);
    }
    cpr::Response response = cpr::Post(cpr::Url("http://httpbin.org/post"),
                               cpr::Payload(vec.begin(), vec.end()));
    if (response.status_code == 200) {
        std::cout << response.text;
    } else {
        std::cerr << "Request failed: " << response.status_code << std::endl;
    }

}

int getArg (std::map<std::string, std::string> &arguments)
{
    std::string key, value;
    while (true)
    {
        std::cout << "Enter key: " << std::endl;
        std::cin >> key;
        if (key == "get")
        {
            return 1;
        } else if (key == "post")
        {
            return 2;
        }
        std::cout << "Enter value: " << std::endl;
        std::cin >> value;
        arguments.insert(std::pair<std::string, std::string>(key, value));
    }
}

int main()
{
    std::map<std::string, std::string> arguments;
    if (getArg(arguments) == 1)
    {
        getRequest(arguments);
    } else {
        postRequest(arguments);
    }
    return 0;
}