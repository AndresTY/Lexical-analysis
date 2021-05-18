#include <iostream>
#include <map>
#include <regex>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>
//vectors
std::vector<std::string> PR = { "std","auto","const","double","float","int","short","struct","unsigned","break","continue","else","for","long","signed","switch","void","case","default","enum","goto","register","sizeof","typedef","volatile","char","do","extern","if","return","static","union","while","include","asm","dynamic_cast","namespace","reinterpret_cast","try","bool","explicit","new","static_cast","typeid","catch","operator","template","typename","class","friend","private","this","using","const_cast","inline","public","throw","virtual","delete","mutable","protected","wchar_t","and","bitand","compl","not_eq","or_eq","xor_eq","bitor","not","or","xor"};
std::vector<std::string> OR = {">","<","==","!=","<=",">=","&","|"};
std::vector<std::string> SP = {"[",".","]","{","}","(",")",";",":","#",",","_","@","!","$","%","^","\\"};
std::vector<std::string> Library = {"cassert","cctype","cerrno","cfernv","cfloat","cinttypes","ciso646","climitis","clocale","cmath","csetjmp","csignal","cstdarg","cstdbool","cstddef","cstdint","cstdio","cstdlib","cststring","ctgmath","ctime","cuchar","cwchar","cwctype","array","deque","forward_list","list","map","queue","set","stack","unordered_map","unordered_set","vector","fstream","iomanip","ios","iosfwd","iostream","istream","ostream","sstream","streambuf","atomic","condition_variable","future","mutex","thread","algorithm","bitset","chrono","codecvt","complex","exception","funtional","initializer_list","iterator","limits","locale","memory","numeric","random","ratio","regex","stdexcept","string","systerm_error","tuple","typeindex","typeinfo","type_traits","utility","valarray"};
std::vector<std::string> OM ={"+","-","*","%","/","**"};
std::unordered_map<std::string,int> Full_summary= {{"identifier",0},{"identifierE",0},{"Keyword",0},{"Library",0},{"Separator",0},{"Math operator",0},{"Relational operator",0},{"Asignation operator",0},{"Boolean literal",0},{"Numberal literal",0},{"String literal",0},{"Comments",0}};

void splitted(std::string filename){
	std::string temp;
	std::string temp2;
	std::string str="";
	std::fstream fs, data;
	fs.open(filename,std::fstream::in);
	data.open("lexi.txt",std::fstream::out);
	while(!fs.eof()){
		fs>>temp;
		str+=temp+"\n";
	}
	data<<str;
	fs.close();
	data.close();
}

void splitted2(){
	std::string temp;
	std::string temp2;
	std::string str="";
	bool str_flag = false;
	bool chr_flag = false;
	int comm_flag = 0;
	std::fstream fs, data;
	fs.open("lexi.txt",std::fstream::in);
	data.open("lexi2.txt",std::fstream::out);
	while(!fs.eof()){
		fs>>temp;
		for(auto& a: temp){
			if(a!='/'&&comm_flag==2){
				str+=a;
			}else if(a=='/'){
				str=str+a;
				comm_flag++;
			}else if(a!='\"'&&str_flag==true){
				str+=a;
			}else if(a=='\"'&&str_flag==true){
				str= str +a+"\n";
				str_flag=false;
			}else if(a=='\"'&&str_flag==false){
				str=str+"\n"+a;
				str_flag=true;
			}else if(a!='\''&&chr_flag==true){
				str+=a;
			}else if(a=='\''&&chr_flag==true){
				str= str +a+"\n";
				chr_flag=false;
			}else if(a=='\''&&chr_flag==false){
				str=str+"\n"+a;
				chr_flag=true;
			}else if(!isalpha(a)&&a!='_'){
				if(isdigit(a)){
					str+=a;
				}else{
					str=str+"\n"+a+"\n";
				}
			}else{
				str+=a;
			}
		}
		if(str_flag||comm_flag==2){
			str+="";
			comm_flag=0;
		}else{
			str+="\n";
			comm_flag=0;
			chr_flag=false;
		}
	}
	data<<str;
	fs.close();
	data.close();
}

