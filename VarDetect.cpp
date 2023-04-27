#include "VarDetect.h"

bool VarDetect::isAccepted(std::string text, int pla)
{
    if (pla >= text.length()) {
        node = false;
        return false;
    }
    
    std::string pic = text.substr(pla, 1);
    node = (pic == "#");
    int ipic = meth.asc(pic);
    std::string aft = "";
    if (pla < text.length() - 1) aft = text.substr(pla + 1, 1);
    int iaft = meth.asc(aft);
    std::string bef = "";
    if (pla > 0) bef = text.substr(pla - 1, 1);
    int ibef = meth.asc(bef);
    if (pic == "-") {
        if ((iaft > 64 && iaft < 91) || (iaft > 96 && iaft < 123) || (ipic > 47 && ipic < 58) || pic == ".") {
            if (hase) {
                expneg = true;
            }else {
                neg = true;
            }
            return true;
        }else{
            return false;
        }
    }
    if ((ipic > 64 && ipic < 91) || (ipic > 96 && ipic < 123)) {
        if (pic == "e") {
            if ((iaft> 64 && iaft < 91) || (iaft > 96 && iaft < 123) || (ibef > 64 && ibef < 91) || (ibef > 96 && ibef < 123)) {
                varnam += pic;
                type = typeVar;
                return true;
            }else{
                if ((iaft > 47 && iaft < 58) || aft == "-") {
                    hase = true;
                }else{
                    //report error
                }
            }
        }
        else {
            varnam += pic;
            type = typeVar;
            return true;
        }        
    }else if (pic == "." || (ipic > 47 && ipic < 58)) {
        if (pic == ".") {
            if (decimal) {
                //report error
            }
            decimal = true;
            return true;
        }else{
            if (hase) {
                exp *= 10;
                exp += ipic - 48;
            }
            else {
                type = typeNum;
                if (decimal) {
                    dplas++;
                    val += pow(10, -dplas) * (ipic - 48);
                }
                else {
                    val *= 10;
                    val += ipic - 48;
                }
            }
            return true;
        }
    }
    else if (pic == "#") {
        type = typeNode;
        return true;
    }
    
    return false;
}

void VarDetect::clear()
{
    varnam = "";
    neg = false;
    decimal = false;
    numneg = false;
    expneg = false;
    hase = false;
    dplas = 0;
    exp = 0;
    val = 0;
    node = false;
}

varinc VarDetect::getVal()
{
    varinc ret;
    ret.neg = neg;
    ret.num = vars.getRef(varnam);
    return ret;
}

double VarDetect::getNum()
{
    if (numneg) val = -val;
    if (expneg) exp = -exp;
    double ret;
    try {
        ret = val * pow(10, exp);
    }
    catch (_exception e) {
        //report error
        ret = 0;
    }
    return ret;
}


