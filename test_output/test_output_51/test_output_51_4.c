
 #pragma ACCEL kernel

void kernel_doitgen(int nr,int nq,int np,double A[25][20][30],double C4[25][30],double B[25][23][30],double D[25][20])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int u;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      for (s = 0; s < 30; s++) {
        A[r][q][s] = ((double )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L4}
      for (p = 0; p < 30; p++) {
        double sum = 0.0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L5}
	for (s = 0; s < 23; s++) {
          sum = sum + B[r][s][p] * D[s][q];
        }
	C4[r][p] = sum;
	double sum_0 = 0.0;
#pragma ACCEL PARALLEL reduction=sum_0 FACTOR=auto{__PARA__L6}
	for (s = 0; s < 20; s++) {
          sum_0 = sum_0 + A[r][s][p] * C4[s][p];
        }
	A[r][q][p] = sum_0;
      }
    }
  }
//#pragma endscop
}
