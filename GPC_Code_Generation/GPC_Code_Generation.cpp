#include"GPC_Code_Generation.h"


void Print_GPC6065(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_6065(\n";
	OF << "input [5:0] col2,\n";
	OF << "input [5:0] col0,\n";
	OF << "output [4:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[3] + col0[1] + col0[2];\n";
		OF << "wire [1:0] FA1 = FA0[0] + col0[5] + col0[4];\n";
		OF << "wire Xor0 = FA1[0] ^ col0[0];\n";
		OF << "\n";
		OF << "wire Xor1 = FA1[1] ^ FA0[1];\n";
		OF << "\n";
		OF << "wire [1:0] FA2 = col2[0] + col2[1] + col2[2];\n";
		OF << "wire [1:0] FA3 = FA2[0] + col2[3] + col2[4];\n";
		OF << "wire Xor2 = FA3[0] ^ col2[5];\n";
		OF << "\n";
		OF << "wire Xor3 = FA3[1] ^ FA2[1];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {FA3[1], col2[5], FA1[1], col0[0]};\n";
		OF << "wire [3:0] S_test = {Xor3, Xor2, Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = 1'b0;\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[3], temp_sum};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC20455(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_20455(\n";
	OF << "input  [1:0] col3,\n";
	OF << "input  [3:0] col1,\n";
	OF << "input  [4:0] col0,\n";
	OF << "output [4:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [3:0] cc_co;\n";
		OF << "wire [3:0] cc_o;\n";
		OF << "wire [3:0] cc_di;\n";
		OF << "wire [3:0] cc_s;\n";
		OF << "wire       s3;\n";
		OF << "wire       c1;\n";
		OF << "\n";
		OF << "LUT6_2 #(64'h69966996AAAAAAAA) U0(\n";
		OF << ".I0(col0[0]),.I1(col0[1]),.I2(col0[2]),.I3(col0[3]),\n";
		OF << ".I4(1'b0),.I5(1'b1),.O5(cc_di[0]),.O6(cc_s[0]));\n";
		OF << "\n";
		OF << "LUT6_2 #(64'h99969666CCC0C000)  U1(\n";
		OF << ".I0(s3),.I1(col1[0]),.I2(col0[1]),.I3(col0[2]),\n";
		OF << ".I4(col0[3]),.I5(1'b1),.O5(c1),.O6(cc_s[1]));\n";
		OF << "\n";
		OF << "assign cc_di[1] = s3;\n";
		OF << "\n";
		OF << "LUT6_2 #(64'h566A566AC33CC33C)  U2(\n";
		OF << ".I0(c1),.I1(col1[1]),.I2(col1[2]),.I3(col1[3]),\n";
		OF << ".I4(1'b0),.I5(1'b1),.O5(s3),.O6(cc_s[2]));\n";
		OF << "\n";
		OF << "assign cc_di[2] = c1;\n";
		OF << "\n";
		OF << "LUT6_2 #(64'h66666666AAAAAAAA)  U3(\n";
		OF << ".I0(col3[0]),.I1(col3[1]),.I2(1'b0),.I3(1'b0),\n";
		OF << ".I4(1'b0),.I5(1'b1),.O5(cc_di[3]),.O6(cc_s[3]));\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(cc_di),\n";
		OF << ".S(cc_s),\n";
		OF << ".O(cc_o),\n";
		OF << ".CO(cc_co),\n";
		OF << ".CYINIT(col0[4]),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign  z = {cc_co[3],cc_o};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC14155(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_14155( \n";
	OF << "input        col3,\n";
	OF << "input  [3:0] col2,\n";
	OF << "input        col1,\n";
	OF << "input  [4:0] col0,\n";
	OF << "output [4:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[3] + col0[2] + col0[1];\n";
		OF << "wire Xor0 = col0[4] ^ FA0[0];\n";
		OF << "wire Xor1 = col1 ^ FA0[1];\n";
		OF << "wire [1:0] FA1 = col2[0] + col2[1] + col2[2];\n";
		OF << "wire Xor2 = col2[3] ^ FA1[0];\n";
		OF << "wire Xor3 = col3 ^ FA1[1];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {col3, col2[3], col1, col0[4]};\n";
		OF << "wire [3:0] S_test = {Xor3, Xor2, Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = col0[0];\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign  z = {temp_carry[3],temp_sum};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC14065(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_14065( \n";
	OF << "input        col3,\n";
	OF << "input  [3:0] col2,\n";
	OF << "input  [5:0] col0,\n";
	OF << "output [4:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[3] + col0[2] + col0[1];\n";
		OF << "wire [1:0] FA1 = FA0[0] + col0[4] + col0[5];\n";
		OF << "wire Xor0 = FA1[0] ^ col0[0];\n";
		OF << "wire Xor1 = FA1[1] ^ FA0[1];\n";
		OF << "wire [1:0] FA2 = col2[0] + col2[1] + col2[2];\n";
		OF << "wire Xor2 = col2[3] ^ FA2[0];\n";
		OF << "wire Xor3 = col3 ^ FA2[1];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {col3, col2[3], FA1[1], col0[0]};\n";
		OF << "wire [3:0] S_test = {Xor3, Xor2, Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = 1'b0;\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign  z = {temp_carry[3],temp_sum};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC13255(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_13255( \n";
	OF << "input        col3,\n";
	OF << "input  [2:0] col2,\n";
	OF << "input  [1:0] col1,\n";
	OF << "input  [4:0] col0,\n";
	OF << "output [4:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[3] + col0[2] + col0[1];\n";
		OF << "wire Xor0 = col0[4] ^ FA0[0];\n";
		OF << "wire [1:0] HA0 = col1[0] + col1[1];\n";
		OF << "wire Xor1 = HA0[0] ^ FA0[1];\n";
		OF << "wire [1:0] FA1 = col2[0] + col2[1] + col2[2];\n";
		OF << "wire Xor2 = HA0[1] ^ FA1[0];\n";
		OF << "wire Xor3 = col3 ^ FA1[1];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {col3, FA1[0], FA0[1], col0[4]};\n";
		OF << "wire [3:0] S_test = {Xor3, Xor2, Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = col0[0];\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign  z = {temp_carry[3],temp_sum};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC73(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_73 (\n";
	OF << "input[6:0]   col0,\n";
	OF << "output[2:0]  z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[1] + col0[2] + col0[3];\n";
		OF << "wire [1:0] FA1 = col0[4] + col0[5] + FA0[0];\n";
		OF << "wire Xor1 = FA1[0] ^ col0[6];\n";
		OF << "wire Xor2 = FA1[1] ^ FA0[1];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {1'd0, FA0[1], col0[6], col0[0]};\n";
		OF << "wire [3:0] S_test = {1'd0, Xor2, Xor1, 1'b0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = 1'b0;\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[2],temp_sum[2:1]};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC264(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_264 (\n";
	OF << "input  [1:0] col1,\n";
	OF << "input  [5:0] col0,\n";
	OF << "output [3:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[2] + col0[3] + col0[4];\n";
		OF << "wire [1:0] HA0 = FA0[0] + col0[5];\n";
		OF << "wire Xor0 = HA0[0] ^ col0[1];\n";
		OF << "\n";
		OF << "wire [1:0] FA1 = FA0[1] + HA0[1] + col1[0]; \n";
		OF << "wire Xor1 = FA1[0] ^ col1[1];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {1'd0, 1'd0, col1[1], col0[1]};\n";
		OF << "wire [3:0] S_test = {1'd0, FA1[1], Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = col0[0];\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[2], temp_sum[2:0]};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC164(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_164 (\n";
	OF << "input       col1,\n";
	OF << "input [5:0] col0,\n";
	OF << "output[3:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[2] + col0[3] + col0[4];\n";
		OF << "wire [1:0] HA0 = FA0[0] + col0[5];\n";
		OF << "wire Xor0 = HA0[0] ^ col0[1];\n";
		OF << "\n";
		OF << "wire [1:0] HA1 = FA0[1] + HA0[1]; \n";
		OF << "wire Xor1 = HA1[0] ^ col1;\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {1'd0, 1'd0, col1, col0[1]};\n";
		OF << "wire [3:0] S_test = {1'd0, HA1[1], Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = col0[0];\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[2], temp_sum[2:0]};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC63(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_63(\n";
	OF << "input  [5:0]  col0,\n";
	OF << "output [2:0]  z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[1] + col0[2] + col0[3];\n";
		OF << "wire [1:0] FA1 = col0[4] + col0[5] + FA0[0];\n";
		OF << "wire Xor0 = FA1[0] ^ col0[0];\n";
		OF << "wire Xor1 = FA1[1] ^ FA0[1];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {2'd0, FA0[1], col0[0]};\n";
		OF << "wire [3:0] S_test = {2'd0, Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = 1'b0;\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[1],temp_sum[1:0]};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC354(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_354(\n";
	OF << "input  [2:0]  col1,\n";
	OF << "input  [4:0]  col0,\n";
	OF << " output[3:0]  z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[3] + col0[1] + col0[2];\n";
		OF << "wire Xor0 = FA0[0] ^ col0[4];\n";
		OF << "wire [1:0] FA1 = col1[0] + col1[1] + FA0[1];\n";
		OF << "wire Xor1 = FA1[0] ^ col1[2];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {2'd0, col1[2], col0[4]};\n";
		OF << "wire [3:0] S_test = {1'd0, FA1[1], Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = col0[0];\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[2], temp_sum[2:0]};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC254(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\n\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";

		OF << "\n";
		OF << "\n\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC153(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_153 (\n";
	OF << "input        col1,\n";
	OF << "input  [4:0] col0,\n";
	OF << "output [2:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[2] + col0[3] + col0[4];\n";
		OF << "wire Xor0 = FA0[0] ^ col0[1];\n";
		OF << "wire Xor1 = FA0[1] ^ col1;\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {2'd0, col1, col0[1]};\n";
		OF << "wire [3:0] S_test = {2'd0, Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = col0[0];\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[1], temp_sum[1:0]};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC53(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_53(\n";
	OF << "input  [4:0]   col0,\n";
	OF << "output [2:0]   z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[1] + col0[2] + col0[3];\n";
		OF << "wire [1:0] HA0 = col0[0] + FA0[0];\n";
		OF << "wire Xor0 = HA0[0] ^ col0[4];\n";
		OF << "wire Xor1 = HA0[1] ^ FA0[1];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {2'd0, FA0[1], col0[4]};\n";
		OF << "wire [3:0] S_test = {2'd0, Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = 1'b0;\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[1],temp_sum[1:0]};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC444(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_444 (\n";
	OF << "input [3:0] col1,\n";
	OF << "input [3:0] col0,\n";
	OF << "output [3:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] HA0 = col0[2] + col0[3];\n";
		OF << "wire Xor0 = HA0[0] ^ col0[1];\n";
		OF << "wire [1:0] FA0 = col1[0] + col1[1] + HA0[1];\n";
		OF << "wire [1:0] HA1 = col1[2] + FA0[0];\n";
		OF << "wire Xor1 = HA1[0] ^ col1[3];\n";
		OF << "wire Xor2 = HA1[1] ^ FA0[1];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {1'b0, HA1[1], col1[3], col0[1]};\n";
		OF << "wire [3:0] S_test = {1'b0, Xor2, Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = col0[0]; \n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[2], temp_sum[2:0]};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC344(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\n\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";

		OF << "\n";
		OF << "\n\n";
	}
	OF << "\nendmodule\n";
}
void Print_GPC244(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\n\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";

		OF << "\n";
		OF << "\n\n";
	}
	OF << "\nendmodule\n";
}
void Print_GPC143(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_143 (\n";
	OF << "input        col1,\n";
	OF << "input  [3:0] col0,\n";
	OF << "output [2:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[1] + col0[2] + col0[3];\n";
		OF << "wire Xor0 = FA0[0] ^ col0[0];\n";
		OF << "wire Xor1 = FA0[1] ^ col1;\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {2'd0, col1, col0[0]};\n";
		OF << "wire [3:0] S_test = {2'd0, Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = 1'b0;\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[1], temp_sum[1:0]};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC43(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_43(\n";
	OF << "input  [3:0]  col0,\n";
	OF << "output [2:0]  z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[2] + col0[1] + col0[0];\n";
		OF << "wire Xor0 = FA0[0] ^ col0[3];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {3'd0, col0[3]};\n";
		OF << "wire [3:0] S_test = {2'd0, FA0[1], Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = 1'b0;\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[1],temp_sum[1:0]};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC534(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_534(\n";
	OF << "input  [4:0] col1,\n";
	OF << "input  [2:0] col0,\n";
	OF << "output [3:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire Xor0 = col0[2] ^ col0[1];\n";
		OF << "wire [1:0] FA0 = col1[2] + col1[3] + col1[4];\n";
		OF << "wire [1:0] HA0 = col1[1] + FA0[0];\n";
		OF << "wire Xor1 = HA0[0] ^ col1[0];\n";
		OF << "wire Xor2= FA0[1] ^ HA0[1];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {1'd0, FA0[1], col1[0], col0[1]};\n";
		OF << "wire [3:0] S_test = {1'd0, Xor2, Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = col0[0];\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[2], temp_sum[2:0]};\n";
	}
	OF << "\nendmodule\n";
}


