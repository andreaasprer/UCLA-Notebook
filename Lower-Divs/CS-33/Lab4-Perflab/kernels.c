#include "kernels.h"
// Global Matrix for compute_matvec
extern Complex compArr[MATVEC_NI][MATVEC_NJ];

// Global arrays for the real and imag of the compArr matrix
// float realCompArr[MATVEC_NI * MATVEC_NJ]; // For real parts
// float imagCompArr[MATVEC_NI * MATVEC_NJ]; // For imaginary parts


float realArr[MATVEC_NI][MATVEC_NJ], imagArr[MATVEC_NI][MATVEC_NJ];

void init() {
// This function executes once before kernels are executed.  It is not timed.

  for (int i = 0; i < MATVEC_NI; ++i) {
    for (int j = 0; j < MATVEC_NJ; ++j) {
      realArr[i][j] = compArr[i][j].real;
      imagArr[i][j] = compArr[i][j].imag;
    }
  }
}

// Ni -- Dimension of the Output Matrix
void compute_abs(int Ni, float Out[Ni]) {
    // for(int i = 0; i < Ni; ++i) {
    //     if(Out[i] <= 0) {
    //         Out[i] = -Out[i];
    //     } 
    // }
 

    // loop unrolling
    int i = 0;

    for (; i <= Ni - 32; i += 32) {
        Out[i] = fabsf(Out[i]);
        Out[i + 1] = fabsf(Out[i + 1]);
        Out[i + 2] = fabsf(Out[i + 2]);
        Out[i + 3] = fabsf(Out[i + 3]);
        Out[i + 4] = fabsf(Out[i + 4]);
        Out[i + 5] = fabsf(Out[i + 5]);
        Out[i + 6] = fabsf(Out[i + 6]);
        Out[i + 7] = fabsf(Out[i + 7]);
        Out[i + 8] = fabsf(Out[i + 8]);
        Out[i + 9] = fabsf(Out[i + 9]);
        Out[i + 10] = fabsf(Out[i + 10]);
        Out[i + 11] = fabsf(Out[i + 11]);
        Out[i + 12] = fabsf(Out[i + 12]);
        Out[i + 13] = fabsf(Out[i + 13]);
        Out[i + 14] = fabsf(Out[i + 14]);
        Out[i + 15] = fabsf(Out[i + 15]);
        Out[i + 16] = fabsf(Out[i + 16]);
        Out[i + 17] = fabsf(Out[i + 17]);
        Out[i + 18] = fabsf(Out[i + 18]);
        Out[i + 19] = fabsf(Out[i + 19]);
        Out[i + 20] = fabsf(Out[i + 20]);
        Out[i + 21] = fabsf(Out[i + 21]);
        Out[i + 22] = fabsf(Out[i + 22]);
        Out[i + 23] = fabsf(Out[i + 23]);
        Out[i + 24] = fabsf(Out[i + 24]);
        Out[i + 25] = fabsf(Out[i + 25]);
        Out[i + 26] = fabsf(Out[i + 26]);
        Out[i + 27] = fabsf(Out[i + 27]);
        Out[i + 28] = fabsf(Out[i + 28]);
        Out[i + 29] = fabsf(Out[i + 29]);
        Out[i + 30] = fabsf(Out[i + 30]);
        Out[i + 31] = fabsf(Out[i + 31]);
    }

    // Handle the remaining elements
    for (; i < Ni; ++i) {
        Out[i] = fabsf(Out[i]);
    }

}

// Ni,Nj -- Dimensions of the In/Out matricies
// Note that compArr is a global array
void compute_matvec(int Ni, int Nj, const Complex In[Nj], Complex Out[Ni]) {
    // for (int i = 0; i < Ni; i++) {
    //     Out[i].real = 0.0f;
    //     Out[i].imag = 0.0f;
    //     for (int j = 0; j < Nj; j++) {
    //         Complex product = complex_multiply(compArr[i][j], In[j]);
    //         Out[i] = complex_add(Out[i], product);
    //     }
    // }

  // tiling and loop unrolling
  int tileSize = 64; 

  for (int i = 0; i < Ni; i++) {
    Out[i].real = 0.0f;
    Out[i].imag = 0.0f;
  }

  for (int ii = 0; ii < Ni; ii += tileSize) {
    for (int jj = 0; jj < Nj; jj += tileSize) {
            
      for (int i = ii; i < ii + tileSize && i < Ni; i++) {
        float realSum = 0.0f;
        float imagSum = 0.0f;

        int j;
        for (j = jj; j + 3 < jj + tileSize && j + 3 < Nj; j += 4) {
          float realPart0 = realArr[i][j] * In[j].real - imagArr[i][j] * In[j].imag;
          float imagPart0 = realArr[i][j] * In[j].imag + imagArr[i][j] * In[j].real;
          realSum += realPart0;
          imagSum += imagPart0;

          float realPart1 = realArr[i][j+1] * In[j+1].real - imagArr[i][j+1] * In[j+1].imag;
          float imagPart1 = realArr[i][j+1] * In[j+1].imag + imagArr[i][j+1] * In[j+1].real;
          realSum += realPart1;
          imagSum += imagPart1;

          float realPart2 = realArr[i][j+2] * In[j+2].real - imagArr[i][j+2] * In[j+2].imag;
          float imagPart2 = realArr[i][j+2] * In[j+2].imag + imagArr[i][j+2] * In[j+2].real;
          realSum += realPart2;
          imagSum += imagPart2;

          float realPart3 = realArr[i][j+3] * In[j+3].real - imagArr[i][j+3] * In[j+3].imag;
          float imagPart3 = realArr[i][j+3] * In[j+3].imag + imagArr[i][j+3] * In[j+3].real;
          realSum += realPart3;
          imagSum += imagPart3;
        }

        // Handle any remaining elements (when Nj is not a multiple of 4)
        for (; j < jj + tileSize && j < Nj; j++) {
          float realPart = realArr[i][j] * In[j].real - imagArr[i][j] * In[j].imag;
          float imagPart = realArr[i][j] * In[j].imag + imagArr[i][j] * In[j].real;
          realSum += realPart;
          imagSum += imagPart;
        }

        Out[i].real += realSum;
        Out[i].imag += imagSum;
      }
    }
  }
}

