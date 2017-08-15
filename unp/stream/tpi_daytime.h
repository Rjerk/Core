#ifndef TPI_DAYTIME_H
#define TPI_DAYTIME_H

#include "stream.h"
#include "tihdr.h"
#include "unpxti.h"

void tpi_bind(int, const void*, size_t);
void tpi_connect(int, const void*, size_t);
ssize_t tpi_read(int, void*, size_t);
void tpi_close(int);

#define HAVE_DEV_TCP 1

#endif
