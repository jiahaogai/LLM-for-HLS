#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[25][25][30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 25; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (p = 0; p < 30; p++) {
        double sum = ((double )0);
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L3}
	for (s = 0; s < 20; s++) {
          sum += A[r][s][p] * C4[s][q][p];
        }
	A[r][q][p] = sum;
      }
    }
  }
//#pragma endscop
}