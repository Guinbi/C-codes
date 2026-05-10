/*
    Esse programa calcula o zero de uma função contínua pelo método da Bissecção.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double func(double x){
  double result = (4 * pow(x, 5.0)) + (7 * pow(x, 2.0)) + (4.0 * x) + 3.0; // Troque <expr> pela expressão da função.
  return result;
}

int existeZero(double a, double b){
  if((func(a)*func(b))<0){
    return 1;
  }
  else{
    return 0;
  }
}

double Bisseccao(double a, double b, double Erro_tol) {

  if(existeZero(a,b) == 0){
    printf("Não há garatias de existência de um zero no intervalo dado.\n\nReinicie com outro intervalo!\n");
    return 0;
  }
  else{
    int n = 1;
    double x = (a+b)/2;
    double xAnt = 0;
    double Er = fabsf(func(x));
    double Ex = 0;
    printf("\nDados das Iterações:\n\n");
    printf("x[%2d] = %.25lf | Er[%2d] = %.25lf | Ex[%2d] = --\n",n,x,n,Er,n);
    do{
      if(func(x) == 0){
        printf("O zero é extamente: x{%d} = ", n);
        return x;
      }
      n++;
      xAnt = x;
      if(existeZero(a,x)){
        b = x;
      }else{
        a = x;
      }
      x = (a+b)/2;
      Er = fabsf(func(x));
      Ex = fabsf(x - xAnt);
      printf("x[%2d] = %.25lf | Er[%2d] = %.25lf | Ex[%2d] = %.25lf\n",n,x,n,Er,n,Ex);
    }while(Er > Erro_tol || Ex > Erro_tol);
    return 0;
  }
}

int main(){
    double a, b, Erro_tol;
    printf("Entre com os valores do extremos do intervalo de busca [a , b].\n");
    printf("a = ");
    scanf("%lf",&a);
    printf("b = ");
    scanf("%lf",&b);
    printf("Digite o erro tolerado: ");
    scanf("%lf", &Erro_tol);


    double result = Bisseccao(a,b,Erro_tol);
    return 0;
}