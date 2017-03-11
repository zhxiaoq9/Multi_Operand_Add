#include "GPC_Heuristic_Greedy.h"


static std::vector<std::vector<std::pair<std::string, std::vector<int> > > > Build_GPC_Library(Target_Mode Mode){
	std::vector<std::vector<std::pair<std::string, std::vector<int> > > > Library;

	std::pair<std::string, std::vector<int> >  GPC_624("GPC_624", { 2, 6, 4 });
	std::pair<std::string, std::vector<int> >  GPC_524("GPC_524", { 2, 5, 4 });
	std::pair<std::string, std::vector<int> >  GPC_424("GPC_424", { 2, 4, 4 });
	std::pair<std::string, std::vector<int> >  GPC_324("GPC_324", { 2, 3, 4 });
	std::pair<std::string, std::vector<int> >  GPC_223("GPC_223", { 2, 2, 3 });
	std::pair<std::string, std::vector<int> >  GPC_123("GPC_123", { 2, 1, 3 });
	std::pair<std::string, std::vector<int> >  GPC_22("GPC_22",   { 2,    2 });

	std::pair<std::string, std::vector<int> >  GPC_534("GPC_534", { 3, 5, 4 });
	std::pair<std::string, std::vector<int> >  GPC_434("GPC_434", { 3, 4, 4 });
	std::pair<std::string, std::vector<int> >  GPC_334("GPC_334", { 3, 3, 4 });
	std::pair<std::string, std::vector<int> >  GPC_233("GPC_233", { 3, 2, 3 });
	std::pair<std::string, std::vector<int> >  GPC_133("GPC_133", { 3, 1, 3 });
	std::pair<std::string, std::vector<int> >  GPC_32("GPC_32",   { 3,    2 });

	std::pair<std::string, std::vector<int> >  GPC_444("GPC_444", { 4, 4, 4 });
	std::pair<std::string, std::vector<int> >  GPC_344("GPC_344", { 4, 3, 4 });
	std::pair<std::string, std::vector<int> >  GPC_244("GPC_244", { 4, 2, 4 });
	std::pair<std::string, std::vector<int> >  GPC_143("GPC_143", { 4, 1, 3 });
	std::pair<std::string, std::vector<int> >  GPC_43("GPC_43",   { 4,    3 });

	std::pair<std::string, std::vector<int> >  GPC_354("GPC_354", { 5, 3, 4 });
	std::pair<std::string, std::vector<int> >  GPC_254("GPC_254", { 5, 2, 4 });
	std::pair<std::string, std::vector<int> >  GPC_153("GPC_153", { 5, 1, 3 });
	std::pair<std::string, std::vector<int> >  GPC_53("GPC_53",   { 5,    3 });

	std::pair<std::string, std::vector<int> >  GPC_6065("GPC_6065", { 6, 0, 6, 5 });
	std::pair<std::string, std::vector<int> >  GPC_264("GPC_264", { 6, 2, 4 });
	std::pair<std::string, std::vector<int> >  GPC_164("GPC_164", { 6, 1, 4 });
	std::pair<std::string, std::vector<int> >  GPC_63("GPC_63",   { 6,    3 });

	std::pair<std::string, std::vector<int> >  GPC_73("GPC_73", { 7, 3 });

	if (Mode == Target_Mode::AD){
		Library.push_back({ GPC_624, GPC_524, GPC_424, GPC_324, GPC_223, GPC_123, GPC_22 });
		Library.push_back({ GPC_534, GPC_434, GPC_334, GPC_233, GPC_32 });
		Library.push_back({ GPC_444, GPC_344, GPC_244, GPC_143, GPC_43 });
		Library.push_back({ GPC_354, GPC_254, GPC_153, GPC_53 });
		Library.push_back({ GPC_264, GPC_164, GPC_63 });
		Library.push_back({ GPC_73 });
	}
	if (Mode == Target_Mode::PD){
		Library.push_back({ GPC_624, GPC_524, GPC_424, GPC_324, GPC_223, GPC_123, GPC_22 });
		Library.push_back({ GPC_534, GPC_233, GPC_133, GPC_32 });
		Library.push_back({ GPC_444, GPC_344, GPC_244, GPC_143, GPC_43 });
		Library.push_back({ GPC_354, GPC_153, GPC_53 });
		Library.push_back({ GPC_164, GPC_63 });
		Library.push_back({ GPC_73 });
	}
	if (Mode == Target_Mode::APD){
		Library.push_back({ GPC_624, GPC_524, GPC_424, GPC_324, GPC_223, GPC_123, GPC_22 });
		Library.push_back({ GPC_534, GPC_434, GPC_334, GPC_233, GPC_32 });
		Library.push_back({ GPC_444, GPC_344, GPC_244, GPC_143, GPC_43 });
		Library.push_back({ GPC_354, GPC_254, GPC_153, GPC_53 });
		Library.push_back({ GPC_264, GPC_164, GPC_63 });
		Library.push_back({ GPC_73 });
	}

	return Library;
}

static void Add_Stage(const std::vector<std::vector<std::pair<std::string, std::vector<int> > > > &Library, 
	std::vector<std::vector<std::map<std::string, int> > > &GPC_Net,
	int Max_Col, int Level	
	){
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

	GPC_Net.push_back(col_vec);
}