void Print_GPC434(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\n\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";

		OF << "\n";
		OF << "\n\n";
	}
	OF << "\nendmodule\n";
}
void Print_GPC334(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\n\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";

		OF << "\n";
		OF << "\n\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC233(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_233(\n";
	OF << "input  [1:0] col1,\n";
	OF << "input  [2:0] col0,\n";
	OF << "output [2:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire Xor0 = col0[1] ^ col0[2];\n";
		OF << "wire Xor1 = col1[1] ^ col1[0]; \n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {2'd0, col1[1], col0[1]};\n";
		OF << "wire [3:0] S_test = {2'd0, Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = col0[0];\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[1], temp_sum[1:0]};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC133(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_133(\n";
	OF << "input        col1,\n";
	OF << "input  [2:0] col0,\n";
	OF << "output [2:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] HA0 = col0[1] + col0[2];\n";
		OF << "wire Xor0 = HA0[0] ^ col0[0];\n";
		OF << "wire Xor1 = HA0[1] ^ col1;\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {2'd0, col1, col0[0]};\n";
		OF << "wire [3:0] S_test = {2'd0, Xor1, Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = 1'b0;\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[1], temp_sum[1:0]};\n";
	}
	OF << "\nendmodule\n";
}

//this GPC32 is a test version
void Print_GPC32(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_32(\n";
	OF << "input  [2:0]  col0,\n";
	OF << "output [1:0]  z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col0[1] + col0[0];\n";
		OF << "wire Xor0 = FA0[0] ^ col0[2];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {3'd0, col0[2]};\n";
		OF << "wire [3:0] S_test = {2'd0, FA0[1], Xor0};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = 1'b0;\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = temp_sum[1:0];\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC624(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "module GPC_624(\n";
	OF << "input [5:0] col1,\n";
	OF << "input [1:0] col0,\n";
	OF << "output [3:0] z\n";
	OF << ");\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\nwire [1:0] FA0 = col1[0] + col1[1] + col1[2];\n";
		OF << "wire [1:0] FA1 = FA0[0] + col1[3] + col1[4];\n";
		OF << "wire Xor1 = FA1[0] ^ col1[5];\n";
		OF << "wire Xor2 = FA0[1] ^ FA1[1];\n";
		OF << "\n";
		OF << "wire [3:0] DI_test = {1'b0, FA1[1], col1[5], col0[1]};\n";
		OF << "wire [3:0] S_test = {1'b0, Xor2, Xor1, col0[1]};\n";
		OF << "wire [3:0] temp_sum;\n";
		OF << "wire [3:0] temp_carry;\n";
		OF << "wire       temp_ci = col0[0];\n";
		OF << "\n";
		OF << "CARRY4 carry1(\n";
		OF << ".DI(DI_test),\n";
		OF << ".S(S_test),\n";
		OF << ".O(temp_sum),\n";
		OF << ".CO(temp_carry),\n";
		OF << ".CYINIT(temp_ci),\n";
		OF << ".CI(1'b0)\n";
		OF << ");\n";
		OF << "\nassign z = {temp_carry[2], temp_sum[2:0]};\n";
	}
	OF << "\nendmodule\n";
}

void Print_GPC524(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\n\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";

		OF << "\n";
		OF << "\n\n";
	}
	OF << "\nendmodule\n";
}
void Print_GPC424(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\n\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";

		OF << "\n";
		OF << "\n\n";
	}
	OF << "\nendmodule\n";
}
void Print_GPC324(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\n\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";

		OF << "\n";
		OF << "\n\n";
	}
	OF << "\nendmodule\n";
}
void Print_GPC223(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\n\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";

		OF << "\n";
		OF << "\n\n";
	}
	OF << "\nendmodule\n";
}
void Print_GPC123(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\n\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";

		OF << "\n";
		OF << "\n\n";
	}
	OF << "\nendmodule\n";
}
void Print_GPC22(std::ostream &OF, GPC_Library_Mode Mode){
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	OF << "\n";
	if (Mode == GPC_Library_Mode::XILINX_CARRY_CHAIN){
		OF << "\n\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";
		OF << "\n";

		OF << "\n";
		OF << "\n\n";
	}
	OF << "\nendmodule\n";
}

