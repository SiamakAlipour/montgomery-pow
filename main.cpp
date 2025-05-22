#include <iostream>
#include <cmath>
#include <gmpxx.h>

#define l mpz_class

using namespace std;


l montgomery(l &result, const l &a, const l &b, const l &N , const l &N_prim, const l &R);

l powmpz(l &pow_result , const l &b , const l &e , const l &N , const l &N_prim , const l &R , const l R_pow2);

int main(){
  l b(4), e(2), N(5), N_prim , inv_N , R , R_pow2 , result;

  if( N % 2 == 0) {
    cout << "N should be odd" << endl;
    return -1;
  }

  size_t k = mpz_sizeinbase(N.get_mpz_t(), 2);

  mpz_ui_pow_ui(R.get_mpz_t(), 2, k); // R = 2^k
  cout << "R :" << R << endl;
  

  mpz_invert(inv_N.get_mpz_t(), N.get_mpz_t(), R.get_mpz_t());
  cout << "inv_N : " << inv_N << endl;

  N_prim = ((R - 1) * inv_N) % R;
  cout << "N_prim : " << N_prim << endl;

  mpz_pow_ui(R_pow2.get_mpz_t(), R.get_mpz_t(), 2); 
  R_pow2 = R_pow2 % N;
  cout << "R^2 :" << R_pow2 % N << endl;

  // l mont_a = montgomery(result , a , R_pow2 , N ,N_prim , R);
  // cout << "montgomery of a :" <<mont_a << endl;

  // l mont_b = montgomery(result , b , R_pow2 , N ,N_prim, R);
  // cout << "montgomery of b :" << mont_b << endl;

  // l mult = montgomery(result, mont_a, mont_b, N,N_prim , R);
  // cout << "mult mont a and mont b : " << mult << endl;

  // result = montgomery(result , mult , 1 , N ,N_prim, R);
  // cout << "last result : " << result << endl;

  powmpz(result , b , e , N , N_prim , R , R_pow2);
  cout << "pow("<<b<< "," << e <<") mod " << N << " is : " << result <<endl;

  return 0;
}


l montgomery(l &result, const l &a, const l &b, const l &N , const l &N_prim, const l &R){
    l T = a*b;
    l m = ((T % R) * N_prim)% R;
    result = (T + m * N) / R;
    if (result >= N) {
        result -= N;
        return result;
    }
    return result;
}

l powmpz(l &pow_result , const l &b , const l &e , const l &N , const l &N_prim , const l &R , const l R_pow2){
  string binary_str = e.get_str(2);
  cout << "binary of "<< e << " is : "<<binary_str << endl;
  l b_montgomery = montgomery(pow_result , b , R_pow2 , N , N_prim , R); 

  for (size_t i = 1 ; i < binary_str.length() ; i++)
  {

    montgomery(pow_result , pow_result , pow_result , N , N_prim , R); // S = b and S^2
    cout << i << " " << binary_str[i] <<" : pow result " << pow_result<< endl;


    if (binary_str[i] == '1'){

      montgomery(pow_result , pow_result , b_montgomery , N , N_prim , R); // S = S * b
      cout << i << " : if bit 1 pow result " << pow_result<< endl;

    } 
  }
  montgomery(pow_result , pow_result , 1 , N , N_prim , R);

  return pow_result;
}