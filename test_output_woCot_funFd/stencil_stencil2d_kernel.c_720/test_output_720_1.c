#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmp_0;
  int tmp_1;
  int tmp_2;
  int tmp_3;
  int tmp_4;
  int tmp_5;
  int tmp_6;
  int tmp_7;
  int tmp_8;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop:for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop:for (j = 1; j < 8186; j++) {
      tmp_8 = 0;
      tmp_7 = 0;
      tmp_6 = 0;
      tmp_5 = 0;
      tmp_4 = 0;
      tmp_3 = 0;
      tmp_2 = 0;
      tmp_1 = 0;
      tmp_0 = 0;
      tmp = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loop:for (k = -4; k < 5; k++) {
        tmp_0 += orig[i * 8192 + j * 1 + k] * filter[0];
        tmp_1 += orig[i * 8192 + j * 1 + k] * filter[1];
        tmp_2 += orig[i * 8192 + j * 1 + k] * filter[2];
        tmp_3 += orig[i * 8192 + j * 1 + k] * filter[3];
        tmp_4 += orig[i * 8192 + j * 1 + k] * filter[4];
        tmp_5 += orig[i * 8192 + j * 1 + k] * filter[5];
        tmp_6 += orig[i * 8192 + j * 1 + k] * filter[6];
        tmp_7 += orig[i * 8192 + j * 1 + k] * filter[7];
        tmp_8 += orig[i * 8192 + j * 1 + k] * filter[8];
      }
      tmp = tmp_0 + tmp_1 + tmp_2 + tmp_3 + tmp_4 + tmp_5 + tmp_6 + tmp_7 + tmp_8;
      sol[i * 8192 + j * 1] = tmp;
    }
  }
}