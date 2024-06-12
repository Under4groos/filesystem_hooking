 
 
#include <iostream>
 
 
 
#include <easyhook.h>
 
#include <winnt.h>
int main()
{
	DWORD processId;
	
	while (true)
	{
		std::wcout << "Enter the target process Id: ";
		std::cin >> processId;
		 
		wchar_t*  dllToInject = (wchar_t*)L"filesystem_hooking.dll";
		 
		wprintf(L"Attempting to inject: %s\n\n", dllToInject);
 

		NTSTATUS nt = RhInjectLibrary(
			processId,
			0,
			EASYHOOK_INJECT_DEFAULT,
			NULL,
			(LPWSTR) dllToInject,
			NULL,
			0
		);

		if (nt != 0)
		{
			printf("RhInjectLibrary failed with error code = %d\n", nt);
			PWCHAR err = RtlGetLastErrorString();
			std::wcout << err << "\n";
		}
		else
		{
			std::wcout << L"Library injected successfully.\n";
			break;
		}
	}

	std::wcout << "Press Enter to exit";
 
	return 0;
}
 