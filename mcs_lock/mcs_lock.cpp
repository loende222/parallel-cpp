#include "mcs_lock.h"

thread_local MCSLock::Node MCSLock::node = {nullptr, false};
