#ifndef _BRIDGEMAIN_H_
#define _BRIDGEMAIN_H_

#include <windows.h>

//default structure alignments forced
#ifdef _WIN64
#pragma pack(push, 16)
#else //x86
#pragma pack(push, 8)
#endif //_WIN64

#ifdef _WIN64
typedef unsigned long long duint;
typedef signed long long dsint;
#else
typedef unsigned long duint;
typedef signed long dsint;
#endif //_WIN64

#ifndef BRIDGE_IMPEXP
#ifdef BUILD_BRIDGE
#define BRIDGE_IMPEXP __declspec(dllexport)
#else
#define BRIDGE_IMPEXP __declspec(dllimport)
#endif //BUILD_BRIDGE
#endif //BRIDGE_IMPEXP

#ifdef __cplusplus
extern "C"
{
#endif

//Bridge defines
#define MAX_SETTING_SIZE 65536
#define DBG_VERSION 16

//Bridge functions
BRIDGE_IMPEXP const char* BridgeInit();
BRIDGE_IMPEXP const char* BridgeStart();
BRIDGE_IMPEXP void* BridgeAlloc(size_t size);
BRIDGE_IMPEXP void BridgeFree(void* ptr);
BRIDGE_IMPEXP bool BridgeSettingGet(const char* section, const char* key, char* value);
BRIDGE_IMPEXP bool BridgeSettingGetUint(const char* section, const char* key, duint* value);
BRIDGE_IMPEXP bool BridgeSettingSet(const char* section, const char* key, const char* value);
BRIDGE_IMPEXP bool BridgeSettingSetUint(const char* section, const char* key, duint value);

//Debugger defines
#define MAX_LABEL_SIZE 256
#define MAX_COMMENT_SIZE 512
#define MAX_MODULE_SIZE 256
#define MAX_BREAKPOINT_SIZE 256
#define MAX_SCRIPT_LINE_SIZE 2048

#define TYPE_VALUE 1
#define TYPE_MEMORY 2
#define TYPE_ADDR 4
#define MAX_MNEMONIC_SIZE 64

//Debugger enums
enum DBGSTATE
{
    initialized,
    paused,
    running,
    stopped
};

enum SEGMENTREG
{
    SEG_DEFAULT,
    SEG_ES,
    SEG_DS,
    SEG_FS,
    SEG_GS,
    SEG_CS,
    SEG_SS
};

enum ADDRINFOFLAGS
{
    flagmodule=1,
    flaglabel=2,
    flagcomment=4,
    flagbookmark=8,
    flagfunction=16
};

enum BPXTYPE
{
    bp_none=0,
    bp_normal=1,
    bp_hardware=2,
    bp_memory=4
};

enum FUNCTYPE
{
    FUNC_NONE,
    FUNC_BEGIN,
    FUNC_MIDDLE,
    FUNC_END,
    FUNC_SINGLE
};

enum LOOPTYPE
{
    LOOP_NONE,
    LOOP_BEGIN,
    LOOP_MIDDLE,
    LOOP_ENTRY,
    LOOP_END
};

enum DBGMSG
{
    DBG_SCRIPT_LOAD,                // param1=const char* filename,      param2=unused
    DBG_SCRIPT_UNLOAD,              // param1=unused,                    param2=unused
    DBG_SCRIPT_RUN,                 // param1=int destline,              param2=unused
    DBG_SCRIPT_STEP,                // param1=unused,                    param2=unused
    DBG_SCRIPT_BPTOGGLE,            // param1=int line,                  param2=unused
    DBG_SCRIPT_BPGET,               // param1=int line,                  param2=unused
    DBG_SCRIPT_CMDEXEC,             // param1=const char* command,       param2=unused
    DBG_SCRIPT_ABORT,               // param1=unused,                    param2=unused
    DBG_SCRIPT_GETLINETYPE,         // param1=int line,                  param2=unused
    DBG_SCRIPT_SETIP,               // param1=int line,                  param2=unused
    DBG_SCRIPT_GETBRANCHINFO,       // param1=int line,                  param2=SCRIPTBRANCH* info
    DBG_SYMBOL_ENUM,                // param1=SYMBOLCBINFO* cbInfo,      param2=unused
    DBG_ASSEMBLE_AT,                // param1=duint addr,                param2=const char* instruction
    DBG_MODBASE_FROM_NAME,          // param1=const char* modname,       param2=unused
    DBG_DISASM_AT,                  // param1=duint addr,				 param2=DISASM_INSTR* instr
    DBG_STACK_COMMENT_GET,          // param1=duint addr,                param2=STACK_COMMENT* comment
    DBG_GET_THREAD_LIST,            // param1=THREADALLINFO* list,       param2=unused
    DBG_SETTINGS_UPDATED,           // param1=unused,                    param2=unused
    DBG_DISASM_FAST_AT,             // param1=duint addr,                param2=BASIC_INSTRUCTION_INFO* basicinfo
    DBG_MENU_ENTRY_CLICKED          // param1=int hEntry,                param2=unused
};

enum SCRIPTLINETYPE
{
    linecommand,
    linebranch,
    linelabel,
    linecomment,
    lineempty,
};

enum SCRIPTBRANCHTYPE
{
    scriptnobranch,
    scriptjmp,
    scriptjnejnz,
    scriptjejz,
    scriptjbjl,
    scriptjajg,
    scriptjbejle,
    scriptjaejge,
    scriptcall
};

enum DISASM_INSTRTYPE
{
    instr_normal,
    instr_branch,
    instr_stack
};

enum DISASM_ARGTYPE
{
    arg_normal,
    arg_memory
};

enum STRING_TYPE
{
    str_none,
    str_ascii,
    str_unicode
};

enum THREADPRIORITY
{
    _PriorityIdle = -15,
    _PriorityAboveNormal = 1,
    _PriorityBelowNormal = -1,
    _PriorityHighest = 2,
    _PriorityLowest = -2,
    _PriorityNormal = 0,
    _PriorityTimeCritical = 15,
    _PriorityUnknown = 0x7FFFFFFF
};

enum THREADWAITREASON
{
    _Executive = 0,
    _FreePage = 1,
    _PageIn = 2,
    _PoolAllocation = 3,
    _DelayExecution = 4,
    _Suspended = 5,
    _UserRequest = 6,
    _WrExecutive = 7,
    _WrFreePage = 8,
    _WrPageIn = 9,
    _WrPoolAllocation = 10,
    _WrDelayExecution = 11,
    _WrSuspended = 12,
    _WrUserRequest = 13,
    _WrEventPair = 14,
    _WrQueue = 15,
    _WrLpcReceive = 16,
    _WrLpcReply = 17,
    _WrVirtualMemory = 18,
    _WrPageOut = 19,
    _WrRendezvous = 20,
    _Spare2 = 21,
    _Spare3 = 22,
    _Spare4 = 23,
    _Spare5 = 24,
    _WrCalloutStack = 25,
    _WrKernel = 26,
    _WrResource = 27,
    _WrPushLock = 28,
    _WrMutex = 29,
    _WrQuantumEnd = 30,
    _WrDispatchInt = 31,
    _WrPreempted = 32,
    _WrYieldExecution = 33,
    _WrFastMutex = 34,
    _WrGuardedMutex = 35,
    _WrRundown = 36,
};

enum MEMORY_SIZE
{
    size_byte,
    size_word,
    size_dword,
    size_qword
};

//Debugger typedefs
typedef MEMORY_SIZE VALUE_SIZE;
struct SYMBOLINFO;

typedef void (*CBSYMBOLENUM)(SYMBOLINFO* symbol, void* user);

//Debugger structs
struct MEMPAGE
{
    MEMORY_BASIC_INFORMATION mbi;
    char info[MAX_MODULE_SIZE];
};

struct MEMMAP
{
    int count;
    MEMPAGE* page;
};

struct BRIDGEBP
{
    BPXTYPE type;
    duint addr;
    bool enabled;
    bool singleshoot;
    bool active;
    char name[MAX_BREAKPOINT_SIZE];
    char mod[MAX_MODULE_SIZE];
    unsigned short slot;
};

struct BPMAP
{
    int count;
    BRIDGEBP* bp;
};

struct FUNCTION
{
    duint start;
    duint end;
};

struct ADDRINFO
{
    int flags; //ADDRINFOFLAGS
    char module[MAX_MODULE_SIZE]; //module the address is in
    char label[MAX_LABEL_SIZE];
    char comment[MAX_COMMENT_SIZE];
    bool isbookmark;
    FUNCTION function;
};

struct SYMBOLINFO
{
    duint addr;
    char* decoratedSymbol;
    char* undecoratedSymbol;
};

struct SYMBOLMODULEINFO
{
    duint base;
    char name[MAX_MODULE_SIZE];
};

struct SYMBOLCBINFO
{
    duint base;
    CBSYMBOLENUM cbSymbolEnum;
    void* user;
};

struct FLAGS
{
    bool c;
    bool p;
    bool a;
    bool z;
    bool s;
    bool t;
    bool i;
    bool d;
    bool o;
};

struct REGDUMP
{
    duint cax;
    duint ccx;
    duint cdx;
    duint cbx;
    duint csp;
    duint cbp;
    duint csi;
    duint cdi;
#ifdef _WIN64
    duint r8;
    duint r9;
    duint r10;
    duint r11;
    duint r12;
    duint r13;
    duint r14;
    duint r15;
#endif //_WIN64
    duint cip;
    unsigned int eflags;
    FLAGS flags;
    unsigned short gs;
    unsigned short fs;
    unsigned short es;
    unsigned short ds;
    unsigned short cs;
    unsigned short ss;
    duint dr0;
    duint dr1;
    duint dr2;
    duint dr3;
    duint dr6;
    duint dr7;
};

struct DISASM_ARG
{
    DISASM_ARGTYPE type;
    SEGMENTREG segment;
    char mnemonic[64];
    duint constant;
    duint value;
    duint memvalue;
};

struct DISASM_INSTR
{
    char instruction[64];
    DISASM_INSTRTYPE type;
    int argcount;
    int instr_size;
    DISASM_ARG arg[3];
};

struct STACK_COMMENT
{
    char color[8]; //hex color-code
    char comment[MAX_COMMENT_SIZE];
};

struct THREADINFO
{
    int ThreadNumber;
    HANDLE hThread;
    DWORD dwThreadId;
    duint ThreadStartAddress;
    duint ThreadLocalBase;
};

struct THREADALLINFO
{
    THREADINFO BasicInfo;
    duint ThreadCip;
    DWORD SuspendCount;
    THREADPRIORITY Priority;
    THREADWAITREASON WaitReason;
    DWORD LastError;
};

struct THREADLIST
{
    int count;
    THREADALLINFO* list;
    int CurrentThread;
};

struct MEMORY_INFO
{
    ULONG_PTR value; //displacement / addrvalue (rip-relative)
    MEMORY_SIZE size; //byte/word/dword/qword
    char mnemonic[MAX_MNEMONIC_SIZE];
};

struct VALUE_INFO
{
    ULONG_PTR value;
    VALUE_SIZE size;
};

struct BASIC_INSTRUCTION_INFO
{
    DWORD type; //value|memory|addr
    VALUE_INFO value; //immediat
    MEMORY_INFO memory;
    ULONG_PTR addr; //addrvalue (jumps + calls)
    bool branch; //jumps/calls
};

struct SCRIPTBRANCH
{
    SCRIPTBRANCHTYPE type;
    int dest;
    char branchlabel[256];
};

//Debugger functions
BRIDGE_IMPEXP const char* DbgInit();
BRIDGE_IMPEXP bool DbgMemRead(duint va, unsigned char* dest, duint size);
BRIDGE_IMPEXP bool DbgMemWrite(duint va, const unsigned char* src, duint size);
BRIDGE_IMPEXP duint DbgMemGetPageSize(duint base);
BRIDGE_IMPEXP duint DbgMemFindBaseAddr(duint addr, duint* size);
BRIDGE_IMPEXP bool DbgCmdExec(const char* cmd);
BRIDGE_IMPEXP bool DbgCmdExecDirect(const char* cmd);
BRIDGE_IMPEXP bool DbgMemMap(MEMMAP* memmap);
BRIDGE_IMPEXP bool DbgIsValidExpression(const char* expression);
BRIDGE_IMPEXP bool DbgIsDebugging();
BRIDGE_IMPEXP bool DbgIsJumpGoingToExecute(duint addr);
BRIDGE_IMPEXP bool DbgGetLabelAt(duint addr, SEGMENTREG segment, char* text);
BRIDGE_IMPEXP bool DbgSetLabelAt(duint addr, const char* text);
BRIDGE_IMPEXP bool DbgGetCommentAt(duint addr, char* text);
BRIDGE_IMPEXP bool DbgSetCommentAt(duint addr, const char* text);
BRIDGE_IMPEXP bool DbgGetBookmarkAt(duint addr);
BRIDGE_IMPEXP bool DbgSetBookmarkAt(duint addr, bool isbookmark);
BRIDGE_IMPEXP bool DbgGetModuleAt(duint addr, char* text);
BRIDGE_IMPEXP BPXTYPE DbgGetBpxTypeAt(duint addr);
BRIDGE_IMPEXP duint DbgValFromString(const char* string);
BRIDGE_IMPEXP bool DbgGetRegDump(REGDUMP* regdump);
BRIDGE_IMPEXP bool DbgValToString(const char* string, duint value);
BRIDGE_IMPEXP bool DbgMemIsValidReadPtr(duint addr);
BRIDGE_IMPEXP int DbgGetBpList(BPXTYPE type, BPMAP* list);
BRIDGE_IMPEXP FUNCTYPE DbgGetFunctionTypeAt(duint addr);
BRIDGE_IMPEXP LOOPTYPE DbgGetLoopTypeAt(duint addr, int depth);
BRIDGE_IMPEXP duint DbgGetBranchDestination(duint addr);
BRIDGE_IMPEXP bool DbgFunctionOverlaps(duint start, duint end);
BRIDGE_IMPEXP bool DbgFunctionGet(duint addr, duint* start, duint* end);
BRIDGE_IMPEXP void DbgScriptLoad(const char* filename);
BRIDGE_IMPEXP void DbgScriptUnload();
BRIDGE_IMPEXP void DbgScriptRun(int destline);
BRIDGE_IMPEXP void DbgScriptStep();
BRIDGE_IMPEXP bool DbgScriptBpToggle(int line);
BRIDGE_IMPEXP bool DbgScriptBpGet(int line);
BRIDGE_IMPEXP bool DbgScriptCmdExec(const char* command);
BRIDGE_IMPEXP void DbgScriptAbort();
BRIDGE_IMPEXP SCRIPTLINETYPE DbgScriptGetLineType(int line);
BRIDGE_IMPEXP void DbgScriptSetIp(int line);
BRIDGE_IMPEXP bool DbgScriptGetBranchInfo(int line, SCRIPTBRANCH* info);
BRIDGE_IMPEXP void DbgSymbolEnum(duint base, CBSYMBOLENUM cbSymbolEnum, void* user);
BRIDGE_IMPEXP bool DbgAssembleAt(duint addr, const char* instruction);
BRIDGE_IMPEXP duint DbgModBaseFromName(const char* name);
BRIDGE_IMPEXP void DbgDisasmAt(duint addr, DISASM_INSTR* instr);
BRIDGE_IMPEXP bool DbgStackCommentGet(duint addr, STACK_COMMENT* comment);
BRIDGE_IMPEXP void DbgGetThreadList(THREADLIST* list);
BRIDGE_IMPEXP void DbgSettingsUpdated();
BRIDGE_IMPEXP void DbgDisasmFastAt(duint addr, BASIC_INSTRUCTION_INFO* basicinfo);
BRIDGE_IMPEXP void DbgMenuEntryClicked(int hEntry);

//Gui defines
#define GUI_PLUGIN_MENU 0

#define GUI_DISASSEMBLY 0
#define GUI_DUMP 1
#define GUI_STACK 2

#define GUI_MAX_LINE_SIZE 65536

//Gui enums
enum GUIMSG
{
    GUI_DISASSEMBLE_AT,             // param1=(duint)va,            param2=(duint)cip
    GUI_SET_DEBUG_STATE,            // param1=(DBGSTATE)state,      param2=unused
    GUI_ADD_MSG_TO_LOG,             // param1=(const char*)msg,     param2=unused
    GUI_CLEAR_LOG,                  // param1=unused,               param2=unused
    GUI_UPDATE_REGISTER_VIEW,       // param1=unused,               param2=unused
    GUI_UPDATE_DISASSEMBLY_VIEW,    // param1=unused,               param2=unused
    GUI_UPDATE_BREAKPOINTS_VIEW,    // param1=unused,               param2=unused
    GUI_UPDATE_WINDOW_TITLE,        // param1=(const char*)file,    param2=unused
    GUI_GET_WINDOW_HANDLE,          // param1=unused,               param2=unused
    GUI_DUMP_AT,                    // param1=(duint)va             param2=unused
    GUI_SCRIPT_ADD,                 // param1=int count,            param2=const char** lines
    GUI_SCRIPT_CLEAR,               // param1=unused,               param2=unused
    GUI_SCRIPT_SETIP,               // param1=int line,             param2=unused
    GUI_SCRIPT_ERROR,               // param1=int line,             param2=const char* message
    GUI_SCRIPT_SETTITLE,            // param1=const char* title,    param2=unused
    GUI_SCRIPT_SETINFOLINE,         // param1=int line,             param2=const char* info
    GUI_SCRIPT_MESSAGE,             // param1=const char* message,  param2=unused
    GUI_SCRIPT_MSGYN,               // param1=const char* message,  param2=unused
    GUI_SYMBOL_LOG_ADD,             // param1(const char*)msg,      param2=unused
    GUI_SYMBOL_LOG_CLEAR,           // param1=unused,               param2=unused
    GUI_SYMBOL_SET_PROGRESS,        // param1=int percent           param2=unused
    GUI_SYMBOL_UPDATE_MODULE_LIST,  // param1=int count,            param2=SYMBOLMODULEINFO* modules
    GUI_REF_ADDCOLUMN,              // param1=int width,            param2=(const char*)title
    GUI_REF_SETROWCOUNT,            // param1=int rows,             param2=unused
    GUI_REF_GETROWCOUNT,            // param1=unused,               param2=unused
    GUI_REF_DELETEALLCOLUMNS,       // param1=unused,               param2=unused
    GUI_REF_SETCELLCONTENT,         // param1=(CELLINFO*)info,      param2=unused
    GUI_REF_GETCELLCONTENT,         // param1=int row,              param2=int col
    GUI_REF_RELOADDATA,             // param1=unused,               param2=unused
    GUI_REF_SETSINGLESELECTION,     // param1=int index,            param2=bool scroll
    GUI_REF_SETPROGRESS,            // param1=int progress,			param2=unused
    GUI_REF_SETSEARCHSTARTCOL,      // param1=int col               param2=unused
    GUI_STACK_DUMP_AT,              // param1=duint addr,           param2=duint csp
    GUI_UPDATE_DUMP_VIEW,           // param1=unused,               param2=unused
    GUI_UPDATE_THREAD_VIEW,         // param1=unused,               param2=unused
    GUI_ADD_RECENT_FILE,            // param1=(const char*)file,    param2=unused
    GUI_SET_LAST_EXCEPTION,         // param1=unsigned int code,    param2=unused
    GUI_GET_DISASSEMBLY,            // param1=duint addr,           param2=char* text
    GUI_MENU_ADD,                   // param1=int hMenu,            param2=const char* title
    GUI_MENU_ADD_ENTRY,             // param1=int hMenu,            param2=const char* title
    GUI_MENU_ADD_SEPARATOR,         // param1=int hMenu,            param2=unused
    GUI_MENU_CLEAR,                 // param1=int hMenu,            param2=unused
    GUI_SELECTION_GET,              // param1=int hWindow,          param2=SELECTIONDATA* selection
    GUI_SELECTION_SET,              // param1=int hWindow,          param2=const SELECTIONDATA* selection
    GUI_GETLINE_WINDOW              // param1=const char* title,    param2=char* text
};

//GUI structures
struct CELLINFO
{
    int row;
    int col;
    const char* str;
};

struct SELECTIONDATA
{
    duint start;
    duint end;
};

//GUI functions
BRIDGE_IMPEXP void GuiDisasmAt(duint addr, duint cip);
BRIDGE_IMPEXP void GuiSetDebugState(DBGSTATE state);
BRIDGE_IMPEXP void GuiAddLogMessage(const char* msg);
BRIDGE_IMPEXP void GuiLogClear();
BRIDGE_IMPEXP void GuiUpdateAllViews();
BRIDGE_IMPEXP void GuiUpdateRegisterView();
BRIDGE_IMPEXP void GuiUpdateDisassemblyView();
BRIDGE_IMPEXP void GuiUpdateBreakpointsView();
BRIDGE_IMPEXP void GuiUpdateWindowTitle(const char* filename);
BRIDGE_IMPEXP HWND GuiGetWindowHandle();
BRIDGE_IMPEXP void GuiDumpAt(duint va);
BRIDGE_IMPEXP void GuiScriptAdd(int count, const char** lines);
BRIDGE_IMPEXP void GuiScriptClear();
BRIDGE_IMPEXP void GuiScriptSetIp(int line);
BRIDGE_IMPEXP void GuiScriptError(int line, const char* message);
BRIDGE_IMPEXP void GuiScriptSetTitle(const char* title);
BRIDGE_IMPEXP void GuiScriptSetInfoLine(int line, const char* info);
BRIDGE_IMPEXP void GuiScriptMessage(const char* message);
BRIDGE_IMPEXP int GuiScriptMsgyn(const char* message);
BRIDGE_IMPEXP void GuiSymbolLogAdd(const char* message);
BRIDGE_IMPEXP void GuiSymbolLogClear();
BRIDGE_IMPEXP void GuiSymbolSetProgress(int percent);
BRIDGE_IMPEXP void GuiSymbolUpdateModuleList(int count, SYMBOLMODULEINFO* modules);
BRIDGE_IMPEXP void GuiReferenceAddColumn(int width, const char* title);
BRIDGE_IMPEXP void GuiReferenceSetRowCount(int count);
BRIDGE_IMPEXP int GuiReferenceGetRowCount();
BRIDGE_IMPEXP void GuiReferenceDeleteAllColumns();
BRIDGE_IMPEXP void GuiReferenceSetCellContent(int row, int col, const char* str);
BRIDGE_IMPEXP const char* GuiReferenceGetCellContent(int row, int col);
BRIDGE_IMPEXP void GuiReferenceReloadData();
BRIDGE_IMPEXP void GuiReferenceSetSingleSelection(int index, bool scroll);
BRIDGE_IMPEXP void GuiReferenceSetProgress(int progress);
BRIDGE_IMPEXP void GuiReferenceSetSearchStartCol(int col);
BRIDGE_IMPEXP void GuiStackDumpAt(duint addr, duint csp);
BRIDGE_IMPEXP void GuiUpdateDumpView();
BRIDGE_IMPEXP void GuiUpdateThreadView();
BRIDGE_IMPEXP void GuiAddRecentFile(const char* file);
BRIDGE_IMPEXP void GuiSetLastException(unsigned int exception);
BRIDGE_IMPEXP bool GuiGetDisassembly(duint addr, char* text);
BRIDGE_IMPEXP int GuiMenuAdd(int hMenu, const char* title);
BRIDGE_IMPEXP int GuiMenuAddEntry(int hMenu, const char* title);
BRIDGE_IMPEXP void GuiMenuAddSeparator(int hMenu);
BRIDGE_IMPEXP void GuiMenuClear(int hMenu);
BRIDGE_IMPEXP bool GuiSelectionGet(int hWindow, SELECTIONDATA* selection);
BRIDGE_IMPEXP bool GuiSelectionSet(int hWindow, const SELECTIONDATA* selection);
BRIDGE_IMPEXP bool GuiGetLineWindow(const char* title, char* text);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif // _BRIDGEMAIN_H_
