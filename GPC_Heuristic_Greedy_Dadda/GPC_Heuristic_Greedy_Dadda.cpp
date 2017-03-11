#include "GPC_Heuristic_Greedy_Dadda.h"


static int Get_Stage_Target(int Current_Dot, int M, int N, int k){
	/*
	if (k == 2){
	if (Current_Dot == 3)
	return 2;
	}
	//calculate like k == 3 when Current_Dot > 3
	int next_target = 3;
	int target = 3;
	while (next_target < Current_Dot){
	target = next_target;
	next_target = (next_target * M) / N;
	}
	return target;
	*/

	if (Current_Dot == 6)
		return 3;

	if (k == 2){
		if (Current_Dot == 3)
			return 2;
	}
	//calculate like k == 3 when Current_Dot > 3
	int next_target = 6;
	int target = 6;
	while (next_target < Current_Dot){
		target = next_target;
		next_target = (next_target * M) / N;
	}
	return target;
}

static int Get_Stages(const std::vector<int> &Columns, int M, int N, int k){
	/*
	//get maximum height of Columns
	int len = Columns.size();
	int max_height = 0;
	for (int i = 0; i < len; ++i){
	if (Columns[i] > max_height)
	max_height = Columns[i];
	}
	//set initial target as 3
	int target = 3;
	int stage = 0;
	while (target < max_height){
	++stage;
	target = (target * M) / N;
	}
	//if k is 2 then a new stage compress 3->2 needed
	if (k == 2)
	return stage + 1;
	else
	return stage;
	*/

	//get maximum height of Columns
	int len = Columns.size();
	int max_height = 0;
	for (int i = 0; i < len; ++i){
		if (Columns[i] > max_height)
			max_height = Columns[i];
	}
	//set initial target as 3
	int target = 6;
	int stage = 0;
	while (target < max_height){
		++stage;
		target = (target * M) / N;
	}
	//if k is 2 then a new stage compress 3->2 needed
	if (k == 2)
		return stage + 2;
	else
		return stage + 1;



}


/************************************************
Function:
	Generate all the GPCs satisfied M, N and Rank,
	sort by compress rate, return the sorted library
	(except for GPC(1,7;3))after it.

Para:
M		: GPC Maximum input number
N		: GPC Maximum output number
Rank	: GPC input rank limit, it means that GPC
		  input rank can not exceed this value, the
		  default value is 2.
		  for example, if Rank = 2, then the GPC
		  can only be like (3;2) (2,6;4) but not
		  (6,0,6;5)
Ret		: store GPC library sorted by compress rate

Attention: for now,this function only support the case 
		   when Rank = 2
			
************************************************/
static std::vector<std::vector<std::pair<std::string, std::vector<int> > > > Build_GPC_Library(int M, int N, int Rank = 2){
	std::vector<std::vector<std::pair<std::string, std::vector<int> > > > Library;
	if (Rank == 2){
		std::vector<std::pair<std::string, std::vector<int> > > Temp0;
		std::pair<std::string, std::vector<int> >  GPC_624("GPC_624", { 2, 6, 4 });
		std::pair<std::string, std::vector<int> >  GPC_524("GPC_524", { 2, 5, 4 });
		std::pair<std::string, std::vector<int> >  GPC_424("GPC_424", { 2, 4, 4 });
		std::pair<std::string, std::vector<int> >  GPC_324("GPC_324", { 2, 3, 4 });
		std::pair<std::string, std::vector<int> >  GPC_223("GPC_223", { 2, 2, 3 });
		std::pair<std::string, std::vector<int> >  GPC_123("GPC_123", { 2, 1, 3 });
		std::pair<std::string, std::vector<int> >  GPC_22("GPC_22", { 2, 2 });
		
		std::pair<std::string, std::vector<int> >  GPC_534("GPC_534", { 3, 5, 4 });
		std::pair<std::string, std::vector<int> >  GPC_434("GPC_434", { 3, 4, 4 });
		std::pair<std::string, std::vector<int> >  GPC_334("GPC_334", { 3, 3, 4 });
		std::pair<std::string, std::vector<int> >  GPC_233("GPC_233", { 3, 2, 3 });
		//std::pair<std::string, std::vector<int> >  GPC_133("GPC_133", { 3, 1, 3 });
		std::pair<std::string, std::vector<int> >  GPC_32("GPC_32",   { 3, 2 });
		
		std::pair<std::string, std::vector<int> >  GPC_444("GPC_444", { 4, 4, 4 });
		std::pair<std::string, std::vector<int> >  GPC_344("GPC_344", { 4, 3, 4 });
		std::pair<std::string, std::vector<int> >  GPC_244("GPC_244", { 4, 2, 4 });
		std::pair<std::string, std::vector<int> >  GPC_143("GPC_143", { 4, 1, 3 });
		std::pair<std::string, std::vector<int> >  GPC_43 ("GPC_43",  { 4, 3 });
		
		std::pair<std::string, std::vector<int> >  GPC_354("GPC_354", { 5, 3, 4 });
		std::pair<std::string, std::vector<int> >  GPC_254("GPC_254", { 5, 2, 4 });
		std::pair<std::string, std::vector<int> >  GPC_153("GPC_153", { 5, 1, 3 });
		std::pair<std::string, std::vector<int> >  GPC_53("GPC_53",   { 5, 3 });
	
		std::pair<std::string, std::vector<int> >  GPC_6065("GPC_6065", { 6, 0, 6, 5 });
		std::pair<std::string, std::vector<int> >  GPC_264("GPC_264", { 6, 2, 4 });
		//std::pair<std::string, std::vector<int> >  GPC_164("GPC_164", { 1, 6, 4 });
		std::pair<std::string, std::vector<int> >  GPC_63 ("GPC_63",  { 6, 3 });		

		std::pair<std::string, std::vector<int> >  GPC_73("GPC_73", { 7, 3 });
		/*
		//sorted by compress ratio
		Library.push_back({ GPC_624, GPC_524, GPC_424, GPC_223, GPC_324, GPC_123, GPC_22 });
		Library.push_back({ GPC_534, GPC_434, GPC_233, GPC_334, GPC_32 });
		Library.push_back({ GPC_444, GPC_344, GPC_143, GPC_244, GPC_43 });
		Library.push_back({ GPC_354, GPC_153, GPC_254, GPC_53 });
		Library.push_back({ GPC_264, GPC_63 });
		Library.push_back({ GPC_73 });
		*/
		
		//sorted by CD/lut
		Library.push_back({ GPC_624, GPC_524, GPC_424, GPC_223, GPC_324, GPC_123, GPC_22 });
		Library.push_back({ GPC_534, GPC_434, GPC_233, GPC_32 });
		Library.push_back({ GPC_444, GPC_344, GPC_143, GPC_244, GPC_43 });
		Library.push_back({ GPC_153, GPC_354, GPC_254, GPC_53 });
		Library.push_back({ GPC_63 });
		Library.push_back({ GPC_73 });
		
	}

	return Library;
}