void GPC_Library_Code_Generation(std::ostream &OF, GPC_Library_Mode Mode){
	Print_GPC6065(OF, Mode);
	Print_GPC20455(OF, Mode);
	Print_GPC14155(OF, Mode);
	Print_GPC14065(OF, Mode);
	Print_GPC13255(OF, Mode);
	
	Print_GPC73(OF, Mode);

	Print_GPC264(OF, Mode);
	Print_GPC164(OF, Mode);
	Print_GPC63(OF, Mode)
		;
	Print_GPC354(OF, Mode);
	//Print_GPC254(OF, Mode);
	Print_GPC153(OF, Mode);
	Print_GPC53(OF, Mode);

	Print_GPC444(OF, Mode);
	//Print_GPC344(OF, Mode);
	//Print_GPC244(OF, Mode);
	Print_GPC143(OF, Mode);
	Print_GPC43(OF, Mode);

	Print_GPC534(OF, Mode);
	//Print_GPC434(OF, Mode);;
	//Print_GPC334(OF, Mode);
	Print_GPC233(OF, Mode);
	Print_GPC133(OF, Mode);
	Print_GPC32(OF, Mode);

	Print_GPC624(OF, Mode);
	//Print_GPC524(OF, Mode);
	//Print_GPC424(OF, Mode);
	//Print_GPC324(OF, Mode);
	//Print_GPC223(OF, Mode);
	//Print_GPC123(OF, Mode);
	//Print_GPC22(OF, Mode);
}


