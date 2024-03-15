
#pragma ACCEL kernel

void kernel_doitgen(double A[25][20][30],double C4[30][24][20],double D[25][20][24])
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
    for (q = 0; q < 24; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (p = 0; p < 20; p++) {
        A[r][p][q] = ((double )0);
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
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
      for (p = 0; p < 30; p++) {
        double sum = 0.0;
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L5}
	for (s = 0; s < 24; s++) {
          sum += A[s][p][r] * C4[s][q][r];
        }
        D[r][q][p] = sum;
      }
    }
  }
//#pragma endscop
}