static void Map_By_GPC(std::vector<int> &Columns,  
	const std::vector<std::vector<std::pair<std::string, std::vector<int> > > > &Library,
	std::vector<std::vector<std::map<std::string, int> > > &GPC_Net,
	int Max_Col, int Stage_Index){
	int target_limit = 3;
	//-------------------Map by most priority GPC------------------//
	std::vector<int> New_Dots(Max_Col);
	//Get most high priority GPC
	std::string MP_Name = Library[Library.size() - 1][0].first;
	std::vector<int> MP_Vec = Library[Library.size() - 1][0].second;
	int BH = MP_Vec[0];
	for (int i = 0; i < Max_Col; ++i){
		while (Columns[i] >= BH){
			bool is_valid_gpc = true;
			for (int k = 1; k < (int)MP_Vec.size() - 1; ++k){
				int index = i + k;
				if (index < Max_Col){
					if (Columns[index] < MP_Vec[k]){
						is_valid_gpc = false;
						break;
					}
				}
				else{
					is_valid_gpc = false;
					break;
				}
			}

			if (is_valid_gpc){
				++GPC_Net[Stage_Index][i][MP_Name];
				for (int k = 0; k < (int)MP_Vec.size() - 1; ++k)
					Columns[i + k] -= MP_Vec[k];
				for (int k = 0; k < (int)MP_Vec[MP_Vec.size() - 1]; ++k)
				if (i + k < Max_Col)
					++New_Dots[i + k];
			}
		}	
	}
	

	//------------------------Map by other  GPC-----------------------//
	for (int i = 0; i < Max_Col; ++i){
		if (Columns[i] <= target_limit)
			continue;
		//get most high prority GPC that suits with the left dots
		std::vector<std::pair<std::string, std::vector<int> > > lib = Library[Columns[i] - 2];
		std::string SUIT_Name;
		std::vector<int> SUIT_Vec;
		for (int k = 0; k < (int)lib.size(); ++k){
			SUIT_Name = lib[k].first;
			SUIT_Vec = lib[k].second;
			bool is_valid_gpc = true;
			for (int m = 1; m < (int)SUIT_Vec.size() - 1; ++m){
				int index = i + m;
				if (index < Max_Col){
					if (Columns[i + m] < SUIT_Vec[m]){
						is_valid_gpc = false;
						break;
					}
				}
				else{
					is_valid_gpc = false;
					break;
				}
			}
			if (is_valid_gpc){
				++GPC_Net[Stage_Index][i][SUIT_Name];
				//update dot number in column
				for (int n = 0; n < (int)SUIT_Vec.size() - 1; ++n)
					Columns[i + n] -= SUIT_Vec[n];
				for (int n = 0; n < SUIT_Vec[SUIT_Vec.size() - 1]; ++n)
					if (Max_Col > i + n)
						New_Dots[i + n] += 1;
				break;
			}
		}		
	}

	//generate next stage dots
	for (int j = 0; j < Max_Col; ++j){
		Columns[j] += New_Dots[j];
	}

}

static void Map3_To_Map2(std::vector<int> &Columns,
	const std::vector<std::vector<std::pair<std::string, std::vector<int> > > > &Library,
	std::vector<std::vector<std::map<std::string, int> > > &GPC_Net,
	int Max_Col, int Stage_Index){

	int target_limit = 2;
	std::vector<int> New_Dots(Max_Col);
	for (int i = 0; i < Max_Col; ++i){	
		if (Columns[i] < 2)
			continue;
		std::vector<std::pair<std::string, std::vector<int> > > lib = Library[Columns[i]-2];
		std::string SUIT_Name;
		std::vector<int> SUIT_Vec;
		for (int k = 0; k < (int)lib.size(); ++k){
			SUIT_Name = lib[k].first;
			SUIT_Vec = lib[k].second;
			bool is_valid_gpc = true;
			for (int m = 1; m < (int)SUIT_Vec.size() - 1; ++m){
				int index = i + m;
				if (index < Max_Col){
					if (Columns[index] < SUIT_Vec[m]){
						is_valid_gpc = false;
						break;
					}
				}
				else{
					is_valid_gpc = false;
					break;
				}
			}
			if (is_valid_gpc){
				//update GPC number in GPC_Net
				++GPC_Net[Stage_Index][i][SUIT_Name];
				//update dot number in column
				for (int n = 0; n < (int)SUIT_Vec.size() - 1; ++n)
					Columns[i + n] -= SUIT_Vec[n];
				for (int n = 0; n < SUIT_Vec[SUIT_Vec.size() - 1]; ++n)
				if (Max_Col > i + n)
					New_Dots[i + n] += 1;
				break;
			}
		}
	}

	//generate next stage dots
	for (int j = 0; j < Max_Col; ++j){
		Columns[j] += New_Dots[j];
	}
}



std::vector<std::vector<std::map<std::string, int> > > Heuristic_Greedy(std::ofstream &OF,
	std::vector<int> Columns,
	Target_Mode Mode,
	int K
	){

	int Max_Col = Get_Out_Widths(Columns);;
	int Stage_Index = 0;
	bool IsFinish;
	std::vector<std::vector<std::map<std::string, int> > > GPC_Net;
	std::vector<std::vector<std::pair<std::string, std::vector<int> > > > GPC_Library = Build_GPC_Library(Mode);

	Columns.resize(Max_Col);
	while (!(IsFinish = Is_Valid_Result(Columns, 3)))
	{
		Add_Stage(GPC_Library, GPC_Net, Max_Col, Stage_Index);

		Map_By_GPC(Columns, GPC_Library, GPC_Net, Max_Col, Stage_Index);

		Stage_Index++;
	}
	if (K == 2){
		Add_Stage(GPC_Library, GPC_Net, Max_Col, Stage_Index);
		Map3_To_Map2(Columns, GPC_Library, GPC_Net, Max_Col, Stage_Index);
		++Stage_Index;
	}

	Write_Heuristic_Message(OF, Columns, GPC_Net, Max_Col, Stage_Index, K);

	return GPC_Net;
}