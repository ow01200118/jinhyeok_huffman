#include "huffman.h"

int main()
{

	int MaxHeapSize = 20; // 힙의 크기 변수 
	int i = 0;
	int j = 0;
	int num = 0;
	unsigned int BitNum = 0; //  압축된 문자열의 bit 길이
	unsigned int ByteNum = 0; // 문자열의 길이
	unsigned int tmp1 = 0;

	double CompNum = 0; // 압축률 변수
	unsigned char Code[100] = { 0x00, }; 
	unsigned char String[100] = { 0x00, }; // 문자열 저장 변수
	unsigned int Fre[26] = { 0x00, }; // 빈도수 저장 변수
	MinHeap *pHeap1 = NULL;
	HeapNode e[26];
	HeapNode *pNode = NULL;
	HeapNode *pNode1 = NULL;
	HeapNode *pNode2 = NULL;
	CompressNum* tmp = NULL;
	tmp = (CompressNum *)malloc(sizeof(CompressNum)); // 압축률을 구하기 위한 정보가 담겨있는 구조체 변수
	int* k;

	k = (unsigned int *)malloc(sizeof(4)); // PrintfHuffman에서 압축된 비트 길이를 저장하는 변수
	k[0] = 0;

	printf("보낼 문자열을 입력하세요. : "); // 문자열 입력 (영어 대문자)
	scanf("%s", String);
	fflush(stdin);

	while (String[i] != 0x00) // 문자열의 빈도수 저장. 
	{
		Fre[String[i] - 'A']++; // 'A'를 빼기를 한 이유는 배열 인덱스의 0번째부터 A,B,C,D,...,Z까지 차례대로 저장하기 위해서이다.
		i++;
	}

	for (i = 0; i < 26; i++) // Data(알파벳)와 빈도수를 저장하고 있는 노드를 만들어 준다.
	{
		if (Fre[i] != 0) 
		{
			e[j].key = Fre[i];
			e[j].data = (i + 65);
			e[j].L_child = NULL;
			e[j].R_child = NULL;
			j++;
		}
	}

	for (i = 0; i < j; i++) // 압축률을 계산하기 위해 입력된 문자열의 길이 계산
	{
		ByteNum += e[i].key;
	}


	pHeap1 = MaekHeap(MaxHeapSize); // 최소 힙 생성
	if (pHeap1 != NULL)
	{
		for (i = 0; i < j; i++)
		{
			InsertMinHeap(pHeap1, e[i]); // 위에서 만들어준 노드들을 최소 힙에 삽입 -> 빈도수를 key로 하여 최소 힙 정렬
		}

		num = pHeap1->currentElementCount; // 현재 노드의 개수 파악
		for (i = 1; i < num; i++) 
		{
			pNode = DeleteMinHeap(pHeap1); // 최소 힙에서 key값이 가장 작은 노드 반환
			pNode1 = DeleteMinHeap(pHeap1); // 최소 힙에서 2번째로 key값이 가장 작은 노드 반환

			pNode2 = MakeNode(pNode, pNode1); // key값이 작은 2개의 노드를 자식으로 가지는 부모 노드 생성
			InsertMinHeap(pHeap1, *pNode2); // key값이 작은 2개의 노드를 자식으로 가지는 부모 노드 삽입
		}

		PrintHuffmanTree(pNode2, -1, tmp, Code, &k[0]); // huffman 압축
		for (i = 0; i < *k; i++) // 압축률 계산
		{
			tmp1 = tmp->Length[i];
			BitNum += (Fre[tmp->data[i] - 'A'] * tmp1); // 압축된 문자열의 비트 수
		}
		CompNum = (double)(BitNum * 100) / (ByteNum * 8); 
		printf("압축률 : %2.2f\n", CompNum);




		RemoveHeap(pHeap1); // 최소 힙 메모리 해제
	}

	free(k);
	free(tmp);
	return 0;
}


