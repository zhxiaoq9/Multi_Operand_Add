/***************************************************************

文件名：GPC_Heuristic_Greedy_Dadda.h

功  能: 改进式Dadda树的启发式算法实现

日  期：2016-11-11

****************************************************************/
#ifndef GPC_HEURISTIC_GREDDY_DADDA_H
#define GPC_HEURISTIC_GREDDY_DADDA_H

#include "GPC_Heuristic.h"

std::vector<std::vector<std::map<std::string, int> > > Heuristic_Greedy_Dadda(std::ofstream &OF,
																			std::vector<int> Columns,
																			int M,
																			int N,
																			int K
																			);

#endif