static inline std::string int2str(int num){
	std::stringstream ss;
	ss << num;
	return ss.str();
}

static inline int str2int(std::string str){
	int num;
	std::stringstream ss(str);
	ss >> num;
	return num;
}

static std::map<std::string, int> Get_Library(const std::vector<std::vector<std::map<std::string, int> > > &GPC_Net){

	assert(GPC_Net.size() > 0 && "GPC_Net is empty!");
	assert(GPC_Net[0].size() > 0 && "GPC_Net is empty!");

	return  GPC_Net[0][0];
}

static std::map<int, std::deque<std::string> > Init_Wire(int Max_Col){
	std::map<int, std::deque<std::string> > Wire;
	std::deque<std::string> tmp;
	for (int i = 0; i < Max_Col; ++i){
		Wire[i] = tmp;
	}
	return Wire;
}

/************************************************
Function:
Get wire name according to it's stage, columns and
how many this kind of GPC used in this stage and column.

Para:
GPC_Name	: GPC's name
Stage		: GPC used stages
Col			: GPC used columns
Index		: GPC's index in all this kinds of gpc
			  used in this stage and column
Ret			: GPC instance name
************************************************/
static std::string Get_Wire_Name(std::string GPC_Name, int Stage, int Col, int Index){
	
	GPC_Name += "_s";
	GPC_Name += int2str(Stage);
	GPC_Name += "_c";
	GPC_Name += int2str(Col);
	GPC_Name += "_";
	GPC_Name += int2str(Index);
	GPC_Name += "_o";
	return GPC_Name;
}

