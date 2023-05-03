#include "VarDetect.h"
#pragma STDC FENV_ACCESS on
namespace AndyInt {
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
        if (pic == " ") {
            if (hasiden) hasspa = true;
            return true;
        }
        else if (pic == "-") {
            if ((iaft > 64 && iaft < 91) || (iaft > 96 && iaft < 123) || (iaft > 47 && iaft < 58) || aft == ".") {
                if (hase) {
                    expneg = true;
                }
                else {
                    neg = true;
                }
                haniden();
                return true;
            }
            else {
                return false;
            }
        }
        else if ((ipic > 64 && ipic < 91) || (ipic > 96 && ipic < 123)) {
            if (pic == "e") {
                if ((iaft > 64 && iaft < 91) || (iaft > 96 && iaft < 123) || (ibef > 64 && ibef < 91) || (ibef > 96 && ibef < 123)) {
                    hantext(pic);
                    return true;
                }
                else {
                    if ((iaft > 47 && iaft < 58) || aft == "-") {
                        hase = true;
                        changType();
                        haniden();
                        return true;
                    }
                    else {
                        ahand.report(17);
                    }
                }
            }
            else {
                hantext(pic);
                return true;
            }
        }
        else if (pic == "." || (ipic > 47 && ipic < 58)) {
            if (pic == ".") {
                if (decimal) {
                    ahand.report(16);
                }
                changType();
                haniden();
                decimal = true;
                return true;
            }
            else {
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
                changType();
                haniden();
                return true;
            }
        }
        else if (pic == "#") {
            type = typeNode;
            changType();
            haniden();
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
        hasiden = false;
        hasspa = false;
        type = typeNone;
        type1 == typeNone;
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
        std::feclearexcept(FE_ALL_EXCEPT);
        ret = val * pow(10, exp);
        if (std::fetestexcept(FE_OVERFLOW)) {
            ahand.report(29);
            return 0;
        }
        return ret;
    }

    void VarDetect::hantext(std::string aprt)
    {
        varnam += aprt;
        type = typeVar;
        funval = -1;
        for (int i = 0; i < 16; i++) {
            if (trans.oFunNames[i] == varnam) {
                type = typeIntern;
                funval = i;
                break;
            }
        }
        for (int i = 0; i < trans.funNames.size(); i++) if (varnam == trans.funNames.at(i)) {
            type = typeExtern;
            funval = i + 16;
            break;
        }
        type1 = (type == typeExtern || type == typeIntern) ? typeFunc : typeVar;
        haniden();
    }

    void VarDetect::haniden()
    {
        if (hasspa) ahand.report(25);
        hasiden = true;
    }
    void VarDetect::changType()
    {
        type1 = type;
    }
}