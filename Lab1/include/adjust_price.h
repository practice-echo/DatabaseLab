#ifndef ADJUST_PRICE_H
#define ADJUST_PRICE_H

#include "book.h"

/* 根据均价调整价格：低于均价涨20%，大于等于均价涨10% */
void AdjustPrices(LinkList head);

#endif