#pragma once
#ifndef SQQUEUE_H_INCLUDED
#define SQQUEUE_H_INCLUDED
#include "headers.h"

bool InitSqQueue(SqQueue& Q);
int SqQueueLength(SqQueue &Q);
bool EnSqQueue(SqQueue &Q, QElemType e);
bool DeSqQueue(SqQueue &Q, QElemType &e);
bool SqQueueFull(SqQueue Q);
bool SqQueueEmpty(SqQueue Q);
#endif // !SQQUEUE_H_INCLUDED
