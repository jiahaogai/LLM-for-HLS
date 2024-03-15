#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][30],double B[25][20][30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L3}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
      for (p = 0; p < 30; p++) {
        double sum = A[r][q][p];
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L4}
	for (s = 0; s < 30; s++) {
          sum += A[r][q][s] * C4[s][p];
        }
        B[r][q][p] = sum;
      }
    }
  }
//#pragma endscop
}