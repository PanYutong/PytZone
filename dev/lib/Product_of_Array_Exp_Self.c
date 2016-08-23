//#include <bits/stdc++.h>
//using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* productExceptSelf(int* nums, int numsSize, int* returnSize) {

  int size = sizeof(int) * numsSize;
  returnSize = (int*)malloc(size);
  int i = 0;
  for (; i < numsSize; ++i) returnSize[i] = 1;

  i = 1;
  for (; i < numsSize; ++i) returnSize[i] = returnSize[i - 1] * nums[i - 1];

  int rtol = 1;

  i = numsSize - 1;
  for (; i >= 0; --i) {

    returnSize[i] *= rtol;

    rtol *= nums[i];

  }

  i = 0;
  for (; i < 4; ++i) printf("%d ", returnSize[i]);
  printf("\n");
  return returnSize;

}

int main(int argc, char * argv[]) {
  printf("pass\n");
  int* numbers;
  numbers = (int*)malloc(sizeof(int) * 4);
  numbers[1] = 2;
  numbers[2] = 2;
  numbers[3] = 2;
  numbers[0] = 2;
  int* rSize;
  int* result;
  result = productExceptSelf(numbers, 4, rSize);
  int i = 0;
  for (; i < 4; ++i) printf("%d ", result[i]);
  printf("\n");
  free(result);
  free(numbers);
  return 0;
}

