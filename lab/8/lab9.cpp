	#include <iostream>
	#include <map>

	int main(){

	int in;
	std::map<int, int> occurances;

	int current_mode_occurances = 0;
	while(std::cin >> in){
		/*
		occurances[in]++;
		if(occurances[in] > current_mode_occurances){
			current_mode_occurances = occurances[in];
		}
		//*/
		///*
		if(occurances.find(in) == occurances.end()){
			occurances.insert( std::pair<int,int>(in,1) );
		}else{
			occurances.find(in)->second++;
		}
		if(occurances.find(in)->second > current_mode_occurances){
			current_mode_occurances = occurances.find(in)->second;
		}
		//*/

	}

	for(std::map<int, int>::iterator itr = occurances.begin(); itr != occurances.end(); itr++){
		if(itr->second == current_mode_occurances){
			std::cout << itr->first << ": " << itr->second << std::endl;
		}
	}


	return 0;
	}