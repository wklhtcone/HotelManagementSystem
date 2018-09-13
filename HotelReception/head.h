#ifndef HEAD_H
#define HEAD_H

#include <ClientConnector.h>
#include "DataStruct.h"

using namespace std;

extern ClientConnector clientConnector;
extern  int roomNums[4];
extern  int roomPrices[4];

extern  vector<vector<string>> roomResult;
extern  vector<vector<string>> roomInfo;

#endif // HEAD_H
