bool KillProcessByName(CString ImageName)
{
	bool	result;
	HANDLE	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // 프로세스 정보 가져오기

	if (hSnap == INVALID_HANDLE_VALUE)
		hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 PE32 = {0};
	PE32.dwSize = sizeof(PROCESSENTRY32);

	result = false;
	if (Process32First(hSnap, &PE32)) // SnapShot에 들어 있는 첫번째 프로세스를 받아오기
	{
		sImageName.MakeUpper();
		do
		{
			// 윈도우 2000 미만 처리
			_tcsupr_s(PE32.szExeFile, MAX_PATH);
			if (_tcsstr(PE32.szExeFile, sImageName) != NULL)
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PE32.th32ProcessID);
				if (!hProcess)
				{
					hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, PE32.th32ProcessID);
				}

				if (hProcess)
				{
					if (PID == 0 || PE32.th32ProcessID == PID) // 프로세스 이름이 내가 원하는 어플리케이션인지 확인
					{											
						TerminateProcess(hProcess, 0);						
						WaitForSingleObject(hProcess, 5000);						
						result = true;
					}
					CloseHandle(hProcess);
				}
			}

		}	while (Process32Next(hSnap, &PE32)); // 다음 프로세스 스냅샷에서 받아오기

		CloseHandle(hSnap);
	}

	return result;
}
