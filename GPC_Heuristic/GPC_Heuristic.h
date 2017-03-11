/***************************************************************

文件名：GPC_Heuristic.h

功  能: 启发式算法通用函数及定义

日  期：2016-11-11

****************************************************************/
#ifndef GPC_HEURISTIC_H
#define GPC_HEURISTIC_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <map>



int Get_Out_Widths(const std::vector<int> &columns);
int Get_Used_LUT(const std::string &str);

void Initial_GPC_Net(const std::vector<std::vector<std::pair<std::string, std::vector<int> > > > &Library,
					std::vector<std::vector<std::map<std::string, int> > > &GPC_Net,
					int Max_Col, int Stage);

bool Is_Valid_Result(const std::vector<int> &Columns, int K);

void Write_Heuristic_Message(std::ofstream &OF, const std::vector<int> &Columns, 
							const std::vector<std::vector<std::map<std::string, int> > > &GPC_Net,
							int Max_Col, int Stages, int K);

#endif