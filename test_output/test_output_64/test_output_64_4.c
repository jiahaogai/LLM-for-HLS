  \n"
			" #pragma ACCEL PIPELINE auto{flatten} \n"
			" #pragma ACCEL TILE FACTOR=auto{1} \n"
			" #pragma ACCEL PARALLEL FACTOR=auto{2} \n"
			" #pragma ACCEL PARALLEL FACTOR=auto{30} \n"
			" #pragma ACCEL PARALLEL FACTOR=auto{10} \n"
			"int C0 = 0; \n"
			"int C1 = 0; \n"
			"int trip_A = 128; \n"
			"int trip_B = 128; \n"
			"int _in_A = 0; \n"
			"int _in_B = 0; \n"
			"int _Aarr = 0; \n"
			"int _Barr = 0; \n"
			"int _Carr_0 = 0; \n"
			"int _Carr_1 = 0; \n"
			"int mul = 0; \n"
			"flatten_loop_A: for(int i = 0;i < 128;i++) { \n"
			"  _in_A = A[i]; \n"
			"  _Aarr = _in_A + 1; \n"
			"  flat_loop_B: for(int j = 0;j < 128;j++) { \n"
			"    _in_B = B[j]; \n"
			"    _Barr = _in_B + 1; \n"
			"    _Carr_0 = C[i][_Aarr]; \n"
			"    _Carr_1 = C[i][_Barr]; \n"
			"    C0 = C_row[0] + _Carr_0; \n"
			"    C1 = C_row[1] + _Carr_1; \n"
			"    mul = C0 * C1; \n"
			"    D[j] = D[j] + mul; \n"
			"  } \n"
			"  C_row[0] = C_row[0] + _Carr_0; \n"
			"  C_row[1] = C_row[1] + _Carr_1; \n"
			" } \n"
			"store: for(int i = 0;i < 128;i++) { \n"
			"  E[i] = C_row[0] + C_row[1]; \n"
			"  C_row[0] = E[i]; \n"
			" }"
			;
			char* after = 			" #pragma ACCEL kernel \n"
			" \n"
			"void kernel_gemm(int ni,int nj,int nk,double alpha,double beta,double C[200][220],double A[200][200],double B[200][220]) { \n"
			"  double tmp[200]; \n"
			"  double mul[200];
//#pragma ACCEL PIPELINE auto{flatten}
			"  for (int i = 0; i < 200; i++) {
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L0}
			"    for (int j = 0; j < 220; j++) {
                   C[i][j] *= beta;
                }
			"  }"
			"  for (int i = 0; i < 200; i++) {
#pragma ACCEL PIPELINE auto{__PIPE__L1}
			"    for (int j = 0; j < 200; j++) {
                   tmp[i] = A[i][j] * alpha;
                   mul[i] = tmp[i] * B[j][219];
					for (int k = 0; k < 220; k++) {
                       C[i][j] += mul[j] * B[i][k];
					}
                   mul[i] = tmp[i] * B[j][218];
					for (int k = 0; k < 220; k++) {
                       C[i][j] += mul[j] * B[i][k];
					}
                   mul[i] = tmp[i] * B[j][217];
					for (int k = 0; k < 220; k++) {
                       C[i][j] += mul[j] * B[i][k];
					}
                   mul[i] = tmp[i] * B[j][216];
					for (int k = 0; k < 220; k++) {
                       C[i][j] += mul[j] * B[i][k];
					}
                   mul[i] = tmp[i] * B[j][215];
					for (int k = 0; k < 220; k++) {
                       C[i][j] += mul[j] * B[i][k];
					}
                   mul[i] = tmp[i] * B[j][214];
					for (int k = 0; k < 220; k++) {
                       C[i][j] += mul[j] * B[i][k];
					}
                   mul[i] = tmp[i] * B[j][213];
					for (int k = 0; k < 220; k++) {
                       C[i][j] += mul[j] * B[i][k];
					}
                   mul[i] = tmp[i] * B[j][212];
					for (int k = 0; k < 220; k++) {
                       C[i][j] += mul[j] * B[i][k];
					}
                   mul[i] = tmp[i] * B[j][211];
					for (int k = 0; k < 220; k++) {
                       C[i][j] += mul[j] * B[i][k];
					}
                   mul[i] = tmp[i] * B[j][210];
					for (int k = 0; k < 220; k++) {
                       C[i][j] += mul[j] * B[i][k];
					}
                   mul[i] = tmp[i] * B[j][209];
					for (int k = 0; k < 220; k++) {
                       C[i][j] += mul[j] * B[i][k];
					}
                   mul[i] = tmp[i] * B[j][208];
					for (int k = 0; k < 220; k++) {
                       C[i][j] += mul[j] * B[i][k];
					}
                   mul[i] = tmp[i] * B[j][207];
					for (int k = 0; k < 220; k++) {
                       C[i][j] += mul[j] * B[i][k];
					}
                   mul[i] = tmp[i] * B[j][206];
				