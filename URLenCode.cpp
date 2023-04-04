CString URLenCode(CString str)
{
	CString ret;
	char *encstr, buf[2 + 1];
	unsigned char c;
	int i, j;

	if (str.IsEmpty())
	{
		return NULL;
	}
	if ((encstr = (char *)malloc((strlen(str) * 3) + 1)) == NULL)
		return NULL;
	
	for (i = j = 0; str[i]; i++)
	{
		c = (unsigned char)str[i];
		if ((c >= '0') && (c <= '9')) encstr[j++] = c;
		else if ((c >= 'A') && (c <= 'Z')) encstr[j++] = c;
		else if ((c >= 'a') && (c <= 'z')) encstr[j++] = c;
		else if ((c == '@') || (c == '.') || (c == '/') || (c == '\\')
			|| (c == '-') || (c == '_') || (c == ':') || (c=='!'))
			encstr[j++] = c;
		else
		{
			sprintf(buf, "%02x", c);
			encstr[j++] = '%';
			encstr[j++] = buf[0];
			encstr[j++] = buf[1];
		}
	}
	encstr[j] = NULL;
	ret.Format("%s", encstr);
	free(encstr);

	return ret;
}
