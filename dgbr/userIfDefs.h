/**************************************************************************
*
*   Copyright:      TE Connectivity
*   Module:
*   Filename:       userIfDefs.h
*   Author:
*   Created:
*   Description:    Data structures
*
*
**************************************************************************/

#ifndef __USERIF_H__
#define __USERIF_H__

#define MAXNUM_USER_FUNC        50
#define MAXNUM_USER_VAR         50
#define USERIF_NAME_SIZE        50
#define USERIF_NUM_PARAMS       5
#define USERIF_HELP_SIZE        128

#define IPC_USERIF_RUN_FUNC     0xFF00
#define IPC_USERIF_SET_VAR      0xFF01

typedef struct
{
    char name[USERIF_NAME_SIZE];
    int (*pFunc)();
    char help[USERIF_HELP_SIZE];
} func_t;

typedef struct
{
    char name[USERIF_NAME_SIZE];
    int *pVar;
    char help[USERIF_HELP_SIZE];
} var_t;

typedef struct
{
    //ipc_hdr_t hdr;
    //char name[USERIF_NAME_SIZE];
    char *name;
    int param[USERIF_NUM_PARAMS];
    int numParams;
    char stdoutDev[USERIF_NAME_SIZE];
} UserifMsg_t;

extern int userifRegisterVar(char *name, int *pVar, char *help);
extern int userifRegisterFunc(char *name, int (*pFunc)(), char *help);

#endif
