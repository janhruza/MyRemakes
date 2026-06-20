#pragma once

#ifndef THREADPARAMS.H
#define THREADPARAMS_H

#include <wtypes.h>
#include "FocusSession.h"

typedef struct tagThreadParams {
    HWND hDlg;
    PFocusSession pSession;
} ThreadParams, * PThreadParams;

#endif