/************************************************
Function:
Get GPC instance column index according to instance
name.
GPC name should be like col0, col1, GPC_73_s1_c3_0_o,
GPC_624_s4_c13_2_o.
		: 
************************************************/
static int Get_Col_Index(std::string GPC_Name){
	int pos = GPC_Name.find('_');
	std::string str;
	if (pos < 0){
		//GPC name is like "col1"
		str = GPC_Name.substr(3, GPC_Name.size());		
	}
	else{
		//GPC name is like "GPC_624_s4_c13_2_o"
		pos = GPC_Name.find('c', 0);
		str = GPC_Name.substr(pos, GPC_Name.size());
		pos = str.find('_', 0);
		str = str.substr(1, pos - 1);
	}
	return str2int(str);
}

/************************************************
Function:
Split GPC instance name into pieces according to 
Para "Width". Store every wire name to Para "Wire"
according to  wire name.
Wire name should be like col0, col1, GPC_73_s1_c3_0_o,
GPC_624_s4_c13_2_o.

Para:
Wire		: Wire name should be stored in this "Wire"
W_Name		: GPC instance name
Width		: GPC output width
************************************************/
static void Store_Wire(std::map<int, std::deque<std::string> > &Wire, std::string W_Name, int Width){
	int base_col = Get_Col_Index(W_Name);
	int Max_Col = Wire.size();
	int index = 0;
	int pos = W_Name.find('_', 0);
	for (int i = 0; i < Width; ++i){
		std::string wire_name(W_Name);
		wire_name += "[";
		wire_name += int2str(i);
		wire_name += "]";
		if (pos < 0)
			index = base_col;
		else
			index = base_col + i;
		if (index < Max_Col)
			Wire[index].push_back(wire_name);			
	}
}

