

class CFontFile
{
public:
	static short			readSHORT(CFile &infile);
	static unsigned short	readUSHORT(CFile &infile);
	static long				readLONG(CFile &infile);
	static unsigned long	readULONG(CFile &infile);
};