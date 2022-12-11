//Midterm Project
//A template class for the sparse matrix

#include<iostream>

using namespace std;
const int MaxSize = 100;
typedef int ElemType;

struct Triple {
    int row;
    int col;
    int value;
    ElemType e;

    Triple &operator=(Triple &x) {
        row = x.row;
        col = x.col;
        value = x.value;
        return *this;
    };
};

class SMatrix {
private:
    SMatrix(int i) {

    }

    int row_sum;
    int col_sum;
    int ele_sum;
    Triple data[MaxSize];
    Triple *smArray;
    int maxTerms;

public:
    //Construct functions to initialize an empty triplet table
    //SMatrix();
    //Release memory
    //~SMatrix() { delete& row_sum, & col_sum, & ele_sum; delete[] & data; };
    //Construct functions to construct a sparse matrix from the original matrix
    //SMatrix(int** d, int m, int n);
    //Iterate over the matrix and output
    //void Matrixdisplay();
    //Matrix transpose
    //SMatrix* MatrixTrans();
    //Matrix multiplication
    //SMatrix* MultiMatrix(SMatrix* mb);

    SMatrix() {
        this->row_sum = 0;
        this->col_sum = 0;
        this->ele_sum = 0;
    }

    /*
        Constructing functions (with parameters)
        Input： int array[][], int row_num, int col_num
        Return： SMatrix
    */
    SMatrix(int **d, int m, int n) {
        //If the matrix is empty, construct the default array
        if (NULL == d || m <= 0 || n <= 0) {
            SMatrix();
            return;
        }
        //Otherwise initialize
        this->row_sum = m;
        this->col_sum = n;
        this->ele_sum = 0;
        //Temporary Variables
        int e = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                //Take the value of the array corresponding to the i, j subscripts
                e = *((int *) d + n * i + j);
                if (0 == e) {
                    continue;
                }
                this->data[ele_sum].row = i;
                this->data[ele_sum].col = j;
                this->data[ele_sum].e = e;
                this->ele_sum++;
            }
        }
    }

    SMatrix(int m, int n){
        this->row_sum = m;
        this->col_sum = n;
        this->ele_sum = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                //Take the value of the array corresponding to the i, j subscripts
                this->data[ele_sum].row = i;
                this->data[ele_sum].col = j;
                this->data[ele_sum].e = 0;
                this->ele_sum++;
            }
        }
    }

    /*
        Print the sparse matrix
    */
    void Matrixdisplay() {
        int t = 0;
        for (int i = 0; i < this->row_sum; i++) {
            for (int j = 0; j < this->col_sum; j++) {
                if (t < this->ele_sum && this->data[t].row == i && this->data[t].col == j) {
                    cout << this->data[t++].e << " ";
                } else {
                    cout << 0 << " ";
                }
            }
            cout << endl;
        }
    }
    /*
        Adding the matrixs
    */
    SMatrix Add(SMatrix &b) {
//        SMatrix Result(row_sum*col_sum);     //The results are stored in the Result

//        cout << this->smArray << endl;
        SMatrix result = *new SMatrix();

        if (row_sum != b.row_sum || col_sum != b.col_sum) {    //Only matrices with the same size can be added together
            cout << "Incompatible matrices" << endl;
            return result;
        }
        result.row_sum = row_sum;
        result.col_sum = col_sum;
        result.ele_sum = row_sum * col_sum;
        result.maxTerms = row_sum * col_sum;
        int i = 0, j = 0, index_a, index_b;
        while (i < ele_sum && j < b.ele_sum) {
            index_a = this->smArray[i].row * col_sum + smArray[i].col;
            index_b = b.smArray[j].row * b.col_sum + b.smArray[i].col;
            if (index_a < index_b) {
                result.smArray[result.ele_sum].row = smArray[i].row;
                result.smArray[result.ele_sum].col = smArray[i].col;
                result.smArray[result.ele_sum].value = smArray[i].value;
                i++;
            }
            if (index_a > index_b) {
                result.smArray[result.ele_sum].row = b.smArray[j].row;
                result.smArray[result.ele_sum].col = b.smArray[j].col;
                result.smArray[result.ele_sum].value = b.smArray[j].value;
                j++;
            }
            if (index_a == index_b) {
                if (smArray[i].value + b.smArray[j].value) {
                    result.smArray[result.ele_sum].row = smArray[j].row;
                    result.smArray[result.ele_sum].col = smArray[j].col;
                    result.smArray[result.ele_sum].value = smArray[i].value + b.smArray[j].value;
                    i++;
                    j++;
                }
            }
            result.ele_sum++;
        }
        for (; i < ele_sum; i++) {
            result.smArray[result.ele_sum].row = smArray[i].row;
            result.smArray[result.ele_sum].col = smArray[i].col;
            result.smArray[result.ele_sum].value = smArray[i].value;
            i++;
            result.ele_sum++;
        }
        for (; j < b.ele_sum; j++) {
            result.smArray[result.ele_sum].row = b.smArray[j].row;
            result.smArray[result.ele_sum].col = b.smArray[j].col;
            result.smArray[result.ele_sum].value = b.smArray[j].value;
            j++;
            result.ele_sum++;
        }
        return result;
    }

    SMatrix myAdd(SMatrix b){
        int temp = 0;
        SMatrix a = *this;
        if (a.row_sum != b.row_sum || a.col_sum != b.col_sum) {
            cout << "Incompatible matrices" << endl;
            return NULL;
        }
        SMatrix c = *new SMatrix(a.row_sum, b.col_sum);
        c.ele_sum = 0;
//        c.row_sum = a.row_sum;
//        c.col_sum = b.col_sum;

        for(int i = 0; i <= a.ele_sum;){
            for(int j = 0; j <= b.ele_sum;){
                if(a.data[i].row>b.data[j].row){
                    c.data[temp].row=b.data[j].row;
                    c.data[temp].col=b.data[j].col;
                    c.data[temp].e=b.data[j].e;
                    c.ele_sum++;
                    temp++;j++;
                }
                else if(a.data[i].row<b.data[j].row)
                {
                    c.data[temp].row=a.data[i].row;
                    c.data[temp].col=a.data[i].col;
                    c.data[temp].e=a.data[i].e;
                    c.ele_sum++;
                    temp++;i++;
                }
                else
                {
                    if(a.data[i].col>b.data[j].col)
                    {
                        c.data[temp].row=b.data[j].row;
                        c.data[temp].col=b.data[j].col;
                        c.data[temp].e=b.data[j].e;
                        c.ele_sum++;
                        temp++;j++;
                    }
                    else if(a.data[i].col<b.data[j].col)
                    {
                        c.data[temp].row=a.data[i].row;
                        c.data[temp].col=a.data[i].col;
                        c.data[temp].e=a.data[i].e;
                        c.ele_sum++;
                        temp++;i++;
                    }
                    else
                    {
                        c.data[temp].row=a.data[i].row;
                        c.data[temp].col=a.data[i].col;
                        c.data[temp].e=a.data[i].e+b.data[j].e;
                        c.ele_sum++;
                        temp++;i++;j++;
                    }
                }
            }
        }
        return c;
    }


    /*
        Transpose the Matrix
    */
    SMatrix *MatrixTrans() {
        SMatrix *MT = new SMatrix();
        MT->row_sum = this->col_sum;
        MT->col_sum = this->row_sum;
        MT->ele_sum = this->ele_sum;
        //Array of non-zero elements per column
        int *col_num = new int[this->col_sum]{0};
        for (int i = 0; i < this->ele_sum; i++) {
            col_num[data[i].col]++;
        }
        //The first non-zero element in each column corresponds to the subscript position of the transposed sparse matrix
        int *col_position = new int[this->col_sum]{0};
        for (int i = 1; i < this->col_sum; i++) {
            col_position[i] = col_position[i - 1] + col_num[i - 1];
        }
        //Realize transposition
        int p = 0;
        for (int i = 0; i < this->ele_sum; i++) {
            p = col_position[this->data[i].col]++;
            MT->data[p].row = this->data[i].col;
            MT->data[p].col = this->data[i].row;
            MT->data[p].e = this->data[i].e;
        }
        return MT;
    }

    /*
        Matrix multiplication
    */
    SMatrix *MultiMatrix(SMatrix *MB) {
        //Legitimacy check
        if (this->col_sum != MB->row_sum) {
            cout << "These two matrices cannot be multiplied together!" << endl;
            return NULL;
        }
        if (this->ele_sum == 0 || MB->data == 0) {
            cout << "The result is a zero matrix!" << endl;
            return NULL;
        }

        //Initialize the result matrix
        SMatrix *MResult = new SMatrix();
        MResult->row_sum = this->row_sum;
        MResult->col_sum = MB->col_sum;
        MResult->ele_sum = 0;

        //Array of non-zero elements per row
        int *row_num = new int[MB->row_sum]{0};
        for (int i = 0; i < MB->ele_sum; i++) {
            row_num[MB->data[i].col]++;
        }
        //The array of subscript positions of the first non-zero element in each row in its sparse matrix
        int *row_position = new int[MB->row_sum]{0};
        for (int i = 1; i < MB->row_sum; i++) {
            row_position[i] = row_position[i - 1] + row_num[i - 1];
        }
        //Multiplying arrays
        //Iterate through the 1D sparse matrix of the matrix A
        int EA = 0, EB = 0;    //Initialize A and B matrix elements E to 0
        int IA = 0, IB = 0, JA = 0, JB = 0;
        int NB = 0;    //Initialize the number of non-zero elements in a row of the matrix B
        int PB = 0;
        int *row_result = new int[MB->col_sum]{
                0};//Temporary storage of the product of each row of the matrix A and each column of the matrix B, the cumulative result
        for (int p = 0; p < this->ele_sum; p++) {
            //Get the elements of matrix A (ia,ja,ea)
            IA = this->data[p].row;
            JA = this->data[p].col;
            EA = this->data[p].e;
            IB = JA;
            //Locate the position of the subscript of the non-zero data element in row IB of the B matrix (corresponding to that in the sparse matrix)
            PB = row_position[IB];
            //Get the number of non-zero elements in row IB of the matrix B
            NB = row_num[IB];
            //Iterate through the non-zero data elements on the IB rows of matrix B to achieve multiplication
            for (int n = 0; n < NB; n++) {
                IB = MB->data[PB + n].row;
                JB = MB->data[PB + n].col;
                EB = MB->data[PB + n].e;
                row_result[JB] += EA * EB;
            }
            /*
                The judgment condition that the matrix A is traversed in one row: (2 cases)
                    1.When the last one is nonzero element(p == this->tu - 1)
                    2.Other situations: Takes the non-zero element's row and determines if it is the same row as the current non-zero element. (this->data[p + 1].i != IA)
                Then the non-zero accumulation result of a row is assigned to the result matrix (sparse matrix), and the accumulator is initialized to 0
            */
            if (p == this->ele_sum - 1 || this->data[p + 1].row != IA)    //不用担心越界！
            {
                //Read and initialize the accumulator row_result[]
                for (int j = 0; j < MB->col_sum; j++) {
                    //Put the result of the accumulator not being 0 into a one-dimensional sparse matrix
                    if (row_result[j] != 0) {
                        MResult->data[MResult->ele_sum].row = IA;
                        MResult->data[MResult->ele_sum].col = j;
                        MResult->data[MResult->ele_sum].e = row_result[j];
                        MResult->ele_sum++;
                    }
                    //Initializing the accumulator row_result[] be 0
                    row_result[j] = 0;
                }
            }
        }
        return MResult;
    }
};


int main() {
    int a1[3][3] = {{1, 1, 1},
                    {2, 1, 1},
                    {1, 4, 5}};
    int a2[3][3] = {{1, 2, 3},
                    {1, 3, 1},
                    {3, 1, 5}};

    SMatrix *sm1 = new SMatrix((int **) a1, 3, 3);
    SMatrix *sm2 = new SMatrix((int **) a2, 3, 3);

    cout << "Matrix 1:" << endl;
    sm1->Matrixdisplay();
    cout << "Matrix 2:" << endl;
    sm2->Matrixdisplay();

    cout << "The result of adding matrix 1 and matrix 2:" << endl;
    SMatrix Result = (sm1->myAdd(*sm2));
    Result.Matrixdisplay();

    cout << "The transpose result of matrix 1:" << endl;
    SMatrix *sm1_t = sm1->MatrixTrans();
    sm1_t->Matrixdisplay();

    cout << "The result of multiplying matrix 1 and matrix 2:" << endl;
    SMatrix *multiResult = sm1->MultiMatrix(sm2);
    multiResult->Matrixdisplay();

    return 0;
}