// 레지스트리에서 프로그램 정보를 검색하는 소스코드
void FindProgramInRegedit()
{
	//CString refer = { "V3 Lite,아이피,Update Helper" };
	CString refer = { "SDK DirectX" };

	CString cutting[99] = { " ", }; //참조값 잘라서 담아줄 변수
	string temptemp[99] = { " ", };
	CString Substr;
	int tokenCounts = 0;
	while (AfxExtractSubString(Substr, refer, tokenCounts, ',')){
		cutting[tokenCounts] = Substr; //참조값 ','로 구분하여 저장
		cutting[tokenCounts] = cutting[tokenCounts].MakeLower(); // 비교를 위하여 소문자로 변경

		temptemp[tokenCounts] = CT2CA(cutting[tokenCounts]);

		tokenCounts++; //참조값의 수를 새어주기 위한 토큰
	}

	DWORD dwIndex = 0;
	LONG lRet;
	DWORD cbName = IS_KEY_LEN;
	TCHAR szSubKeyName[IS_KEY_LEN];
	HKEY hKey;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, // Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall 
		IS_KEY, 0, KEY_READ | KEY_WOW64_32KEY, &hKey) != ERROR_SUCCESS) {
	}
	while ((lRet = ::RegEnumKeyEx(hKey, dwIndex, szSubKeyName, &cbName, NULL,
		NULL, NULL, NULL)) != ERROR_NO_MORE_ITEMS){
		if (lRet == ERROR_SUCCESS)
		{
			HKEY hItem;
			if (::RegOpenKeyEx(hKey, szSubKeyName, 0, KEY_READ, &hItem) != ERROR_SUCCESS)
				continue;

			string name = RegistryQueryValue(hItem, _T("DisplayName")); //프로그램 명

			for (int i = 0; i < tokenCounts; i++){ //참조값의 개수만큼 반복
				int findRes = 0;
				std::transform(name.begin(), name.end(), name.begin(), asciitolower);// 프로그램명 소문자로 변경

				if (strstr(name.c_str(), cutting[i]) != NULL){
					//if (CheckSubstring(name.c_str(), temptemp[i])){
					m_wndList.AddString(name.c_str());
				}
			}
			::RegCloseKey(hItem);
		}
		dwIndex++;
		cbName = IS_KEY_LEN;
	}
	::RegCloseKey(hKey);

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, // 6432node
		IS_KEY, 0, KEY_READ | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS) {
	}
	while ((lRet = ::RegEnumKeyEx(hKey, dwIndex, szSubKeyName, &cbName, NULL,
		NULL, NULL, NULL)) != ERROR_NO_MORE_ITEMS){
		if (lRet == ERROR_SUCCESS)
		{
			HKEY hItem;
			if (::RegOpenKeyEx(hKey, szSubKeyName, 0, KEY_READ, &hItem) != ERROR_SUCCESS)
				continue;

			string name = RegistryQueryValue(hItem, _T("DisplayName")); //프로그램 명

			for (int i = 0; i < tokenCounts; i++){ //참조값의 개수만큼 반복
				int findRes = 0;
				std::transform(name.begin(), name.end(), name.begin(), asciitolower);// 프로그램명 소문자로 변경

				if (strstr(name.c_str(), cutting[i]) != NULL){
					//if (CheckSubstring(name.c_str(), temptemp[i])){
					m_wndList.AddString(name.c_str());
				}
			}
			::RegCloseKey(hItem);
		}
		dwIndex++;
		cbName = IS_KEY_LEN;
	}
	::RegCloseKey(hKey);
}
