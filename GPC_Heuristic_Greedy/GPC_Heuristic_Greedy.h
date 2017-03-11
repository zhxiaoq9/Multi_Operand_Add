/***************************************************************

�ļ�����GPC_Heuristic_Greedy.h

��  ��: 2010�����ס�Improved Synthesis of Compressor Trees on FPGAs
		by a  Hybrid and Systematic Design Approach������ʽ�㷨ʵ��

��  �ڣ�2016-11-11

****************************************************************/
#ifndef GPC_HEURISTIC_GREDDY_H
#define GPC_HEURISTIC_GREDDY_H

#include "GPC_Heuristic.h"

enum Target_Mode{ PD, AD, APD };
std::vector<std::vector<std::map<std::string, int> > > Heuristic_Greedy(std::ofstream &OF,
																		std::vector<int> Columns,
																		Target_Mode Mode,
																		int K);
#endif