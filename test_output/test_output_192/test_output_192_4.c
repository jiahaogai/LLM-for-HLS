

 #pragma ACCEL kernel

void kernel_doitgen(int idx,int idy,int full[25][20][30],int filter[20][25][1][9])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 20; q++) {
      for (p = 0; p < 30; p++) {
        full[r][q][p] = ((int )0);
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (q = 0; q < 20; q++) {
      for (p = 0; p < 30; p++) {
        for (s = 0; s < 5; s++) {
          full[r][q][p] += filter[q][r][0][s] * ((int )((double )((ifthen(s + p - 2 >= 0 && s + p - 2 < 30, 30, ((int )0))) * ((ifthen(r + q - 2 >= 0 && r + q - 2 < 25, 25, ((int )0))) * ((ifthen(s + p - 2 >= 0 && s + p - 2 < 30, 30, ((int )0)))))) * (double )((ifthen(r + q - 2 >= 0 && r + q - 2 < 25, 25, ((int )0)))) * (double )((ifthen(s + p - 2 >= 0 && s + p - 2 < 30, 30, ((int )0)))) * (double )((ifthen(r + q - 2 >= 0 && r + q - 2 < 25, 25, ((int )0))))));
        }
      }
    }
  }
//#pragma endscop
}
