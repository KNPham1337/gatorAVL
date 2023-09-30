/*

    Validate Class will be used to validate name, ID, and number

*/

#include <string>

class validate{
    validate(){}
    ~validate(){}

    public:
    
    static bool validateName(std::string& name);
    static bool validateID(std::string& stringID);
    static bool validateNumber(std::string& stringNum);
};