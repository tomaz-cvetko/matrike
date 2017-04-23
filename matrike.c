#include <stdio.h>
#include <stdlib.h>

float **ustvari_matriko(int rows, int cols){
  float **A;
  A = malloc(rows * sizeof *A);
  for(int i = 0; i < rows; i++){
    *(A+i) = (float*)malloc(cols*sizeof **(A+i));
  }

  return A;
}

void napolni_matriko(float **matrika, int rows, int cols, int index){
  printf("You will fill your matrix number %d row by row:\n", index);
  for (int i = 0; i < rows; i++){
    //printf("\nEnter numbers in the %dth row: <num1> <num2> ... <num%d>\n", i+1, cols);
    printf("%d: ", i+1);
    for (int j = 0; j < cols; j++){
      float a;
      scanf("%f", &a);
      matrika[i][j] = a;
    }
  }
}

void print_matrix(float **matrika, int rows, int cols, int index){
  printf("This is your matrix number %d\n", index);
  for (int i = 0; i < rows; i++){
    printf("|| ");
    for (int j = 0; j < cols; j++){
      float a = matrika[i][j];
      printf("%12.4f ", a);
    }
    printf("||\n");
  }
  printf("\n");
}

void zamenjaj_vrstici(float **matrika, int prva, int stolpci, int druga){ //funkcija dela
  //zamenja prvo in drugo vrstico (vrednosti v vsakem stolpcu)
  float *t = matrika[prva];
  matrika[prva] = matrika[druga];
  matrika[druga] = t;
}

void deli_vrstico(float **matrika, int vrstica, int stolpci, float stevilo){ //funkcija dela parametri!!!
  //deli vrstico z vrednostjo v prvem veljavnem mestu
  if (stevilo == 0.0){
    printf("WTF");
    return;
  }
  for (int j = 0; j < stolpci; j++){
    matrika[vrstica][j] /= stevilo;
  }
}

void odstej_xvrstico(float **matrika, int tarca, int zacetek, int stolpci, int sredstvo, float x){
  //tarca - x*sredstvo = cilj oziroma 0 v stolpcu zacetek (point funkcije)
  if (x == 0) return;
  for(int j = zacetek; j < stolpci; j++){
    matrika[tarca][j] -= x*matrika[sredstvo][j];
  }
}

void gauss_jordan(float **znana, int rows, int cols, float **pridruzena){
  int vrstica = 0;
  for(int j = 0; j < cols; j++){
    int test = 0;
    //najdi row v katerem col. ni 0
    for (int i = vrstica; i < rows; i++){
      if(znana[i][j] != 0){
        if(vrstica != i){
          zamenjaj_vrstici(znana, vrstica, cols, i);
          zamenjaj_vrstici(pridruzena, vrstica, cols, i); //matriki sta istih dimenzij

          printf("Zamenjani vrstici:\n");
          print_matrix(znana, rows, cols, 1);
          print_matrix(pridruzena, rows, cols, 2);
          //do tu je vse super
        }
        test = 1;
        break;
      }
      continue;
    }
    if(test == 1){
      float m = znana[vrstica][j];
      if (m != 1){
        deli_vrstico(znana, vrstica, cols, m);
        deli_vrstico(pridruzena, vrstica, cols, m);

        printf("Zdeljeni vrstici z %.2f:\n", m);
        print_matrix(znana, rows, cols, 1);
        print_matrix(pridruzena, rows, cols, 2);
      }

      //v znani matriki je v j-tem stolpcu in vrstici vrstica vrednost 1
      //iznici ostale
      for(int k = 0; k < rows; k++){
        float x = znana[k][j];
        if(k != vrstica && x != 0){
          odstej_xvrstico(znana, k, j, cols, vrstica, x);
          odstej_xvrstico(pridruzena, k, 0, cols, vrstica, x);

          printf("Odsteti vrstici:\n");
          print_matrix(znana, rows, cols, 1);
          print_matrix(pridruzena, rows, cols, 2);
        }
        else continue;
      }
      //vse vrednosti razen ene so iznicene, lahko gre v naslednji stolpec in tudi vrstica, ki jo nastavljamo je +1
      vrstica++;
    }
  }
}

int main(void){
  int rows, cols;
  float **matrika1, **matrika2;
  printf("NAVODILA:\nProgram izvede Gauss-Jordanov algoritem na prvi vneseni matriki\nin enake vrsticne operacije izvede \
  tudi na drugi (pridruzeni matriki).\nTo lahko uporabimo za: \n a) racunanje inverza prve matrike, ce kot drugo vnesemo identiteto ustrezne dimenzije \
  \n b) resitev navadne matricne enacbe (kvadratne matrike) A*X = B, A prva matrika, B rezulat in X neznana matrika \
  \n c) racunanje resitev sistema inearnih enacb, ce v prvi stolpec druge matrike vnesemo desne strani enacajev\n");
  printf("=====================================================================================================\n");
  printf("\nEnter two numbers: <rows> <cols> (st.vrstic in st.stolpcev)\n");
  scanf("%d", &rows);
  //printf("Enter two numbers: <rows> <cols>\n");
  scanf("%d", &cols);

  //zaenkrat matriki enaki
  matrika1 = ustvari_matriko(rows, cols);
  matrika2 = ustvari_matriko(rows, cols);
  //printf("\nMatrices made");
  //print_matrix(matrika1, rows, cols, 1);
  //print_matrix(matrika2, rows, cols, 2);

  napolni_matriko(matrika1, rows, cols, 1);
  napolni_matriko(matrika2, rows, cols, 2);
  printf("\nMatrices filled\n");
  print_matrix(matrika1, rows, cols, 1);
  print_matrix(matrika2, rows, cols, 2);

  gauss_jordan(matrika1, rows, cols, matrika2);
  printf("\nAlgorithm complete. Printing results: ...\n\n");
  print_matrix(matrika1, rows, cols, 1);
  print_matrix(matrika2, rows, cols, 2);

  for(int i = 0; i < rows; i++){
    free(*(matrika1+i));
    free(*(matrika2+i));
  }
  free(matrika1);
  free(matrika2);


  printf("\nthe end\nto exit enter a letter:");
  fflush(stdin);
  getchar();

  return 0;
}
