#include "list_workers.h"
#include <workers.h>

list_workers::list_workers()
{
    workrs = new std::list<workers>;
}

void add_worker(const workers& wrkr)
{
    workrs->push_back(wrkr);
}
