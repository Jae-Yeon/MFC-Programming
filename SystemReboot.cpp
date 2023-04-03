void SystemReboot()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// 토큰 프로세스 가져오기
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		return false;

	// shutdown privilege의 LUID 가져오기
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1; // one privilege to set 
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// 현재 process의 shutdown privilege 가져오기 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

	// 에러 났을 경우 처리
	if (GetLastError() != ERROR_SUCCESS);
	AfxMessageBox("AdjustTokenPrivileges");

	fResult = InitiateSystemShutdown
		(
		NULL,                 
		"System rebooting.",  // 유저 메세지
		0,                    // 리부팅 할 시간
		FALSE,               
		TRUE);                // 재부팅 옵션

	if (!fResult)
	{
		AfxMessageBox("InitiateSystemShutdown failed.");
	}
}
