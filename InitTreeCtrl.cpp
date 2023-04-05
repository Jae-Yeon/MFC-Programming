// 윈도우 파일 탐색기의 폴더 구조를 구현하기 위한 함수

void InitTreeCtrl()
{
	// 1.1 C드라이브의 폴더목록을 TreeView에 보여준다.
	HTREEITEM hItem = m_Tree.InsertItem(_T("C:", hItem));

	//  1.1.1 CFileFind를 이용하여 "C:\\*.*"의 파일 또는 폴더를 찾는다.
	CFileFind finder;
	BOOL bWorking = finder.FindFile(_T("C:\\*.*"));
	//  1.1.2 C드라이브의 모든 파일을 하나씩 검사하면서 폴더만 Tree의 아이템으로 삽입한다.
	while (bWorking) {
		//   1.1.2.1 "C:\\*.*"의 NextFile(C드라이브의 첫번째)부터 아래 검사를 시작한다.
		bWorking = finder.FindNextFile();
		//   1.1.2.2 현재 검사하고 있는 것이 Directory일 경우만 Tree의 아이템으로 삽입한다.
		if (finder.IsDirectory()) {
			m_Tree.InsertItem(finder.GetFileName(), hItem);
		}
	}
	//  1.1.3 삽입한 모든 트리아이템을 보이도록 한다.
	m_Tree.EnsureVisible(hItem);
}
