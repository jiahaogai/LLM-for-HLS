#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int fi;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PARALLEL reduction = orig FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      ti = i - 4 + j;
      sol[i] += filter[j] * (ti < 0 ? 0 : (ti > 8191 ? 0 : orig[ti]));
    }
  }
//#pragma endscop
}