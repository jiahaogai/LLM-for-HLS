
 #pragma ACCEL kernel

void kernel_doitgen(int A[25][20][30],int C4[30][28][20])
{
  int r;
  int q;
  int p;
  int s;
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (q = 0; q < 20; q++) {
      
#pragma ACCEL PIPELINE auto{__PIPE__L2}
      
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
      for (p = 0; p < 30; p++) {
        A[r][q][p] = ((long )r) * (((long )q) * (((long )p) * 2));
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
        
#pragma ACCEL PIPELINE auto{__PIPE__L5}
        for (i = 1; i < 5; i++) {
          s = r + 2;
          t = q + 2;
#pragma ACCEL PARALLEL reduction=C4 FACTOR=auto{__PARA__L6}
          for (j = 0; j < 4; j++) {
            C4[p][s + j][t] += A[r][q][p + j] * ((long )i) * 2;
          }
        }
      }
    }
  }
//#pragma endscop
}