// Ni,Nj -- Dimensions of the In/Out matricies
void compute_transpose(int Ni, int Nj,
                    const char In[Ni][Nj], char Out[Nj][Ni]) {
  // for(int j = 0; j < Nj; ++j) {
  //   for(int i = 0; i < Ni; ++i) {
  //     move_one_value(i,j,j,i,Ni,Nj,In,Out);
  //   }
  // }

  // add tiling
  int tileSize = 200;
  for (int i = 0; i < Ni; i += tileSize) {
    for (int j = 0; j < Nj; j += tileSize) {
      // process each tile
      for (int ti = i; ti < i + tileSize && ti < Ni; ++ti) {
        for (int tj = j; tj < j + tileSize && tj < Nj; ++tj) {
            Out[tj][ti] = In[ti][tj];
        }
      }
    }
  }
}


// Ni,Nj,Nk -- Dimensions of the output matrix
// S -- width/length/height of the stencil
void compute_stencil(int Ni, int Nj, int Nk, int S, 
            const float In[Ni+S][Nj+S][Nk+S], float Out[Ni][Nj][Nk], 
            const float Stencil[S][S][S]) {
  if (Ni == 128) {
    compute_stencil_1(In, Out, Stencil);
  } else if (Ni == 64) {
    compute_stencil_2(In, Out, Stencil);
  }
  else {
    compute_stencil_3(In, Out, Stencil);
  }
  

}


void compute_stencil_1(const float In[128 + 8][128 + 8][128 + 8], 
                       float Out[128][128][128], 
                       const float Stencil[8][8][8]) {
  for (int i = 0; i < 128; ++i) {
    for (int j = 0; j < 128; ++j) {
      for (int k = 0; k < 128; ++k) {
        Out[i][j][k] = 0.0;
        float sum = 0.0f;
        for (int z = 0; z < 8; ++z) {
          for (int y = 0; y < 8; ++y) {
            for (int x = 0; x < 8; ++x) {
              float input_val = In[i + x][j + y][k + z];
              float stencil_val = Stencil[x][y][z];
              sum += input_val * stencil_val;  
        } } }
        Out[i][j][k] = sum;
  } } }
}

void compute_stencil_2(const float In[64 + 20][64 + 20][64 + 20],
                       float Out[64][64][64],
                       const float Stencil[20][20][20]) {
    // change ordering with unrolling
    for (int i = 0; i < 64; ++i) {
        for (int j = 0; j < 64; ++j) {
            for (int k = 0; k < 64; ++k) {
                float sum = 0.0f;
              for (int y = 0; y < 20; ++y) {
                for (int z = 0; z < 20; ++z) {
                  for (int x = 0; x < 20; x += 2) {
                            sum += In[i + x][j + y][k + z] * Stencil[x][y][z];
                            sum += In[i + x + 1][j + y][k + z] * Stencil[x + 1][y][z];
                } } }
                
                Out[i][j][k] = sum;
    } } }
}



void compute_stencil_3(const float In[4 + 2][4 + 2][1048576 + 2],
                       float Out[4][4][1048576],
                       const float Stencil[2][2][2]) {
  // for unrolling stencils
  const float stencilVals[8] = {
      Stencil[0][0][0], Stencil[1][0][0],
      Stencil[0][1][0], Stencil[1][1][0],
      Stencil[0][0][1], Stencil[1][0][1],
      Stencil[0][1][1], Stencil[1][1][1]};

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      for (int k = 0; k < 1048576; ++k) {
        float sum = 0.0f;

        sum += In[i][j][k] * stencilVals[0];
        sum += In[i + 1][j][k] * stencilVals[1];
        sum += In[i][j + 1][k] * stencilVals[2];
        sum += In[i + 1][j + 1][k] * stencilVals[3];
        sum += In[i][j][k + 1] * stencilVals[4];
        sum += In[i + 1][j][k + 1] * stencilVals[5];
        sum += In[i][j + 1][k + 1] * stencilVals[6];
        sum += In[i + 1][j + 1][k + 1] * stencilVals[7];

        Out[i][j][k] = sum;
      }
    } 
  }
}