/************************************************
Function:
	Generate Module input and output declaration.

Para:
O_Width		: Module output width
Module_Name	: Top module name
Columns		: Initial dot input matrix

************************************************/
static void GPC_Declare_Top_Module(std::ofstream &OF, const std::vector<int> &Columns, int O_Width, std::string Module_Name){

	OF << "module " << Module_Name << "(\n";

#ifdef GPC_REG_MODE
	OF << "input i_clk,\n";
#endif


	//generate input declaration
	for (int i = 0; i < ((int)Columns.size());++i){
		OF << "input [" << (Columns[i] - 1);
		OF << ":0] " << "I_col" << i << ",\n";
	}
	//generate output declaration
	OF << "output ";
#ifdef GPC_REG_MODE
	OF << "reg ";
#endif
	OF << "[" << (O_Width - 1) << ":0] O_out\n";
	OF << ");\n";

	OF << "\n";
}

static void GPC_Declare_Init_Wire(std::ofstream &OF, const std::vector<int> &Columns,
	const std::vector<std::vector<std::map<std::string, int> > >  &GPC_Net,
	std::map<int, std::deque<std::string> > &Wire){
	assert(GPC_Net.size() > 0 && "GPC_Net is empty!");

	int Init_Col = Columns.size();
	int Max_Col = GPC_Net[0].size();
	//===============Declare initial input =================//
#ifdef GPC_REG_MODE
	//==========print and store reg wire============//
	for (int i = 0; i < Init_Col; ++i){
		std::string wire_name = "col";
		wire_name += int2str(i);
		Store_Wire(Wire, wire_name, Columns[i]);
		OF << "reg [" << (Columns[i] - 1) << ":0] " << wire_name << ";\n";
	}
	OF << "wire [" << (Max_Col - 1) << ":0] out;\n\n";
	//=============print always block===============//
	OF << "always @(posedge i_clk)\n";
	OF << "\tbegin\n";
	for (int i = 0; i < Init_Col; ++i){
		std::string wire_name = "col";
		wire_name += int2str(i);
		OF << "\t" <<wire_name << " <= I_col" << i << ";\n";
	}
	OF << "\tend\n";

	OF << "always @(posedge i_clk)\n";
	OF << "\tbegin\n";
	OF << "\tO_out <= out;\n";
	OF << "\tend\n";
	OF << "\n";
#else
	//==========print initial input wire============//
	for (int i = 0; i < Init_Col; ++i){
		std::string wire_name = "col";
		wire_name += int2str(i);
		Store_Wire(Wire, wire_name, Columns[i]);
		OF << "wire [" << (Columns[i] - 1) << ":0] " << wire_name;
		OF << " = I_col" << i << ";\n";
	}
#endif

}

static void GPC_Declare_Stage_Wire(std::ofstream &OF,
	const std::vector<std::vector<std::map<std::string, int> > >  &GPC_Net,
	std::map<int, std::deque<std::string> > &Wire, int Stage){
	int Max_Col = GPC_Net[0].size();
	//===============Declare every stage output =================//
	std::map<std::string, int>::const_iterator iter;
	OF << "\n";
	for (int j = 0; j < Max_Col; ++j){
		for (iter = GPC_Net[Stage][j].begin(); iter != GPC_Net[Stage][j].end(); ++iter){
			std::string module_name = iter->first;
			int out_width = module_name[module_name.size() - 1] - '0';
			for (int k = 0; k < iter->second; ++k){				
				std::string wire_name = Get_Wire_Name(module_name, Stage, j, k);
				Store_Wire(Wire, wire_name, out_width);
				OF << "wire [" << (out_width - 1) << ":0] " << wire_name << ";\n";
			}
		}
	}

}

/************************************************
Function:
Get GPC input range number.
For example:
GPC_233, Index = 1, return 2
GPC_73, Index = 0, return 7
GPC_6065, Index =0, return 6,
		  Index = 1, return 0,
		  Index = 2, return 6
************************************************/
static inline int Get_GPC_Input_Num(std::string GPC_Name, int Index){
	std::string str = GPC_Name.substr(4, GPC_Name.size() - 5);
	return str[str.size() - 1 - Index] - '0';
}
/************************************************
Function:
Get GPC maximum input weight.
For example:
GPC_233 return 1
GPC_73 return 0
GPC_6065 return 2
************************************************/
static inline int Get_GPC_Maximum_Rank(std::string GPC_Name){
	 std::string str = GPC_Name.substr(4, GPC_Name.size() - 5);
	 return str.size() - 1;
}