static void Build_GPC_Net(std::vector<int> &Columns,
	const std::vector<std::vector<std::pair<std::string, std::vector<int> > > > &Library,
	std::vector<std::vector<std::map<std::string, int> > > &GPC_Net,
	int Max_Col, int Stage, int M, int N, int K){
	// get maximum dot number in all columns
	int Height = 0;
	for (int i = 0; i < Max_Col; ++i){
		if (Columns[i] > Height)
			Height = Columns[i];
	}

	//-------------------process each stage except for final stage------------------//
	int stage_num = 0;
	if (K == 2)
		stage_num = Stage - 2;
	else
		stage_num = Stage - 1;
	for (int i = 0; i < stage_num; ++i){
		//store new dots generated by GPC
		std::vector<int> New_Dot(Max_Col);
		//get target
		Height = Get_Stage_Target(Height, M, N, K);
		for (int j = 0; j < Max_Col; ++j){
			//if total dot number is less than target,
			//then, continue next column
			if (Height >= Columns[j] + New_Dot[j])
				continue;
			///////////////////////////////////////////////GPC map by most priority GPC
			//get most priority GPC
			std::string MP_Name = Library[Library.size() - 1][0].first;
			std::vector<int> MP_Vec = Library[Library.size() - 1][0].second;
			while (Columns[j] >= MP_Vec[0]){
				bool is_valid_gpc = true;
				for (int k = 1; k < (int)MP_Vec.size() - 1; ++k){
					int index = j + k;
					if (index < Max_Col){
						if (Columns[j + k] < MP_Vec[k]){
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
					++GPC_Net[i][j][MP_Name];
					//update dot number in column
					for (int k = 0; k < (int)MP_Vec.size() - 1; ++k)
						Columns[j + k] -= MP_Vec[k];
					for (int k = 0; k < MP_Vec[MP_Vec.size() - 1]; ++k)
						if (Max_Col > j + k)
							New_Dot[j + k] += 1;
				}
			}
			//if the left dots number less than 2, then continue next column process
			if (Columns[j] < 2)
				continue;
			///////////////////////////////////////////////GPC map by other GPC
			//get most high prority GPC that suits with the left dots, process with it
			std::vector<std::pair<std::string, std::vector<int> > > lib = Library[Columns[j] - 2];
			std::string SUIT_Name = lib[0].first;;
			std::vector<int> SUIT_Vec = lib[0].second;
			for (int k = 0; k < 1; ++k){
				bool is_valid_gpc = true;
				for (int m = 1; m < (int)SUIT_Vec.size() - 1; ++m){
					int index = j + m;
					if (index < Max_Col){
						if (Columns[j + m] < SUIT_Vec[m]){
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
					++GPC_Net[i][j][SUIT_Name];
					//update dot number in column
					for (int n = 0; n < (int)SUIT_Vec.size() - 1; ++n)
						Columns[j + n] -= SUIT_Vec[n];
					for (int n = 0; n < SUIT_Vec[SUIT_Vec.size() - 1]; ++n)
						if (Max_Col > j + n)
							New_Dot[j + n] += 1;
					break;
				}
			}
			///////////////////////////To be assure the limit can be satisfied
			if (Height < Columns[j] + New_Dot[j]){
				for (int k = 1; k < (int)lib.size(); ++k){
					SUIT_Name = lib[k].first;
					SUIT_Vec = lib[k].second;
					bool is_valid_gpc = true;
					for (int m = 1; m < (int)SUIT_Vec.size() - 1; ++m){
						int index = j + m;
						if (index < Max_Col){
							if (Columns[j + m] < SUIT_Vec[m]){
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
						++GPC_Net[i][j][SUIT_Name];
						//update dot number in column
						for (int n = 0; n < (int)SUIT_Vec.size() - 1; ++n)
							Columns[j + n] -= SUIT_Vec[n];
						for (int n = 0; n < SUIT_Vec[SUIT_Vec.size() - 1]; ++n)
							if (Max_Col > j + n)
								New_Dot[j + n] += 1;
						break;
					}
				}
			}
		}
		//Generate next stage dots
		for (int j = 0; j < Max_Col; ++j)
			Columns[j] += New_Dot[j];
	}

	//-------------------process each left stage------------------//
	for (int i = stage_num; i < Stage; ++i){
		//store new dots generated by GPC
		std::vector<int> New_Dot(Max_Col);
		//get target
		Height = Get_Stage_Target(Height, M, N, K);
		for (int j = 0; j < Max_Col; ++j){
			//if total dot number is less than target,
			//then, continue next column
			if (Height >= Columns[j] + New_Dot[j])
				continue;
			//a bug happened here
			std::vector<std::pair<std::string, std::vector<int> > > lib = Library[Columns[j] - 2];
			std::string SUIT_Name;
			std::vector<int> SUIT_Vec;
			for (int k = 0; k < (int)lib.size(); ++k){
				SUIT_Name = lib[k].first;
				SUIT_Vec = lib[k].second;
				bool is_valid_gpc = true;
				for (int m = 1; m < (int)SUIT_Vec.size() - 1; ++m){
					int index = j + m;
					if (index < Max_Col){
						if (Columns[j + m] < SUIT_Vec[m]){
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
					++GPC_Net[i][j][SUIT_Name];
					//update dot number in column
					for (int n = 0; n < (int)SUIT_Vec.size() - 1; ++n)
						Columns[j + n] -= SUIT_Vec[n];
					for (int n = 0; n < SUIT_Vec[SUIT_Vec.size() - 1]; ++n)
						if (Max_Col > j + n)
							New_Dot[j + n] += 1;
					break;
				}
			}
		}
		//Generate next stage dots
		for (int j = 0; j < Max_Col; ++j)
			Columns[j] += New_Dot[j];
		
	}
}


/************************************************
Function£º
		Build GPC net, record used GPC kind and 
		number for every stage and column
Para:
	OF		: GPC Net message file name
	Columns	: initial input dot diagram
	M		: GPC Maximum input number
	N		: GPC Maximum output number
	K		: GPC finian limit, usually 2 or three
************************************************/
std::vector<std::vector<std::map<std::string, int> > > Heuristic_Greedy_Dadda(
																			std::ofstream &OF, 
																			std::vector<int> Columns,
																			int M, int N, int K
																			){

	std::vector<std::vector<std::pair<std::string, std::vector<int> > > > GPC_Library = Build_GPC_Library(M, N, 2);
	

	int Max_Col = Get_Out_Widths(Columns);
	int Stages =  Get_Stages(Columns, M, N, K);
	
	std::vector<std::vector<std::map<std::string, int> > > GPC_Net;
	std::vector<std::vector<std::map<std::string, int> > > New_GPC_Net;
	Columns.resize(Max_Col);
	//backup Columns
	std::vector<int> New_Columns(Columns);

	Initial_GPC_Net(GPC_Library, GPC_Net, Max_Col, Stages);	
	
	Build_GPC_Net(Columns, GPC_Library, GPC_Net, Max_Col, Stages, M, N, K);
	bool is_valid = Is_Valid_Result(Columns, K);
	
	Write_Heuristic_Message(OF, Columns, GPC_Net, Max_Col, Stages, K);
	

	return GPC_Net;
}

