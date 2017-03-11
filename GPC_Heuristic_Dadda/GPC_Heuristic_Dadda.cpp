#include "GPC_Heuristic_Dadda.h"

static int Get_Stage_Target(int Current_Dot, int M, int N, int k){
	
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
	
}


static int Get_Stages(const std::vector<int> &Columns, int M, int N, int k){
	
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
}



static std::vector<std::vector<std::pair<std::string, std::vector<int> > > > Build_GPC_Library(int M, int N, int Rank){

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
		std::pair<std::string, std::vector<int> >  GPC_133("GPC_133", { 3, 1, 3 });
		std::pair<std::string, std::vector<int> >  GPC_32("GPC_32", { 3, 2 });	

		std::pair<std::string, std::vector<int> >  GPC_444("GPC_444", { 4, 4, 4 });
		std::pair<std::string, std::vector<int> >  GPC_344("GPC_344", { 4, 3, 4 });
		std::pair<std::string, std::vector<int> >  GPC_244("GPC_244", { 4, 2, 4 });
		std::pair<std::string, std::vector<int> >  GPC_143("GPC_143", { 4, 1, 3 });
		std::pair<std::string, std::vector<int> >  GPC_43("GPC_43", { 4, 3 });		

		std::pair<std::string, std::vector<int> >  GPC_354("GPC_354", { 5, 3, 4 });
		std::pair<std::string, std::vector<int> >  GPC_254("GPC_254", { 5, 2, 4 });
		std::pair<std::string, std::vector<int> >  GPC_153("GPC_153", { 5, 1, 3 });
		std::pair<std::string, std::vector<int> >  GPC_53("GPC_53", { 5, 3 });
		
		std::pair<std::string, std::vector<int> >  GPC_264("GPC_264", { 6, 2, 4 });
		std::pair<std::string, std::vector<int> >  GPC_164("GPC_164", { 1, 6, 4 });
		std::pair<std::string, std::vector<int> >  GPC_63("GPC_63", { 6, 3 });
		
		std::pair<std::string, std::vector<int> >  GPC_73("GPC_73", { 7, 3 });

		//sort by default
		
		Library.push_back({ GPC_624, GPC_524, GPC_424, GPC_324, GPC_223, GPC_123, GPC_22 });
		Library.push_back({ GPC_534, GPC_434, GPC_334, GPC_233, GPC_133, GPC_32 });
		Library.push_back({ GPC_444, GPC_344, GPC_244, GPC_143, GPC_43 });
		Library.push_back({ GPC_354, GPC_254, GPC_153, GPC_53 });
		Library.push_back({ GPC_264, GPC_164, GPC_63 });
		Library.push_back({ GPC_73 });
		
		/*
		//sort by compress ratio
		Library.push_back({ GPC_624, GPC_524, GPC_424, GPC_223, GPC_324, GPC_123, GPC_22 });
		Library.push_back({ GPC_534, GPC_434, GPC_233, GPC_334, GPC_32 });
		Library.push_back({ GPC_444, GPC_344, GPC_143, GPC_244, GPC_43 });
		Library.push_back({ GPC_354, GPC_153, GPC_254, GPC_53 });
		Library.push_back({ GPC_264, GPC_63 });
		Library.push_back({ GPC_73 });
		*/
		
		/*
		Library.push_back({ GPC_223, GPC_123, GPC_22 });
		Library.push_back({ GPC_233, GPC_133, GPC_32 });
		Library.push_back({ GPC_143, GPC_43 });
		Library.push_back({ GPC_153, GPC_53 });
		Library.push_back({ GPC_63 });
		*/
	}
	return Library;

}

