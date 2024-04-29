Expected: 
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  int middle;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  middle = 4 + 8;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  int tmp_1;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  tmp_1 = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  int tmp_2;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  tmp_2 = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  int tmp_3;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  tmp_3 = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  int tmp_4;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  tmp_4 = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  int tmp_5;
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  tmp_5 = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  int tmp_6;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  tmp_6 = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  int tmp_7;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  tmp_7 = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  int tmp_8;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  tmp_8 = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  int tmp_9;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  tmp_9 = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FA