void lexmico(){
	std::string temp,str,str_class;
	int op;
	std::fstream data,fs;
	std::regex re_varibles ("([A-Za-z_]*|[0-9]*?)");
	std::regex re_number ("([0-9.e]*?)");
	std::regex re_string ("\"(.*)\"|\'(.*)\'?");
	std::regex re_comm ("//(.*)?");
	fs.open("result.csv",std::fstream::out);
	fs.clear();
	data.open("lexi2.txt",std::fstream::in);
	fs<<"Name Token"<<","<<"token"<<","<<"token class"<<","<<"desc"<<"\n";
	while(!data.eof()){
		data>>temp;
		if(std::find(PR.begin(),PR.end(),temp) != PR.end()){
			op = 2;
			str_class="Keyword";
			str=" ";
			Full_summary[str_class]++;
		}else if(std::find(OR.begin(),OR.end(),temp) != OR.end()){
			op = 4;
			str_class="Operator";
			str="Relational operator";
			Full_summary[str]++;
		}else if(std::find(SP.begin(),SP.end(),temp) != SP.end()){
			op=3;
			str_class="Separator";
			str = "Special Simbol";
			Full_summary[str_class]++;
		}else if(std::find(Library.begin(),Library.end(),temp) != Library.end()){
			op=2;
			str = "Library";
			str_class="Keyword";
			Full_summary[str]++;
		}else if(std::regex_match(temp,re_number)){
			op=5;
			str="number";
			str_class="literal";
			Full_summary["Numberal literal"]++;
		}else if(temp == "="){
			op =4;
			str = "Asignation operator";
			str_class = "Operator";
			Full_summary[str]++;
		}else if(std::find(OM.begin(),OM.end(),temp) != OM.end()){
			op=4;
			str = "Math operator";
			str_class = "Operator";
			Full_summary[str]++;
		}else if(temp=="true"||temp=="false"){
			op = 5;
			str = "boolean";
			str_class = "literal";
			Full_summary["Boolean literal"]++;
		}else if(std::regex_match(temp,re_string)){
			op=5;
			str="string";
			str_class = "literal";
			Full_summary["String literal"]++;
		}else if(std::regex_match(temp,re_comm)){
				op=6;
				str=" ";
				str_class="commet";
			Full_summary["Comments"]++;
		}else if(std::regex_match(temp,re_varibles)){
			op=1;
			str_class="identifier";
			str=" ";
			Full_summary["identifier"]++;
		}else{
			op=1;
			str_class="identifier";
			str="Error";
			Full_summary["identifierE"]++;
		}
		fs<<temp<<","<<op<<","<<str_class<<","<<str<<"\n";
		
	}
	fs.close();
	data.close();

}

void full(){
	std::cout<<"====Full summary===="<<"\n";
	for(auto& e: Full_summary){
		std::cout<<e.first<<":"<<e.second<<"\n";
	}
}

void partular(){
	std::unordered_map<std::string,int> temp={{"identifier",Full_summary["identifier"]+Full_summary["identifierE"]},{"Keyword",Full_summary["Keyword"]+Full_summary["Library"]},{"Separator",Full_summary["Separator"]},{"Operator",Full_summary["Math operator"]+Full_summary["Relational operator"]+Full_summary["Asignation operator"]},{"literal",Full_summary["Boolean literal"]+Full_summary["Numberal literal"]+Full_summary["String literal"]},{"Comments",Full_summary["Comments"]}}; 
	std::cout<<"====Particular summary===="<<"\n";
	for(auto& e: temp){
		std::cout<<e.first<<":"<<e.second<<"\n";
	}
}

void specify(std::string n){
	std::unordered_map<std::string,int> temp={{"Identifier",Full_summary["identifier"]+Full_summary["identifierE"]},{"Keyword",Full_summary["Keyword"]+Full_summary["Library"]},{"Separator",Full_summary["Separator"]},{"Operator",Full_summary["Math operator"]+Full_summary["Relational operator"]+Full_summary["Asignation operator"]},{"literal",Full_summary["Boolean literal"]+Full_summary["Numberal literal"]+Full_summary["String literal"]},{"Comments",Full_summary["Comments"]}}; 

	if(temp.find(n)==temp.end()){
		std::cout<<"not found token"<<"\n";
	}else{
		std::cout<<temp.find(n)->first <<":"<< temp.find(n)->second<<"\n";
	}
}

void summary(int type_summary){
	std::string req_token;
	switch(type_summary)
	{
		case 1:
			full();
			break;
		case 2:
			partular();
			break;
		case 3:
			std::cout<<"What token do you want?"<<"\n";
			std::cin>>req_token;
			specify(req_token);
			break;
	}
}
std::string menu(){
	return"===== How summary do you want? =====\n1. full summary \n2. particular summary\n3. summary especially\n *. close\n";
}
void start(){
	int a;
	bool t=true;
	std::string file;
	std::cout<<"file to analyze: ";
	std::cin>>file;
	std::ifstream check(file);
	if(!check.good()){
		std::cout<<"no found file"<<"\n";
		exit(EXIT_FAILURE);
	}

	splitted(file);
	splitted2();
	lexmico();
	do{
		std::cout<<menu();
		std::cin>>a;
		summary(a);
		if(a>3){
			t=false;
		}
	}while(t);
}

int main(){
	start();
	return 0;
}