static void Build_GPC_Net(std::vector<int> &Columns,
						const std::vector<std::vector<std::pair<std::string, std::vector<int> > > > &Library,
						std::vector<std::vector<std::map<std::string, int> > > &GPC_Net,
						int Max_Col, int Stage, int M, int N, int K){

	//Get maximum height of all Columns
	int Height = 0;
	for (int num : Columns){
		if (num > Height)
			Height = num;
	}
	/***************************
	int stage_num(0);
	if (K == 2)
		stage_num = Stage - 1;
	else
		stage_num = Stage;
	***************************/
	//GPC map by most priority GPC
	//get most priority GPC
	std::string MP_Name = Library[Library.size() - 1][0].first;
	std::vector<int> MP_Vec = Library[Library.size() - 1][0].second;
	int BH = MP_Vec[0];
	for (int i = 0; i < Stage; ++i){
		//get target
		Height = Get_Stage_Target(Height, M, N, K);
		std::vector<int> New_Dots(Max_Col);
		for (int j = 0; j < Max_Col; ++j){
			//if left dots is more than height
			if (Height >= Columns[j] + New_Dots[j])
				continue;
			//start map by GPC
			int exceed_dots = Columns[j] + New_Dots[j] - Height;
			while (exceed_dots > 0){
				//get dots left if the most priority GPC can be used
				//mp_left_dots = Columns[j] + New_Dots[j] - BH + 1 - Height;
				int mp_left_dots = exceed_dots - BH + 1;
				if (mp_left_dots >= 0){
					bool is_valid_gpc = true;
					//map by most priority GPC
					for (int k = 1; k < (int)MP_Vec.size() - 1; ++k){
						int index = j + k;
						if (index < Max_Col){
							if (Columns[i] < MP_Vec[k]){
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
								New_Dots[j + k] += 1;
					}
				}
				else{
					//map by other GPC
					//calculate used GPC most least dots, assume it as X, then
					//Columns[j] + New_Dots[j] - X + 1 = Height;so X = exceed_dots + 1
					int X = exceed_dots + 1;
					//get most high prority GPC that suits with the left dots, process with it
					std::vector<std::pair<std::string, std::vector<int> > > lib = Library[X - 2];
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
									New_Dots[j + n] += 1;
							break;
						}
					}
				}
				//update exceed dots
				exceed_dots = Columns[j] + New_Dots[j] - Height;
			}
		}
		//generate next stage dots
		for (int k = 0; k < Max_Col; ++k)
			Columns[k] += New_Dots[k];
	
	}
	/*************************************************************************
	//----------------------------process for 3->2 ----------------------------//
	//In this step we only us GPC(3,2) and GPC(2,2)
	//get final stage target
	Height = Get_Stage_Target(Height, M, N, K);
	if (K == 4){
		//find GPC(3;2)
		std::pair<std::string, std::vector<int> > GPC_32;
		for (int m = 0; m < (int)Library[1].size(); ++m){
			GPC_32 = Library[1][m];
			if ((GPC_32.second).size() == 2)
				break;
		}
		//find GPC(2;2)
		std::pair<std::string, std::vector<int> > GPC_22;
		for (int m = 0; m <(int)Library[0].size(); ++m){
			GPC_22 = Library[0][m];
			if ((GPC_22.second).size() == 2)
				break;
		}

		std::vector<int> Fin_New_Dot(Max_Col);
		for (int j = 0; j < Max_Col; ++j){
			if (Height >= Columns[j] + Fin_New_Dot[j])
				continue;
			//Calculate GPC most least dots for a suitable GPC, assume as X
			// Columns[j] + Fin_New_Dot[j] - X + 1 = Height
			int X = Columns[j] + Fin_New_Dot[j] - Height + 1;
			if (X == 3){
				//Map with GPC_32
				//update GPC number in GPC_Net
				++GPC_Net[Stage - 1][j][GPC_32.first];
				//update dot number in column
				for (int n = 0; n < (int)(GPC_32.second).size() - 1; ++n)
					Columns[j + n] -= (GPC_32.second)[n];
				for (int n = 0; n < (GPC_32.second)[(GPC_32.second).size() - 1]; ++n)
					Fin_New_Dot[j + n] += 1;
			}
			else if (X == 2){
				//update GPC number in GPC_Net
				++GPC_Net[Stage - 1][j][GPC_22.first];
				//update dot number in column
				for (int n = 0; n < (int)(GPC_22.second).size() - 1; ++n)
					Columns[j + n] -= (GPC_22.second)[n];
				for (int n = 0; n < (GPC_22.second)[(GPC_22.second).size() - 1]; ++n)
					Fin_New_Dot[j + n] += 1;

			}



		}
		//Generate final left dots
		for (int j = 0; j < Max_Col; ++j)
			Columns[j] += Fin_New_Dot[j];
	}
	**********************************************************************/
}

std::vector<std::vector<std::map<std::string, int> > > Heuristic_Dadda(std::ofstream &OF,
														std::vector<int> Columns,
														int M,
														int N,
														int K
														){
	std::vector<std::vector<std::pair<std::string, std::vector<int> > > > GPC_Library = Build_GPC_Library(M, N, 2);

	int Max_Col = Get_Out_Widths(Columns);
	int Stages = Get_Stages(Columns, M, N, K);

	std::vector<std::vector<std::map<std::string, int> > > GPC_Net;
	Initial_GPC_Net(GPC_Library, GPC_Net, Max_Col, Stages);

	Columns.resize(Max_Col);
	Build_GPC_Net(Columns, GPC_Library, GPC_Net, Max_Col, Stages, M, N, K);

	Write_Heuristic_Message(OF, Columns, GPC_Net, Max_Col, Stages, K);

	return GPC_Net;
}
