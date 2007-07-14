#ifndef _ECORE_EVAS_TEST_H
#define _ECORE_EVAS_TEST_H


#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Ecore.h"
#include "Ecore_Evas.h"

#define IM "efl/data/images/"
#define PT "efl/data/pointers/"
#define FN "efl/data/fonts/"

#ifdef __cplusplus
extern "C" {
#endif

extern double       start_time;
extern Ecore_Evas  *ee;
extern Evas        *evas;



void calibrate_pos_set(int pos);
int  calibrate_pos_get(void);
void calibrate_finish(void);
void calibrate_start(void);

void bg_resize(double w, double h);
void bg_start(void);
void bg_go(void);
    
int  app_start(int argc, const char **argv);
void app_finish(void);
#ifdef __cplusplus
}
#endif

#endif
