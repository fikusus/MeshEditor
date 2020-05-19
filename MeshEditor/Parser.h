#pragma once
class Parser
{
public:
	static void parce(int argc, char *argv[], std::map<std::string, std::string>& parsedText) {
		int i = 4;
		std::string s1, s2;
		while (i < argc)
		{
			s1 = argv[i - 2];
			s2 = argv[i];
			if (s2[0] == '(' && argv[i + 2][strlen(argv[i + 2])-2] == ')') {

				s2 += argv[i + 1];
				s2 += argv[i + 2];
				i += 2;
			}
			clearStr(s1);
			clearStr(s2);
			parsedText.insert(std::pair<std::string, std::string>(s1, s2));
			i += 3;

		}
	}
private:
	static void clearStr(std::string& str) {
		if (str[str.length() - 1] == ',') {
			str.erase(str.begin() + str.length() - 1);
		}
	}
};
