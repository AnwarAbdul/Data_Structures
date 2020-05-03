#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>

int get_number(std::string number){
	int num = 0;
	int count = 0;
	for(int i = number.length() - 1; i >= 0; i--){
		num += (number[i] - 0x30) * (int)(pow(10,count));
		count++;
	}
	return num;
}


void add_phonebook(std::string *phonebook, int number, std::string name){
	phonebook[number].replace(0,15,name);
}

std::string find_phonebook(std::string *phonebook, int number){
	if(phonebook[number] == "")
		return "not found";
	else
		return phonebook[number];
}

void delete_phonebook(std::string *phonebook, int number){
	if(phonebook[number] == "")
		return;
	else
		phonebook[number] = "not found";
}

int main(){
	int n;
	std::cin>>n;
	int p = 10000001;
	std::string *phonebook = (std::string*)malloc(sizeof(std::string)*p);
	int i;
	std::string line;
	char temp[50];
	std::cin.ignore();
	std::vector<std::string> tokens;
	std::vector<std::string> output;
	for(i = 0; i < n; i++){
		getline(std::cin,line);
		strcpy(temp,line.c_str());
		char *token = strtok(temp," ");
		char tmp[20];
		tokens.clear();
		while(token != NULL){
			strcpy(tmp,token);
			tokens.push_back(tmp);
			token = strtok(NULL," ");
		}
		int number = get_number(tokens[1]);
		if(tokens[0] == "add")
			add_phonebook(phonebook,number,tokens[2]);
		else if(tokens[0] == "find")
			output.push_back(find_phonebook(phonebook,number));
		else
			delete_phonebook(phonebook,number);
	}
	for(i = 0; i < output.size(); i++)
		std::cout<<output[i]<<"\n";
	free(phonebook);
	return 0;
}
