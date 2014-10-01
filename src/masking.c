#include <R.h>
#include <Rdefines.h>
#include <Rinternals.h>
#include <stdio.h>
#include <stdlib.h>

SEXP masking(SEXP simgData, SEXP smask,
	     SEXP srow, SEXP scol, 
	     SEXP smaskrow, SEXP smaskcol)
{
  int nrow, ncol, maskrow, maskcol,
    i, j, k, l, mr2, mc2;
  double *imgData, *mask, *pmaskedImg, sum;
  SEXP maskedImg;

  nrow = asInteger(srow);
  ncol = asInteger(scol);
  maskrow = asInteger(smaskrow);
  maskcol = asInteger(smaskcol);
  imgData = REAL(simgData);
  mask = REAL(smask);
  mr2 = (maskrow/2);
  mc2 = (maskcol/2);

  maskedImg = PROTECT(NEW_NUMERIC(nrow * ncol));
  pmaskedImg = NUMERIC_POINTER(maskedImg);

  /* for(i = 0; i < nrow - maskrow; i++) { */
  /*   for(j = 0; j < ncol - maskcol; j++) { */
  /*     sum = 0; */
  /*     for(k = 0; k < maskrow; k++) { */
  /* 	for(l = 0; l < maskcol; l++) {  */
  /* 	  sum = sum + ( */
  /* 		       imgData[(j + k) * nrow + (i + l)] *  */
  /* 		       mask[k * maskrow + l] */
  /* 		       ); */
  /* 	} */
  /*     } */
  /*     pmaskedImg[(j + mc2) * nrow + i + mr2] = sum; */
  /*   } */
  /* } */
  for(i = 0; i < nrow; i++) {
    for(j = 0; j < ncol; j++) {
      pmaskedImg[j * nrow + i] = 0;
    }
  }

  for(i = 0; i < nrow - 2 * mr2; i++) {
    for(j = 0; j < ncol - 2 * mc2; j++) {
      sum = 0;
      for(k = 0; k < maskrow; k++) {
  	for(l = 0; l < maskcol; l++) {
  	  sum = sum + (
  		       imgData[(j + l) * nrow + (i + k)] *
  		       mask[l * maskrow + k]
  		       );
  	}
      }
      pmaskedImg[(j + mc2) * nrow + i + mr2] = sum;
    }
  }

  UNPROTECT(1);
  return maskedImg;
}


