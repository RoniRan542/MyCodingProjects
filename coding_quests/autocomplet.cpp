/*************************************************
 *Name : Ran Aharon Cohen	 	    			 *
 *Date: 	19.07.22		            		 *
 *Description : Implement Autocomplete function  *
 *************************************************/
#include <iostream>
#include <vector>
#include <list>

std::list<std::string> Autocomplete(const std::string &query,
                                    std::vector<std::string> strings)
{
    std::list<std::string> ret_list;
    for (const auto &str : strings)
    {
        bool is_fit = true;
        for (size_t i = 0; i < query.length(); ++i)
        {
            if (query[i] != str[i])
            {
                is_fit = false;
                break;
            }
        }

        if (is_fit)
        {
            ret_list.push_front(str);
        }
    }

    return ret_list;
}

int main()
{
    std::vector<std::string> strings = {"dog", "deer", "deal"};

    std::list<std::string> ret_vec = Autocomplete("de", strings);
    for (std::list<std::string>::iterator it = ret_vec.begin(); it != ret_vec.end(); ++it)
    {
        std::cout << it->data() << std::endl;
    }

    return 0;
}
