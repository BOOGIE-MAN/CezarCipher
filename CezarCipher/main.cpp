#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <unordered_map>

#define charShiftedByKey ((int)input[i] + (key))

char getChar(const char c, const int key) { return (char)(((int)c - key) + 26 * (((int)c - key) < (int)'a')); }

int main()
{
	std::string input;
	constexpr short alen = 26;
	int key;
	const char* statsPath = "statisticsEn.txt";
	const char* messagePath = "secretMessage.txt";

	std::fstream fStat, fCypher;

	while (input != "0")
	{
		std::cout << "[0] \t CLOSE\n";
		std::cout << "[1] \t ENCRYPT\n[2] \t AUTO DECODE\n\n";
		
		std::cout << "> your choice = ";
		std::getline(std::cin, input);
		std::cout << '\n';

		if (input == "1")
		{
			std::cout << "> enter message: "; 
			std::getline(std::cin, input);
			
			std::cout << "> enter key: \t"; 
			std::string skey;
			std::getline(std::cin, skey);
			key = std::stoi(skey);
			std::cout << std::endl;

			key %= alen;

			fCypher.open(messagePath, std::ios::out);
			for (int i = 0; i < input.length(); i++)
				fCypher << (isalpha(input[i]) ? (char)(charShiftedByKey - alen * (charShiftedByKey >(int)'z')) : input[i]);
			fCypher.close();
		}
		else if (input == "2")
		{
			fCypher.open(messagePath, std::ios::in);
			if (fCypher.good())
				std::cout << "File read successfully!\n\n";
			else
			{
				std::cout << "failed to read the file!\nEnding execution. Press [enter] to quit";
				std::cin.get();
				break;
			}

			std::getline(fCypher, input);
			fCypher.close();

			fStat.open(statsPath);

			std::unordered_map<char, int> a;
			std::unordered_map<char, float>stats;
			std::string temp;
			std::string decrypted;


			double error = 0.0, ehold = 1.0, stat;
			char letter;
			int Fline = alen;

			while (Fline--)
			{
				fStat >> letter;
				fStat >> stat;
				stats[letter] = stat * 0.01;
			}

			fStat.close();

			int keyPred;
			for (int k = 0; k < alen; k++)
			{
				error = 0.0;

				for (auto& c : input)
				{
					if (isalpha(c))
					{
						auto newChar = getChar(c, k);
						a[newChar]++;
						temp += newChar;
					}
					else
						temp += c;
				}

				for (auto& i : a)
					error += abs((stats[i.first] - i.second) / (float)input.length());
				a.clear();

				if (error < ehold)
				{
					ehold = error;
					keyPred = k;
					decrypted = temp;
				}
				temp.clear();
			}
			std::cout << "predicted key: " << keyPred << std::endl;
			std::cout << "decrypted text: " << decrypted << std::endl << std::endl;
		}

		std::cout << "-----------------------------------------------------------------------------\n";
	}
	std::cout << "==================================== END ====================================\n";

	std::cin.get();
}