/************************************************
Function:
Generate wire connection for a certain gpc.

Para:
Base_Col  : Used GPC's column
Input_Rank: Input weight for GPC
Input_Num : Input number for GPC input rank
************************************************/
static void GPC_Connection(std::ostream &OF, std::map<int, std::deque<std::string> > &Wire,
	int Base_Col, int Input_Rank, int Input_Num){
	int col_index = Base_Col + Input_Rank;
	for (int i = 0; i < Input_Num; ++i){
		if (!Wire[col_index].empty()){
			OF << Wire[col_index].front();
			Wire[col_index].pop_front();
		}
		else{
			OF << "1'b0";
		}

		if (i != Input_Num - 1){
			OF << ",";
		}
	}
}

/************************************************
Function:
Instance every GPC for a certain Stage.

Para:
Stage  : Stage number to be instanced.
************************************************/
static void GPC_Module_Install(std::ofstream &OF,
	const std::vector<std::vector<std::map<std::string, int> > >  &GPC_Net,
	std::map<int, std::deque<std::string> > &Wire, int Stage){
	
	int Max_Col = GPC_Net[0].size();
	std::map<std::string, int>::const_iterator iter;
	OF << "\n";
	for (int j = 0; j < Max_Col; ++j){
		for (iter = GPC_Net[Stage][j].begin(); iter != GPC_Net[Stage][j].end(); ++iter){
			std::string module_name = iter->first;
			int out_width = module_name[module_name.size() - 1] - '0';
			int range = Get_GPC_Maximum_Rank(module_name);
			//===============For every GPC of  GPC "module_name"=================//
			for (int k = 0; k < iter->second; ++k){			
				std::string wire_name = Get_Wire_Name(module_name, Stage, j, k);
				OF << module_name << "  " << wire_name.substr(0,wire_name.size()-2) << "(\n";
				//===================GPC wire connection========================//
				//print every GPC's input
				for (int m = 0; m <= range; ++m){
					int input_num = Get_GPC_Input_Num(module_name, m);
					if (input_num > 0){
						OF << ".col" << m << "({";
						GPC_Connection(OF, Wire, j, m, input_num);
						OF << "}),\n";
					}
				}
				//print a GPC's output
				OF << ".z(" << wire_name << ")\n";
				OF << ");\n";
			}
		}
	}


}

/************************************************
Function:
Print final adder for compress tree
************************************************/
static void GPC_Final_Adder(std::ofstream &OF, 
	std::map<int, std::deque<std::string> > &Wire, 
	int K){
	int Max_Col = Wire.size();
	//Print operand
	for (int m = 0; m < K; ++m){
		OF << "\n";
		OF << "wire [" << Max_Col - 1 << ":0] ";
		OF << "op" << m << " = {";
		for (int i = Max_Col - 1; i >= 0; --i){
			if (!Wire[i].empty()){
				OF << Wire[i].front();
				Wire[i].pop_front();
			}
			else{
				OF << "1'b0";
			}

			if (i != 0){
				OF << ',';
			}
		}
		OF << "};";
	}

	//add operand
	OF << "\n\nassign ";
#ifdef GPC_REG_MODE
		OF << "out";
#else
		OF << "O_out";
#endif
		OF << " = ";
		for (int i = 0; i < K; ++i){
			OF << "op" << i;
			if (i != K - 1){
				OF << " + ";
			}
		}
		OF << ";\n";

		OF << "\nendmodule\n";

}


