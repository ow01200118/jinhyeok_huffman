#include "huffman.h"

int main()
{

	int MaxHeapSize = 20; // ���� ũ�� ���� 
	int i = 0;
	int j = 0;
	int num = 0;
	unsigned int BitNum = 0; //  ����� ���ڿ��� bit ����
	unsigned int ByteNum = 0; // ���ڿ��� ����
	unsigned int tmp1 = 0;

	double CompNum = 0; // ����� ����
	unsigned char Code[100] = { 0x00, }; 
	unsigned char String[100] = { 0x00, }; // ���ڿ� ���� ����
	unsigned int Fre[26] = { 0x00, }; // �󵵼� ���� ����
	MinHeap *pHeap1 = NULL;
	HeapNode e[26];
	HeapNode *pNode = NULL;
	HeapNode *pNode1 = NULL;
	HeapNode *pNode2 = NULL;
	CompressNum* tmp = NULL;
	tmp = (CompressNum *)malloc(sizeof(CompressNum)); // ������� ���ϱ� ���� ������ ����ִ� ����ü ����
	int* k;

	k = (unsigned int *)malloc(sizeof(4)); // PrintfHuffman���� ����� ��Ʈ ���̸� �����ϴ� ����
	k[0] = 0;

	printf("���� ���ڿ��� �Է��ϼ���. : "); // ���ڿ� �Է� (���� �빮��)
	scanf("%s", String);
	fflush(stdin);

	while (String[i] != 0x00) // ���ڿ��� �󵵼� ����. 
	{
		Fre[String[i] - 'A']++; // 'A'�� ���⸦ �� ������ �迭 �ε����� 0��°���� A,B,C,D,...,Z���� ���ʴ�� �����ϱ� ���ؼ��̴�.
		i++;
	}

	for (i = 0; i < 26; i++) // Data(���ĺ�)�� �󵵼��� �����ϰ� �ִ� ��带 ����� �ش�.
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

	for (i = 0; i < j; i++) // ������� ����ϱ� ���� �Էµ� ���ڿ��� ���� ���
	{
		ByteNum += e[i].key;
	}


	pHeap1 = MaekHeap(MaxHeapSize); // �ּ� �� ����
	if (pHeap1 != NULL)
	{
		for (i = 0; i < j; i++)
		{
			InsertMinHeap(pHeap1, e[i]); // ������ ������� ������ �ּ� ���� ���� -> �󵵼��� key�� �Ͽ� �ּ� �� ����
		}

		num = pHeap1->currentElementCount; // ���� ����� ���� �ľ�
		for (i = 1; i < num; i++) 
		{
			pNode = DeleteMinHeap(pHeap1); // �ּ� ������ key���� ���� ���� ��� ��ȯ
			pNode1 = DeleteMinHeap(pHeap1); // �ּ� ������ 2��°�� key���� ���� ���� ��� ��ȯ

			pNode2 = MakeNode(pNode, pNode1); // key���� ���� 2���� ��带 �ڽ����� ������ �θ� ��� ����
			InsertMinHeap(pHeap1, *pNode2); // key���� ���� 2���� ��带 �ڽ����� ������ �θ� ��� ����
		}

		PrintHuffmanTree(pNode2, -1, tmp, Code, &k[0]); // huffman ����
		for (i = 0; i < *k; i++) // ����� ���
		{
			tmp1 = tmp->Length[i];
			BitNum += (Fre[tmp->data[i] - 'A'] * tmp1); // ����� ���ڿ��� ��Ʈ ��
		}
		CompNum = (double)(BitNum * 100) / (ByteNum * 8); 
		printf("����� : %2.2f\n", CompNum);




		RemoveHeap(pHeap1); // �ּ� �� �޸� ����
	}

	free(k);
	free(tmp);
	return 0;
}


