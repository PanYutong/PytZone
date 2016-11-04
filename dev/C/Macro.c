//#include <bits/stdc++.h>
//using namespace std;
#include <stdio.h>

#define igt_main \
  static void igt_tokencat(__real_main, __LINE__)(void); \
  int main(int argc, char **argv) { \
  igt_subtest_init_parse_opts(&argc, argv, NULL, NULL, NULL, \
      NULL, NULL); \
  igt_tokencat(__real_main, __LINE__)(); \
  igt_exit(); \
  } \
  static void igt_tokencat(__real_main, __LINE__)(void) \

int main(int argc, char * argv[]) {
  int par1 = 1, par2 = 2;
  return 0;
}
