#pragma ACCEL PARALLEL FACTOR=auto{1}
#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{8}
stencil(orig,sol,filter);