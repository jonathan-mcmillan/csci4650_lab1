#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
using namespace std;

string letterFreq = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
char checkChar = 'A';
int alphaSize = 26;


string decryptText(string key, string ctext){
        string dtext = "";
        int pos = 0;
        for(int i = 0; i < ctext.size(); i++){
                pos = key.find(ctext[i]);
                dtext = dtext + letterFreq[pos];
        }

        return dtext;
}

string getText(string arg, char c){
	fstream txt(arg.c_str(), fstream::in);
	string text;
	getline(txt, text, c);
	txt.close();

	return text;
}

int getCount(string dict, string dtext){
        int count = 0;
	
	ifstream infile(dict.c_str());
	string line;
	
	while(getline(infile, line)){	
		if(dtext.find(line.substr(0, line.size()-1)) != string::npos){
			count++;
		}
	}

	infile.close();
        return count;
}

string freqAnalysis(string ciphertext){
	int count[alphaSize];
        for(int i = 0; i < alphaSize; i++){
                count[i] = 0;
        }

        for(int i = 0; i < ciphertext.size(); i++){
                for(int k = 0; k < alphaSize; k++){
                        if(ciphertext[i] == checkChar + k){
                                count[k]++;
                        }
                }
        }
	
	//display frequency of chracters in ciphertext
	for(int i = 0; i < alphaSize; i++){
		cout << "Number of " << char(checkChar + i) << "'s = " << count[i] << "\n";
	}

	int largest = count[0];
        int times = 0;
        int n = 0;
        string key = "";

        while(times != alphaSize){
                largest = count[0];
                n = 0;
                for(int i = 0; i < alphaSize; i++){
                        if(largest < count[i]){
                                largest = count[i];
                                n = i;
                        }
                }
                key = key +  char(checkChar + n);
                times++;
                count[n] = 0;
        }

        for(int i = 0; i < alphaSize; i++){
                if(!(key.find(char(checkChar + i)) != std::string::npos))
                        key[alphaSize - 1] = char(checkChar + i);
        }
        
	return key;
} 

int main(int argc, char *argv[]){
	//Error checking
	if(argc !=  3){
		cout << "Invalid number of arguments.\n";
		cout << "Please give arguments in the following manner:\n";
		cout << "./crypt <ciphertext> <dictionary>\n";
		
		return 0;
	}

	cout << "\n";

	string ciphertext = getText(argv[1], '\0');
	
	//Get frequency of characters in ciphertext
	string key = freqAnalysis(ciphertext);
                 
	cout << "\nKey mapped to most frequent letters: ";
	cout << key << "\n";

	string decipheredText = decryptText(key, ciphertext);
	cout << "The deciphered text is: \n";
	cout << decipheredText << "\n";

	int cnt = getCount(argv[2], decipheredText);

	cout << "Total number of words from dictionary that are in deciphered text: " << cnt << "\n\n";
	
	cout << "Now key will be permuted to find a larger amount of words from dictionary found in deciphered text.\n\n";
	string newKey;
	string newdecipheredText;
	int newCount;
	for(int i = 0; i < alphaSize - 4; i++){
		for(int k = 1; k <= 4; k++){
			newKey = key;
			swap(newKey[i], newKey[i+k]);
			newdecipheredText = decryptText(newKey, ciphertext);
			newCount = getCount(argv[2], newdecipheredText);
			
			if(newCount > cnt){
				k = 0;
				cnt = newCount;
				key = newKey;
				decipheredText = newdecipheredText;
			}
		}
	}
	
	cout << "The key with the largest amount of words found from dictionary is: " << key << "\n";
	cout << "The total number of words found from the dictionary is: " << cnt << "\n";
	cout << "The deciphered text is\n" << decipheredText << "\n\n";	
	
	int ynNum;
	cout << "If you would like to permute the key yourself, enter '1'.\n";
	cout << "If you don't wish to permute the key anymore, enter '0'.\n";

	cin >> ynNum;
	if(ynNum == 1){
		cout << "\nYou have decided to permute the key yourself, the key must be 26 letters long.\n";
		string userKey;

		while(1){
			cout << "Please enter the key you wish to test: ";
			cin >> userKey;
			transform(userKey.begin(), userKey.end(), userKey.begin(), ::toupper);

			if(userKey.size() == 26){
				newdecipheredText = decryptText(userKey, ciphertext);
				newCount = getCount(argv[2], newdecipheredText);

				cout << "\nKey given: " << userKey << "\n";
				cout << "Number of words found from dictionary: " << newCount << "\n";
				cout << "The deciphered text is\n" << newdecipheredText << "\n\n";
				
				cout << "Would you like to permute another key yourself?\n";
				cout << "1 - yes\n0 - no\n";
				cin >> ynNum;
				
				if(ynNum != 1){
					break;
				}
			}
			else{
				cout << "The input you gave was invalid, key must be 26 letters long.\n";
			}
		}
	}
	
	cout << "Closing program, goodbye!\n";
 
	return 0;
}
