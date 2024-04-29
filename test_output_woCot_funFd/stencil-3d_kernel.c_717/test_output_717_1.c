- `long C0`: Constant value.
- `long C1`: Constant value.
- `long orig[39304]`: Original array.
- `long sol[32768]`: Solution array.
- `long i;long j;long k;long idx;long idx_orig;`: Loop and index variables.
- `long NX;long NY;long NZ;long P;long Q;long R;`:"
- `== CONSTANTS ==`: Separation tag for constants
- `NX = 40;`: Size of the grid in the X direction.
- `NY = 40;`: Size of the grid in the Y direction.
- `NZ = 40;`: Size of the grid in the Z direction.
- `P = 1;`: Number of processes in the X direction.
- `Q = 1;`: Number of processes in the Y direction.
- `R = 1;`: Number of processes in the Z direction.
- `idx_orig = i * (NY * NZ) + j * NZ + k;`:"
- `idx = (i * NY + j) * NZ + k;`:"
- `C0 = 10;`: Constant used in the computation.
- `C1 = 20;`: Constant used in the computation.
- `orig[idx_orig] = C0;`: Initialize the original array.
- `sol[idx] = 1;`: Initialize the solution array.
- `for k = 1 to NZ - 2`: Loop over the grid in the Z direction.
- `for j = 1 to NY - 2`: Loop over the grid in the Y direction.
- `for i = 1 to NX - 2`: Loop over the grid in the X direction.
- `sol[idx] = C1 * orig[idx_orig - 1 - NX*NY] + C1 * orig[idx_orig - 1 - NX] + C1 * orig[idx_orig - 1 - 1] + C1 * orig[idx_orig - NX*NY] + C1 * orig[idx_orig - NX] + C1 * orig[idx_orig - 1] + C1 * orig[idx_orig + 1] + C1 * orig[idx_orig + 1 + NX] + C1 * orig[idx_orig + 1 + NX*NY] + C1 * orig[idx_orig];`: Compute the result for the point (i,j,k).
- `end for`: End loop over k.
- `end for`: End loop over j.
- `end for`: End loop over i.
- `end PIPELINE`: End of pipelined region.
- `end TILE`: End of tile.
- `end ACCEL kernel`: End of kernel stencil3d.

#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long idx_orig;
  long NX;
  long NY;
  long NZ;
  long P;
  long Q;
  long R;
  NX = 40L;
  NY = 40L;
  NZ = 40L;
  P = 1L;
  Q = 1L;
  R = 1L;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (k = 1; k < NZ - 1; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{30}
    for (j = 1; j < NY - 1; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (i = 1; i < NX - 1; i++) {
        idx = (i * NY + j) * NZ + k;
        idx_orig = i * (NY * NZ) + j * NZ + k;
        sol[idx] = C1 * orig[idx_orig - 1 - NX * NY] + C1 * orig[idx_orig - 1 - NX] + C1 * orig[idx_orig - 1 - 1] + C1 * orig[idx_orig - NX * NY] + C1 * orig[idx_orig - NX] + C1 * orig[idx_orig - 1] + C1 * orig[idx_orig + 1] + C1 * orig[idx_orig + 1 + NX] + C1 * orig[idx_orig + 1 + NX * NY] + C1 * orig[idx_orig];
      }
    }
  }
}