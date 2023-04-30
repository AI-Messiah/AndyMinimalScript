#include "ResCheck.h"

ResCheck::ResCheck()
{
	std::string resWords[] = { "def", "if", "else", "while", "goto", "exit"};
	for (int i = 0; i < 6; i++) words.push_back(resWords[i]);	
}

void ResCheck::Check(std::string text)
{
	std::string comwrd;
	std::string bef = "";
	std::string aft = "";
	int comlen;
	int ibef, iaft;
	if (text.length() > 1) {
		for (int i = 0; i < text.length() - 1;i++) {
			for (int j = 0; j < 6; j++) {
				comwrd = words.at(j);
				if (i + comwrd.length() <= text.length()) {
					comlen = comwrd.length();
					if (text.substr(i, comlen) == comwrd) {
						if (i > 0) bef = text.substr(i - 1, 1);
						ibef = meth.asc(bef);
						aft = "";
						if (i + comlen < text.length()) aft = text.substr(i + comlen, 1);
						iaft = meth.asc(aft);
						if (!((iaft > 64 && iaft < 91) || (iaft > 96 && iaft < 123) || (ibef > 64 && ibef < 91) || (ibef > 96 && ibef < 123))) {
							ahand.report(24);
							return;
						}
					}
				}
			}
		}
	}
}
