//MATEEV IGOR
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

//This function puts just ONE element's sum from matrix M*M with center in (k,line) in array S
void SUM (double MATRIX[], int N, int M, double S[], int k, int line){
    for(int s=0; s<M; s++){
        for(int i=0; i<M; i++){
            S[k-line*(M-1)]+=MATRIX[k+i+N*s];
        }
    }
}

//This function puts EVERY element's sum matrix M*M in matrix N*N in array S
void GENERATE (double MATRIX[], int N, int M, double S[], int W){
    for(int s=0; s<W; s++){
        for(int i=0; i<W; i++){
                SUM(MATRIX, N, M, S, i+s*N,s);
        }
    }
}

//This function displays information about maximum submatrix M*M with coordinates left top element k in array MATRIX
void INFORMATION (double MATRIX[], int N, int M, int k, double MAXIMUM){
    ofstream file;
    file.open("RESULT.txt",  ios_base::out | ios_base::binary);
    if(!file) {
            cout<<"ERROR, can't open file to write."<<endl;
            exit(2);
    }
    cout<<"The max sum:    "<<MAXIMUM<<'\n'<<endl;
    file<<"The max sum:    "<<MAXIMUM<<'\n'<<endl;

    cout<<"The coordinates elements from max matrix M*M: (line, column)"<<'\n'<<endl;
    file<<"The coordinates elements from max matrix M*M: (line, column)"<<'\n'<<endl;

    int line=(k/N)+1;
    int column=k-(line-1)*N;
    for(int s=0; s<M; s++){
        for(int i=0; i<M; i++){
            cout<<setw(6)<<'('<<line+s<<','<<column+i<<')';
            file<<setw(6)<<'('<<line+s<<','<<column+i<<')';
        }
        cout<<endl;
        file<<endl;
    }

    cout<<"\n\n"<<endl;
    file<<"\n\n"<<endl;

    cout<<"The max matrix M*M:"<<'\n'<<endl;
    file<<"The max matrix M*M:"<<'\n'<<endl;
    for(int s=0; s<M; s++){
        for(int i=0; i<M; i++){
            cout<<setw(9)<<MATRIX[k-1+i+N*s]<<'\t';
            file<<setw(9)<<MATRIX[k-1+i+N*s]<<'\t';
        }
        cout<<"\n\n"<<endl;
        file<<"\n\n"<<endl;
    }
    file.close();
}

int main(){
    int N, M, NN, NM, W;
    double *MATRIX, *S;

    //Read file and get information about M and N
    ifstream file;
    file.open("matrix500",  ios_base::in | ios_base::binary);
    if(!file) {
            cout<<"ERROR, can't open file matrix500"<<endl;
            exit(2);
    }
    file>>N;
    file>>M;

    NN=N*N;                     //Elements in matrix N*N
    NM=(N+1-M)*(N+1-M);         //Elements in matrix N*N without one matrix M*M
    W=N+1-M;                    //Computational boundaries in matrix N*N


    MATRIX = new double[N*N];

    //Save matrix's elements in linear array MATRIX
    for(int i=0; i<NN; i++){
        file>>MATRIX[i];
    }
    file.close();

    //Create linear array where we're going to save every submatrix's sum.
    S = new double[NM];
    for (int i=0; i<NM; i++){
        S[i]=0;
    }

    //Save every submatrix's sum in S
    GENERATE(MATRIX, N, M, S, W);

    //Search max sum and coordinates
    double MAXIMUM=S[0];
    int realCORDINATE;
    int CORDINATE=0;
    for(int i=0; i<NM; i++){
        if(S[i]>MAXIMUM) MAXIMUM=S[i], CORDINATE=i;
    }
    realCORDINATE = CORDINATE + (CORDINATE/W)*(M-1) + 1;    //Translate coordinate top left element (max element's number in S) from array S in coordinates in array N (max element's number in N)

    //Display information
    INFORMATION(MATRIX, N, M, realCORDINATE, MAXIMUM);

    delete (S);
    delete(MATRIX);
    return 0;
}
