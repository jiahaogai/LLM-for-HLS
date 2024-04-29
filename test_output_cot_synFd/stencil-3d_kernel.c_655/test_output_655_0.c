#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[27],double sol[27])
{
  double C2;
  double tmp[3];
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  for (i = 0; i < 3; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 3; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 3; k++) {
        tmp[0] = orig[i * 3 + j * 3 + k];
        tmp[1] = orig[i * 3 + j * 3 + k + 3];
        tmp[2] = orig[i * 3 + j * 3 + k + 6];
        C2 = 0.125 * (tmp[0] + tmp[1] + tmp[2]);
        sol[i * 3 + j * 3 + k] = C2;
        sol[i * 3 + j * 3 + k + 3] = C2 + (tmp[1] - C2);
        sol[i * 3 + j * 3 + k + 6] = C2 + (tmp[2] - C2);
      }
    }
  }
//#pragma endscop
}