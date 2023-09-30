#include "Validate.h"

bool validate::validateName(std::string& name){
    for (char c: name)
        if (!isalpha(c) && !isspace(c))
            return false;

    return true;
}
bool validate::validateID(std::string& stringID){
    if (stringID.size() != 8)
        return false;

    return validateNumber(stringID);
}
bool validate::validateNumber(std::string& stringNum){
    for (char c: stringNum)
        if (!isdigit(c))
            return false;

    return true;
}