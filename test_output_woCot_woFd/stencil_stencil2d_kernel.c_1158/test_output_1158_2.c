#pragma ACCEL kernel

### PIPELINE auto{off}

### TILE FACTOR=auto{1}

### PARALLEL FACTOR=auto{7}

int main(int argc,char **argv)
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  stencil(orig,sol1,filter);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{31}
  stencil(sol1,sol2,filter);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  stencil(sol2,sol,filter);
//#pragma endscop
}