void GPC_Testbench_Gen(std::ofstream &OF, std::vector<int> Columns,
	const std::vector<std::vector<std::map<std::string, int> > >  &GPC_Net,
	int K, std::string Testbench_Name){
	
	int Max_Col = GPC_Net[0].size();
	int Init_Col = Columns.size();
	OF << "`timescale 1ns/1ps\n\n";
	OF << "module " << Testbench_Name << "_t;\n\n";
	
	for (int i = 0; i < Init_Col; i++)
		OF << "reg [" << (Columns[i] - 1) << ":0] " << "I_col" << i << ";\n";

	OF << "wire [" << (Max_Col - 1) << ":0] " << "O_out;\n\n";
#ifdef GPC_REG_MODE
	OF << "reg\ti_clk;\n\n";
#endif
	//==================begin initial block==================//
	OF << "initial\n";
	OF << "begin\n";
	for (int i = 0; i < Init_Col; i++){
		OF << "I_col" << i << " = 1'b0;\n";
	}
	OF << "end\n\n";

	//==================begin always block==================//
	for (int i = 0; i < Init_Col; i++){
		OF << "always #20 ";
		OF << "I_col" << i << " = $random;\n";
	}
	OF << "\n";

#ifdef GPC_REG_MODE
	OF << "always #5 i_clk = ~i_clk;\n";
#endif
	//==================module installation==================//
	OF << Testbench_Name << " " << Testbench_Name << "(\n";
#ifdef GPC_REG_MODE
	OF << "\t\t.i_clk(i_clk),\n";
#endif
	for (int i = 0; i < Init_Col; ++i){
		OF << "\t\t.I_col" << i << "(";
		OF << "I_col" << i << "),\n";
	}
	OF << "\t\t.O_out(O_out)\n";

	OF << "\t\t);\n\n";

	//==================begin to calculate true result==================//
	int max_input = *(std::max_element(std::begin(Columns), std::end(Columns)));
	int width = 1 + (int)(log((double)max_input) / log(2));
	if (pow(2, width) < max_input){
		OF << "Error occured in file:" << __FILE__ << "\tline:" << __LINE__;
	}
	for (int i = 0; i < Init_Col; ++i){
		OF << "wire[" << (width - 1) << ":0] ";
		OF << "col" << i << "_cnt = ";
		unsigned int cur_width = Columns[i];
		for (int j = 0; j < (int)cur_width; j++){
			OF << "I_col" << i << "[" << j << "]";
			if (j != (int)(cur_width - 1)){
				OF << " + ";
			}
		}
		OF << ";\n";
	}
	OF << "\n";
	
	for (int i = 0; i < Init_Col; i++){
		OF << "wire[" << (Max_Col - 1) << ":0] ";
		OF << "col" << i << "_num" << " = ";
		//OF << "col" << i << "_cnt" << " * " << Max_Col << "\'d" << ((unsigned long long)pow(2, i)) << ";\n";
		OF << "col" << i << "_cnt" << " * " << "(1 << " << i << ");\n";
	}
	OF << "\n";
	
#ifdef GPC_REG_MODE
	OF << "reg[" << (Max_Col - 1) << ":0] " << "true_num_tmp0;\n";
	OF << "reg[" << (Max_Col - 1) << ":0] " << "true_num;\n\n";

	OF << "always @(posedge i_clk)\n";
	OF << "begin\n";
	OF << "true_num_tmp0 <= ";
	for (int i = 0; i < Init_Col; ++i){
		OF << "col" << i << "_num";
		if (i != Init_Col - 1)
			OF << " + ";
	}
	OF << ";\n";
	OF << "true_num <= true_num_tmp0;\n";
	OF << "end\n\n";

#else
	OF << "wire[" << (Max_Col - 1) << ":0] ";
	OF << "true_num = ";
	for (int i = 0; i < Init_Col; i++){
		OF << "col" << i << "_num";
		if (i != Init_Col - 1){
			OF << " + ";
		}
	}
	OF << ";\n\n";
#endif

	OF << "wire error = (O_out == true_num) ? 1'b0 : 1'b1;\n\n";

	OF << "endmodule\n";
}


void GPC_Heuristic_Code_Generation(std::ofstream &OF, std::vector<int> Columns,
	std::vector<std::vector<std::map<std::string, int> > > GPC_Net,
	int K, std::string Module_Name){

	std::map<std::string, int> GPC_Library = Get_Library(GPC_Net);
	int Max_Col = GPC_Net[0].size();
	int Stages = GPC_Net.size();

	GPC_Declare_Top_Module(OF, Columns, Max_Col, Module_Name);

	std::map<int, std::deque<std::string> > Wire = Init_Wire(Max_Col);

	GPC_Declare_Init_Wire(OF, Columns, GPC_Net, Wire);
	for (int stage_index = 0; stage_index < Stages; ++stage_index){
		GPC_Declare_Stage_Wire(OF, GPC_Net, Wire, stage_index);
		GPC_Module_Install(OF, GPC_Net, Wire, stage_index);
	}
	
	GPC_Final_Adder(OF, Wire, K);
	
 	return;
}


