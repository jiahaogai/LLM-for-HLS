#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = ((0 + filter[0]) * orig[i][j]) + ((0 + filter[1]) * (orig[i][j + 1]) + ((0 + filter[2]) * orig[i][j + 2]) + ((0 + filter[3]) * orig[i][j + 3]) + ((0 + filter[4]) * orig[i][j + 4]) + ((0 + filter[5]) * orig[i][j + 5]) + ((0 + filter[6]) * orig[i][j + 6]) + ((0 + filter[7]) * orig[i][j + 7]) + ((0 + filter[8]) * orig[i][j + 8]) + ((0 + filter[9]) * orig[i][j + 9]) + ((0 + filter[10]) * orig[i][j + 10]) + ((0 + filter[11]) * orig[i][j + 11]) + ((0 + filter[12]) * orig[i][j + 12]) + ((0 + filter[13]) * orig[i][j + 13]) + ((0 + filter[14]) * orig[i][j + 14]) + ((0 + filter[15]) * orig[i][j + 15]) + ((0 + filter[16]) * orig[i][j + 16]) + ((0 + filter[17]) * orig[i][j + 17]) + ((0 + filter[18]) * orig[i][j + 18]) + ((0 + filter[19]) * orig[i][j + 19]) + ((0 + filter[20]) * orig[i][j + 20]) + ((0 + filter[21]) * orig[i][j + 21]) + ((0 + filter[22]) * orig[i][j + 22]) + ((0 + filter[23]) * orig[i][j + 23]) + ((0 + filter[24]) * orig[i][j + 24]));
    }
  }
//#pragma endscop
}