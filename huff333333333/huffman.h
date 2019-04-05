#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct HeapNodeType
{
	unsigned char data; // ���ĺ� 
	unsigned int key; // ���ĺ��� �󵵼�
	struct HeapNodeType* L_child; // ���� �ڽ� ��� �ּ� ����
	struct HeapNodeType* R_child; // ������ �ڽ� ��� �ּ� ����
}HeapNode;

typedef struct HeapType
{
	int MaxElementCount;		// �ִ� ��� ����
	int currentElementCount;	// ���� ��� ����
	HeapNode* Node;		// ��� ������ ���� 1���� �迭
}MinHeap;

typedef struct CompressNumType
{
	unsigned char data[26]; // ���ĺ�
	unsigned int Length[26]; // ����� ��Ʈ ����
}CompressNum;

MinHeap* MaekHeap(int MaxElementCount);// �켱���� ť�� ����� �� ���� �Լ�
void RemoveHeap(MinHeap* Heap);// ������ ���� �޸� �����Լ�
void InsertMinHeap(MinHeap* Heap, HeapNode element);// �������� �߰� ���� �Լ�
HeapNode* DeleteMinHeap(MinHeap* Heap);// �������� ���� ���� �Լ�
HeapNode* MakeNode(HeapNode* left, HeapNode* right);// �켱���� ť���� 2���� ������ �� �װ��� Ű ���� ���� �� ��带 �ڽ����� ������ �θ� ��� ���� �Լ�
void PrintHuffmanTree(HeapNode *p, int Depth, CompressNum* tmp, unsigned char *Code, int* k);// �����͸� ��� �������� ������ִ� �Լ�

#endif


