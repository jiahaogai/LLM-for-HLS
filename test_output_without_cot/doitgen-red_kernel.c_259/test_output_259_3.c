#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}

void kernel_doitgen(double A[25][20][30],double C4[30][30],double sum[30])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      for (s = 0; s < 30; s++) {
        A[r][q][s] *= C4[s][q];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (q = 0; q < 20; q++) {
      sum[r] = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L5}
      for (s = 0; s < 30; s++) {
        sum[r] += A[r][q][s];
      }
    }
  }
//#pragma endscop
}