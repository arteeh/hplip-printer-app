// SPDX-License-Identifier: Apache-2.0
#include "hplip-plugin-verify.h"
int main(int argc, char **argv)
{
  if (argc != 6)
    return 2;
  return hplip_verify_plugin(argv[1], argv[2], argv[3], argv[4], argv[5]) ? 0 : 1;
}
