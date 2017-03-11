#include "GPC_Heuristic.h"


/************************************************
Function:
Initialize GPC network using GPC library

Para:
Library	: GPC library
GPC_Net	: GPC Net to be initialized by GPC library
Max_Col	: Maximum column number for result
Stage	: Total stages of GPC_Net
************************************************/
void Initial_GPC_Net(const std::vector<std::vector<std::pair<std::string, std::vector<int> > > > &Library,
	std::vector<std::vector<std::map<std::string, int> > > &GPC_Net,
	int Max_Col, int Stage){
	std::map<std::string, int> lib_map;
	for (int i = 0; i < (int)Library.size(); ++i){
		for (int j = 0; j < (int)Library[i].size(); j++){
			lib_map[Library[i][j].first] = 0;
		}
	}
	std::vector<std::map<std::string, int> > col_vec;
	for (int i = 0; i < Max_Col; ++i){
		col_vec.push_back(lib_map);
	}

	for (int i = 0; i < Stage; ++i){
		GPC_Net.push_back(col_vec);
	}
}

bool Is_Valid_Result(const std::vector<int> &Columns, int K){
	int len = Columns.size();
	for (int i = 0; i < len; ++i){
		if (Columns[i] > K)
			return false;
	}
	return true;
}

int Get_Out_Widths(const std::vector<int> &columns){
	double sum = 0;
	int len = columns.size();
	for (int i = 0; i < len; ++i)
	{
		sum += columns[i] * pow(2, i);
	}
	int out_width = (int)(ceil(log(sum) / log(2)));
	return out_width;
}

int Get_Used_LUT(const std::string &str){
	int num = 0;
	if (str[str.size() - 1] == '5')
		num = 4;
	if (str[str.size() - 1] == '4')
		num = 3;
	if (str[str.size() - 1] == '3')
		num = 2;
	if (str[str.size() - 1] == '2')
		num =  1;
	//for GPC624,GPC524,GPC424, GPC324,these GPC only cost 2 luts
	if ((str[str.size() - 2] == '2') && (str[str.size() - 3] >= '3') && (str[str.size() - 3] <= '6'))
		num = 2;


	return num;
}

void Write_Heuristic_Message(std::ofstream &OF, const std::vector<int> &Columns,
							const std::vector<std::vector<std::map<std::string, int> > > &GPC_Net,
							int Max_Col, int Stages, int K){
	OF << "####################################################################\n";
	OF << "This is a detail report of GPC network used in heuristic algorithom.\n";
	OF << "####################################################################\n";
	OF << "\n\n";
	OF << "======================Final Left Dots Report======================\n";
	//output final left dots
	OF << "Output dot array  graphy is:\n";
	OF << "(MSB)  ";
	int left_dots = 0;

	for (int i = Max_Col - 1; i >= 0; --i){
		OF << " " << Columns[i];
		//Check if left dots number in every column is less than K
		if (Columns[i] > K){
			OF << "\nFile: " << __FILE__ << "  Line: " << __LINE__ << "\n";
			OF << "ERROR!!! Dots number left in column " << i << " exceed limit " << K << ".\n";
		}
		//Get dots number lefted for carry propagate adder
		left_dots += Columns[i];
	}
	OF << " (LSB)\n";
	OF << "Sum of dos left for Carry Propagate Adder is : " << left_dots << "\n";

	//output output width and total stage
	OF << "Output bit width is:\t" << Max_Col << "\n";
	OF << "GPC network stage is:\t" << Stages << "\n";

	OF << "\n======================Detail GPC Used Message======================";
	//get a new map for area calculation
	std::map<std::string, int> for_area;
	//output GPC messages for every stage
	int GPC_Sum = 0;
	std::map<std::string, int> GPC_Map;
	std::map<std::string, int>::iterator iter;
	for (int i = 0; i < Stages; ++i){
		int row_total = 0;
		OF << "\nGPCs used in stage " << i << ":\n";
		for (int j = 0; j < Max_Col; ++j){
			OF << "\tGPCs used in column " << j << ":\n";
			GPC_Map = GPC_Net[i][j];
			for (iter = GPC_Map.begin(); iter != GPC_Map.end(); ++iter){
				//Initialize map for area
				for_area[iter -> first] = 0;
				if (iter->second > 0){
					//get sum number of GPC in one stage
					row_total += iter->second;
					OF << "\t\t\t\t\t\t" << iter->first << ":" << iter->second << "\n";
				}
			}
		}
		OF << "\tTotal used GPCs in this stage is: " << row_total << "\n";
		//get sum  number of GPC in all stage
		GPC_Sum += row_total;
	}	
	
	OF << "\n======================Resources Used Report======================\n";
	//calculate every gpc used number
	for (int i = 0; i < Stages; ++i){
		for (int j = 0; j < Max_Col; ++j){
			GPC_Map = GPC_Net[i][j];
			for (iter = GPC_Map.begin(); iter != GPC_Map.end(); ++iter){
				if (iter->second > 0)
					for_area[iter->first] += iter->second;				
			}
		}
	}
	//calculate GPC network area
	OF << "Messages for every kinds of GPC.\n";
	int total_luts = 0;
	for (iter = for_area.begin(); iter != for_area.end(); ++iter){		
		if (iter->second > 0){
			int luts = 0;
			OF << "\tNumber of " << iter->first << "\t: " << iter->second << " \t";
			OF << "Each " << iter->first << " used LUTs number is: \t" << Get_Used_LUT(iter->first);			
			luts = (iter->second) * Get_Used_LUT(iter->first);
			OF << "\t Total LUTs is : " << luts << "\n";
			total_luts += luts;
		}
	}
	OF << "\tTotal number of GPCs used is: " << GPC_Sum << "\n";
	OF << "\tSum of used luts is: " << total_luts << "\n";
	//calculate final adder area
	int adder_lut = 0;
	if (K == 2){
		for (int i = 0; i < Max_Col; ++i){
			if (Columns[i] == 2)
				++adder_lut;
		}
	}
	if (K == 3){
		for (int i = 0; i < Max_Col; ++i){
			if (Columns[i] > 1)
				++adder_lut;
		}
		++adder_lut;
	}
	OF << "\tSum of RCA luts is: " << adder_lut << "\n";
}