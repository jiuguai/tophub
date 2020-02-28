#include <stdio.h>

void maxSubSeq(int *arr, int N);
int maxSubSeq1(int *arr, int N);
int maxSubSeq2(int *arr, int l,int h);

int main(void){
    int k;
    int max;
    scanf("%d", &k);
    int arr[k];
    for (int i=0; i<k; i++){
        scanf("%d", &arr[i]);
    }
    maxSubSeq(arr, k);
    // max = maxSubSeq1(arr, k);
    // max = maxSubSeq2(arr, 0, k-1);
    
    return 0;
}



int maxSubSeq2(int *arr, int l,int h){
    
    
    if ( l == h){
        return arr[l];
    }
    int m = (l+h)/2;
    int maxSum, max, thisSum, lMaxSum=0, rMaxSum=0;
    int lmax = maxSubSeq2(arr, l, m);
    int rmax = maxSubSeq2(arr, m+1, h);
    thisSum = 0;

    for (int i=m; i>=l; i--){
        thisSum += arr[i];
        if (lMaxSum < thisSum){
            lMaxSum = thisSum;
        }
    }

    thisSum = 0;
    for (int i=m+1; i<=h; i++){
        thisSum += arr[i];
        if (rMaxSum < thisSum){
            rMaxSum = thisSum;
        }
    }

    maxSum = lMaxSum + rMaxSum;
    max = lmax > rmax ? lmax : rmax;
    maxSum = maxSum>max ? maxSum : max;


    return maxSum;
}

int maxSubSeq1(int *arr, int N){
    int thisSum, maxSum = 0;

    for (int i=0; i<N; i++){
        thisSum = 0;
        for (int j=i; j<N; j++){
            thisSum += arr[j];
            if (thisSum>maxSum){
                maxSum = thisSum;
            }
        }
    }

    return maxSum;
}


void maxSubSeq(int *arr, int N){
    int thisSum, maxSum;
    int start=0, end=N-1;
    thisSum = maxSum = 0;
    int flag = 1;
    for (int i=0; i<N; i++){
        if (arr[i] >= 0){
            flag = 0;
            break;
        }
    }
    if (flag == 1){
        printf("%d %d %d", maxSum, arr[start], arr[end]);
        return;
    }



    for (int i=0; i<N; i++){
        thisSum += arr[i];
        if (thisSum>maxSum){
            maxSum = thisSum;
            end = i;
        }else if(thisSum<0){
            thisSum = 0;
        }
    }
    if (maxSum != 0){
        thisSum = 0;
        for (int i=end; i>=0; i--){
            thisSum += arr[i];
            if (thisSum == maxSum){
                start = i;

            }
        }
        printf("%d %d %d", maxSum, arr[start], arr[end]);
    }else{

        printf("0 0 0");
    }
    

    

}
