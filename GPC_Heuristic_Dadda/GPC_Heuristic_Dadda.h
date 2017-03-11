/***************************************************************

�ļ�����GPC_Heuristic_Greedy.h

��  ��: 2010�����ס�Multi-Operand Adder Synthesis on FPGAs
		Using Generalized Parallel Counters������ʽ�㷨ʵ��

��  �ڣ�2016-11-11

****************************************************************/
#ifndef GPC_HEURISTIC_DADDA_H
#define GPC_HEURISTIC_DADDA_H

#include "GPC_Heuristic.h"

std::vector<std::vector<std::map<std::string, int> > > Heuristic_Dadda(std::ofstream &OF,
														std::vector<int> Columns,
														int M,
														int N,
														int K
														);
														
#endif