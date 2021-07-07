/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include <iostream>

#include "CommonDataModel.h"
#include "algorithms/Algorithm.h"

int main(int argc, char* argv[])
{
  Algorithm algo;

  algo.addObject2().setBar_mL_per_s(5);
  algo.addObject2().setBar_mL_per_s(10);
  algo.addObject2().setBar_mL_per_s(25);

  algo.ComputeObject1();

  std::string json;
  algo.serializeToString(json, eSerializationFormat::JSON);
  std::cout << json << std::endl;
}