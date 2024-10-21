// CodeGear C++Builder
// Copyright (c) 1995, 2018 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DosCommand.pas' rev: 33.00 (Windows)

#ifndef DoscommandHPP
#define DoscommandHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>

//-- user supplied -----------------------------------------------------------

namespace Doscommand
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EDosCommand;
class DELPHICLASS ECreatePipeError;
class DELPHICLASS ECreateProcessError;
class DELPHICLASS EProcessTimer;
class DELPHICLASS TProcessTimer;
class DELPHICLASS TInputLines;
class DELPHICLASS TSyncString;
class DELPHICLASS TReadPipe;
class DELPHICLASS TDosThread;
class DELPHICLASS TDosCommand;
//-- type declarations -------------------------------------------------------
#pragma pack(push,4)
class PASCALIMPLEMENTATION EDosCommand : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline  EDosCommand(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline  EDosCommand(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline  EDosCommand(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline  EDosCommand(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline  EDosCommand(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline  EDosCommand(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline  EDosCommand(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline  EDosCommand(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline  EDosCommand(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline  EDosCommand(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline  EDosCommand(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline  EDosCommand(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline  virtual ~EDosCommand() { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION ECreatePipeError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline  ECreatePipeError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline  ECreatePipeError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline  ECreatePipeError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline  ECreatePipeError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline  ECreatePipeError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline  ECreatePipeError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline  ECreatePipeError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline  ECreatePipeError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline  ECreatePipeError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline  ECreatePipeError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline  ECreatePipeError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline  ECreatePipeError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline  virtual ~ECreatePipeError() { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION ECreateProcessError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline  ECreateProcessError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline  ECreateProcessError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline  ECreateProcessError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline  ECreateProcessError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline  ECreateProcessError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline  ECreateProcessError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline  ECreateProcessError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline  ECreateProcessError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline  ECreateProcessError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline  ECreateProcessError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline  ECreateProcessError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline  ECreateProcessError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline  virtual ~ECreateProcessError() { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION EProcessTimer : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline  EProcessTimer(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline  EProcessTimer(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline  EProcessTimer(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline  EProcessTimer(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline  EProcessTimer(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline  EProcessTimer(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline  EProcessTimer(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline  EProcessTimer(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline  EProcessTimer(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline  EProcessTimer(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline  EProcessTimer(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline  EProcessTimer(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline  virtual ~EProcessTimer() { }
	
};

#pragma pack(pop)

enum DECLSPEC_DENUM TOutputType : unsigned char { otEntireLine, otBeginningOfLine };

enum DECLSPEC_DENUM TEndStatus : unsigned char { esStop, esProcess, esStill_Active, esNone, esError, esTime };

typedef System::UnicodeString  (__closure *TCharDecoding)(System::TObject* ASender, System::Classes::TStream* ABuf);

typedef void  (__closure *TCharEncoding)(System::TObject* ASender, const System::UnicodeString AChars, System::Classes::TStream* AOutBuf);

#pragma pack(push,4)
class PASCALIMPLEMENTATION TProcessTimer : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Syncobjs::TCriticalSection* FCriticalSection;
	bool FEnabled;
	System::Syncobjs::TEvent* FEvent;
	int FID;
	int FSinceBeginning;
	int FSinceLastOutput;
	int  get_SinceBeginning();
	int  get_SinceLastOutput();
	void  set_Enabled(const bool AValue);
	
private:
	static System::Classes::TThreadList* FTimerInstances;
	void  MyTimer();
	
private:
	// __classmethod void  Create@();
	
public:
	 TProcessTimer();
	
private:
	// __classmethod void  Destroy@();
	
public:
	 virtual ~TProcessTimer();
	void  Beginning();
	void  Ending();
	void  NewOutput();
	__property bool Enabled = {read=FEnabled, write=set_Enabled, nodefault};
	__property System::Syncobjs::TEvent* Event = {read=FEvent};
	__property int SinceBeginning = {read=get_SinceBeginning, nodefault};
	__property int SinceLastOutput = {read=get_SinceLastOutput, nodefault};
};

#pragma pack(pop)

typedef void  (__closure *TNewLineEvent)(System::TObject* ASender, const System::UnicodeString ANewLine, TOutputType AOutputType);

typedef void  (__closure *TNewCharEvent)(System::TObject* ASender, System::WideChar ANewChar);

typedef void  (__closure *TErrorEvent)(System::TObject* ASender, System::Sysutils::Exception* AE, bool &AHandled);

typedef void  (__closure *TTerminateProcessEvent)(System::TObject* ASender, bool &ACanTerminate);

#pragma pack(push,4)
class PASCALIMPLEMENTATION TInputLines : public System::Sysutils::TSimpleRWSync
{
	typedef System::Sysutils::TSimpleRWSync inherited;
	
public:
	System::UnicodeString operator[](int AIndex) { return this->Strings[AIndex]; }
	
private:
	System::Syncobjs::TEvent* FEvent;
	System::Classes::TStrings* FList;
	System::UnicodeString  get_Strings(int AIndex);
	void  set_Strings(int AIndex, const System::UnicodeString AValue);
	
public:
	 TInputLines();
	 virtual ~TInputLines();
	int  Add(const System::UnicodeString AValue);
	int  Count();
	void  Delete(int AIndex);
	System::Classes::TStrings*  LockList();
	void  UnlockList();
	__property System::Syncobjs::TEvent* Event = {read=FEvent};
	__property System::UnicodeString Strings[int AIndex] = {read=get_Strings, write=set_Strings/*, default*/};
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TSyncString : public System::Sysutils::TSimpleRWSync
{
	typedef System::Sysutils::TSimpleRWSync inherited;
	
private:
	System::UnicodeString FValue;
	System::UnicodeString  get_Value();
	void  set_Value(const System::UnicodeString AValue);
	
public:
	void  Add(const System::UnicodeString AValue);
	void  Delete(int APos, int ACount);
	int  Length();
	__property System::UnicodeString Value = {read=get_Value, write=set_Value};
public:
	/* TSimpleRWSync.Create */ inline  TSyncString() : System::Sysutils::TSimpleRWSync() { }
	/* TSimpleRWSync.Destroy */ inline  virtual ~TSyncString() { }
	
};

#pragma pack(pop)

class PASCALIMPLEMENTATION TReadPipe : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	System::Syncobjs::TEvent* FEvent;
	TCharDecoding FOnCharDecoding;
	NativeUInt Fread_stdout;
	NativeUInt Fwrite_stdout;
	TSyncString* FSyncString;
	
protected:
	virtual void  Execute();
	
public:
	 TReadPipe(NativeUInt AReadStdout, NativeUInt AWriteStdout, TCharDecoding AOnCharDecoding);
	 virtual ~TReadPipe();
	HIDESBASE void  Terminate();
	__property System::Syncobjs::TEvent* Event = {read=FEvent};
	__property TSyncString* ReadString = {read=FSyncString};
};


class PASCALIMPLEMENTATION TDosThread : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	System::UnicodeString FCommandLine;
	System::UnicodeString FCurrentDir;
	System::Classes::TStringList* FEnvironment;
	TInputLines* FInputLines;
	bool FInputToOutput;
	System::Classes::TStringList* FLines;
	int FMaxTimeAfterBeginning;
	int FMaxTimeAfterLastOutput;
	TCharDecoding FOnCharDecoding;
	TCharEncoding FOnCharEncoding;
	TNewCharEvent FOnNewChar;
	TNewLineEvent FOnNewLine;
	TTerminateProcessEvent FOnTerminateProcess;
	System::Classes::TStrings* FOutputLines;
	TDosCommand* FOwner;
	int FPriority;
	_PROCESS_INFORMATION FProcessInformation;
	System::Syncobjs::TEvent* FTerminateEvent;
	TProcessTimer* FTimer;
	System::UnicodeString  DoCharDecoding(System::TObject* ASender, System::Classes::TStream* ABuf);
	void  DoEndStatus(TEndStatus AValue);
	void  DoLinesAdd(const System::UnicodeString AStr);
	void  DoNewChar(System::WideChar AChar);
	void  DoNewLine(const System::UnicodeString AStr, TOutputType AOutputType);
	void  DoReadLine(TSyncString* AReadString, System::UnicodeString &AStr, System::UnicodeString &ALast, bool &ALineBeginned);
	void  DoSendLine(NativeUInt AWritePipe, System::UnicodeString &ALast, bool &ALineBeginned);
	void  DoTerminateProcess();
	
private:
	unsigned FExitCode;
	
protected:
	bool FCanTerminate;
	virtual void  Execute();
	
public:
	 TDosThread(TDosCommand* AOwner, System::UnicodeString ACl, System::UnicodeString ACurrDir, System::Classes::TStringList* ALines, System::Classes::TStrings* AOl, TProcessTimer* ATimer, int AMtab, int AMtalo, TNewLineEvent AOnl, TNewCharEvent AOnc, System::Classes::TNotifyEvent Ot, TTerminateProcessEvent AOtp, int Ap, bool Aito, System::Classes::TStrings* AEnv, TCharDecoding AOnCharDecoding, TCharEncoding AOnCharEncoding);
	 virtual ~TDosThread();
	HIDESBASE void  Terminate();
	__property TInputLines* InputLines = {read=FInputLines};
};


class PASCALIMPLEMENTATION TDosCommand : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FCommandLine;
	System::UnicodeString FCurrentDir;
	System::Classes::TStrings* FEnvironment;
	unsigned FExitCode;
	bool FInputToOutput;
	System::Classes::TStringList* FLines;
	int FMaxTimeAfterBeginning;
	int FMaxTimeAfterLastOutput;
	TCharDecoding FOnCharDecoding;
	TCharEncoding FOnCharEncoding;
	TErrorEvent FonExecuteError;
	TNewCharEvent FOnNewChar;
	TNewLineEvent FOnNewLine;
	System::Classes::TNotifyEvent FOnTerminated;
	TTerminateProcessEvent FOnTerminateProcess;
	System::Classes::TStrings* FOutputLines;
	int FPriority;
	TDosThread* FThread;
	TProcessTimer* FTimer;
	TEndStatus  get_EndStatus();
	bool  get_IsRunning();
	void  set_CharDecoding(const TCharDecoding AValue);
	void  set_CharEncoding(const TCharEncoding AValue);
	
private:
	int FEndStatus;
	_PROCESS_INFORMATION FProcessInformation;
	
protected:
	virtual System::UnicodeString  DoCharDecoding(System::TObject* ASender, System::Classes::TStream* ABuf);
	virtual void  DoCharEncoding(System::TObject* ASender, const System::UnicodeString AChars, System::Classes::TStream* AOutBuf);
	void  ThreadTerminated(System::TObject* ASender);
	
public:
	 virtual TDosCommand(System::Classes::TComponent* AOwner);
	 virtual ~TDosCommand();
	void  Execute();
	void  SendLine(const System::UnicodeString AValue, bool AEol);
	void  Stop();
	__property TEndStatus EndStatus = {read=get_EndStatus, nodefault};
	__property unsigned ExitCode = {read=FExitCode, nodefault};
	__property bool IsRunning = {read=get_IsRunning, nodefault};
	__property System::Classes::TStringList* Lines = {read=FLines};
	__property System::Classes::TStrings* OutputLines = {read=FOutputLines, write=FOutputLines};
	__property int Priority = {read=FPriority, write=FPriority, nodefault};
	__property _PROCESS_INFORMATION ProcessInformation = {read=FProcessInformation};
	
__published:
	__property System::UnicodeString CommandLine = {read=FCommandLine, write=FCommandLine};
	__property System::UnicodeString CurrentDir = {read=FCurrentDir, write=FCurrentDir};
	__property System::Classes::TStrings* Environment = {read=FEnvironment};
	__property bool InputToOutput = {read=FInputToOutput, write=FInputToOutput, nodefault};
	__property int MaxTimeAfterBeginning = {read=FMaxTimeAfterBeginning, write=FMaxTimeAfterBeginning, nodefault};
	__property int MaxTimeAfterLastOutput = {read=FMaxTimeAfterLastOutput, write=FMaxTimeAfterLastOutput, nodefault};
	__property TCharDecoding OnCharDecoding = {read=FOnCharDecoding, write=set_CharDecoding};
	__property TCharEncoding OnCharEncoding = {read=FOnCharEncoding, write=set_CharEncoding};
	__property TErrorEvent OnExecuteError = {read=FonExecuteError, write=FonExecuteError};
	__property TNewCharEvent OnNewChar = {read=FOnNewChar, write=FOnNewChar};
	__property TNewLineEvent OnNewLine = {read=FOnNewLine, write=FOnNewLine};
	__property System::Classes::TNotifyEvent OnTerminated = {read=FOnTerminated, write=FOnTerminated};
	__property TTerminateProcessEvent OnTerminateProcess = {read=FOnTerminateProcess, write=FOnTerminateProcess};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Doscommand */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DOSCOMMAND)
using namespace Doscommand;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DoscommandHPP
