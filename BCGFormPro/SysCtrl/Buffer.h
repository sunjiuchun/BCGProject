
/*---------------------------------------------------
�ļ���: Buffer.h
��  ;: ���ڴ�Ŵ��ڶ������ݵĶ��У����Ұ�����ƴ�ӳ����������ݰ�
��  ��: 2005.01.05
��  ��: 1.0
��  ��: �� ��
---------------------------------------------------*/

#if !defined(BUFFER_H)
#define BUFFER_H



#define ARRAY_SIZE		 2000	//2008.07.04����һ��Ҫ����

class CBuffer  
{
public:
	CBuffer();  
	virtual ~CBuffer();

	int		GetSize(void);
	bool	AddData(const  char *pBuffer,int iSize);
	bool	GetPackage(char *pArray,int iSize, char cStart, char cEnd);	
	void    ClearBuffer();
	bool	GetData( char *pBuffer,int iSize);

private:

	int		GetRemainSize(void);

	bool	CopyData( char *pBuffer,int iSize);
	void	AddHead(int iTotal);
	char	GetSiteData(int iSite);	
	int		GetBufferSize(void);
	char	m_Array[ARRAY_SIZE];
	int		m_iHead;
	int		m_iEnd;
};

#endif 
