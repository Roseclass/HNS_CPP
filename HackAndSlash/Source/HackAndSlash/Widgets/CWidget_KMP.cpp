#include "CWidget_KMP.h"
#include "Global.h"

bool UCWidget_KMP::Check(FString KMP, FString Str)
{
	int32 KMPlen = KMP.Len();
	int32 Strlen = Str.Len();
	int32 dis = 0,//건너뛸인덱스양
		index = 0,//시작점
		count = 0;//일치하는양
	while (true)
	{
		index = 0;
		if ((index + dis) + KMPlen > Strlen)
			break;
		while (Str[index+dis]==KMP[count])
		{
			count++;
			index++;
			if (count==KMPlen)
				return true;
		}
		dis += count - table[count];
		count = 0;
	}
	return false;
}

void UCWidget_KMP::MakeKMPArray(FString KMP)
{	
	table.SetNum(KMP.Len()+1);
	table[0] = -1;
	for (int32 i = 1; i <= KMP.Len(); i++)
		table[i] = 0;
	int32 index=0;
	for (int32 i = 1; i < KMP.Len(); i++)
	{
		while (KMP[index]!=KMP[i]&&index>0)
		{
			index = table[index];
		}
		if (KMP[index] == KMP[i])
			table[i + 1] = ++index;
	}
}