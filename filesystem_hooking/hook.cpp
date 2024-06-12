


using namespace std;
#include <easyhook.h>
#include <iostream>
#include "Converter.h"
#include <fstream>
#include<iostream>
extern "C" void __declspec(dllexport) __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO * inRemoteInfo);

string GetStatus(long atr) {
	switch (atr)
	{
	case DELETE:
		return "Delete";
	case FILE_WRITE_DATA:
	case FILE_WRITE_ATTRIBUTES:
	case FILE_WRITE_EA:
	case FILE_APPEND_DATA:
	case WRITE_DAC:
	case WRITE_OWNER:
		return "Write";
	case FILE_READ_DATA:
	case FILE_READ_ATTRIBUTES:
	case FILE_READ_EA:
	case READ_CONTROL:
		return "Read";
	}
	return "null";
}
 
 
DWORD gFreqOffset = 0;
string path{};
ifstream ifile; struct stat info;
NTSTATUS NtCreateFileHook(
	PHANDLE FileHandle,
	ACCESS_MASK DesiredAccess,
	POBJECT_ATTRIBUTES ObjectAttributes,
	PIO_STATUS_BLOCK IoStatusBlock,
	PLARGE_INTEGER AllocationSize,
	ULONG FileAttributes,
	ULONG ShareAccess,
	ULONG CreateDisposition,
	ULONG CreateOptions,
	PVOID EaBuffer,
	ULONG EaLength
) {
	// \??\

	try
	{
		path = ConvertLPCWSTRToString((LPCWSTR)(ObjectAttributes->ObjectName->Buffer));

		cout << GetStatus(DesiredAccess) << ": " << path << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	 
	
	//MessageBox(GetActiveWindow(), (LPCWSTR)ObjectAttributes->ObjectName->Buffer,(LPCWSTR)L"Object Name", MB_OK);
	return NtCreateFile(FileHandle, DesiredAccess, ObjectAttributes, IoStatusBlock, AllocationSize, FileAttributes, ShareAccess,
		CreateDisposition, CreateOptions, EaBuffer, EaLength);
}



void __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* inRemoteInfo)
{
	 
	// Perform hooking
	HOOK_TRACE_INFO hHook = { NULL }; // keep track of our hook

	// Install the hook
	NTSTATUS result = LhInstallHook(
		GetProcAddress(GetModuleHandle(TEXT("ntdll")), "NtCreateFile"),
		NtCreateFileHook,
		NULL,
		&hHook);
	if (FAILED(result))
	{
		//cout << GetActiveWindow() << ": " << (LPCWSTR)RtlGetLastErrorString() << endl;
		MessageBox(GetActiveWindow(), (LPCWSTR)RtlGetLastErrorString(), (LPCWSTR)L"Failed to install hook", MB_OK);
	}

	// If the threadId in the ACL is set to 0,
	// then internally EasyHook uses GetCurrentThreadId()
	ULONG ACLEntries[1] = { 0 };

	// Disable the hook for the provided threadIds, enable for all others
	LhSetExclusiveACL(ACLEntries, 1, &hHook);

	return;
}