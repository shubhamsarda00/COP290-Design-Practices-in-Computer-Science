/*
 * libaudio.h
 *
 *  Created on: 27-Feb-2022
 *      Author: shubham
 */

#ifndef TASK3_LIBAUDIO_H_
#define TASK3_LIBAUDIO_H_
using namespace std;

typedef struct{
    int label;
    float prob;
}pred_t;

extern pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred);



#endif /* TASK3_LIBAUDIO_H_ */
