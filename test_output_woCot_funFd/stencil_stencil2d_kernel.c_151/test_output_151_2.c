#pragma ACCEL kernel

<<<<<<< HEAD
void stencil(double orig[8192],double sol[8192],double filter[9])
=======
void stencil(int orig[8192],int sol[8192],int filter[9])
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
{
  int i;
  int j;
  int k;
<<<<<<< HEAD
  int k_col;
  int i_col;
  double sum;
=======
  int sum;
  double f_entry;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
<<<<<<< HEAD
=======
    sum = 0;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
<<<<<<< HEAD
    for (j = 0; j < 8192; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{64}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((i + (-4 + (k >> 2)))) << 3;
        i_col = ((j + (-4 + (k & 0x3)))) << 3;
        sum += filter[k] * orig[k_col + i_col];
      }
      sol[j] = sum;
    }
=======
    for (j = 0; j < 9; j++) {
      f_entry = filter[j];
      k = i + (-4 + j);
      sum += f_entry * orig[k];
    }
    sol[i] = sum;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  }
}