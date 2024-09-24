#include <stdio.h>
#include <iostream>
#include <string>
int main(){
	std::string linea;
        int cont=0;
        while(cont<10 && std::getline(std::cin, linea)){
		std::cout << linea << std::endl;
		cont++;
        }
	return 0;
}

