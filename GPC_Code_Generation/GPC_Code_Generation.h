/***************************************************************

文件名：GPC_Code_Generation.h

功  能: 代码生成

日  期：2016-11-11

****************************************************************/
#ifndef GPC_CODE_GENERATION_H
#define GPC_CODE_GENERATION_H

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<map>
#include<list>
#include<deque>
#include<assert.h>
#include <algorithm>

#define GPC_TB_GEN
#define GPC_REG_MODE
#define GPC_PIPLINE

enum GPC_Library_Mode{ XILINX_CARRY_CHAIN, GENERAL_LUT, MIXED_CARRY_LUT };

void GPC_Library_Code_Generation(std::ostream &OF, GPC_Library_Mode Mode);

void Print_GPC6065(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC20455(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC14155(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC14065(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC13255(std::ostream &OF, GPC_Library_Mode Mode);

void Print_GPC73(std::ostream &OF, GPC_Library_Mode Mode);

void Print_GPC264(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC164(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC63(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC354(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC254(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC153(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC53(std::ostream &OF, GPC_Library_Mode Mode);

void Print_GPC444(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC344(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC244(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC143(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC43(std::ostream &OF, GPC_Library_Mode Mode);

void Print_GPC534(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC434(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC334(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC233(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC133(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC32(std::ostream &OF, GPC_Library_Mode Mode);

void Print_GPC624(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC524(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC424(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC324(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC223(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC123(std::ostream &OF, GPC_Library_Mode Mode);
void Print_GPC22(std::ostream &OF, GPC_Library_Mode Mode);

void GPC_Heuristic_Code_Generation(std::ofstream &OF, std::vector<int> Columns,
	std::vector<std::vector<std::map<std::string, int> > > GPC_Net,
	int K, std::string Module_Name);

void GPC_Testbench_Gen(std::ofstream &OF, std::vector<int> Columns,
	const std::vector<std::vector<std::map<std::string, int> > >  &GPC_Net,
	int K, std::string Testbench_Name);


#endif