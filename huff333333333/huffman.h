#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct HeapNodeType
{
	unsigned char data; // 알파벳 
	unsigned int key; // 알파벳의 빈도수
	struct HeapNodeType* L_child; // 왼쪽 자식 노드 주소 저장
	struct HeapNodeType* R_child; // 오른쪽 자식 노드 주소 저장
}HeapNode;

typedef struct HeapType
{
	int MaxElementCount;		// 최대 노드 개수
	int currentElementCount;	// 현재 노드 개수
	HeapNode* Node;		// 노드 저장을 위한 1차원 배열
}MinHeap;

typedef struct CompressNumType
{
	unsigned char data[26]; // 알파벳
	unsigned int Length[26]; // 압축된 비트 길이
}CompressNum;

MinHeap* MaekHeap(int MaxElementCount);// 우선순위 큐로 사용할 힙 생성 함수
void RemoveHeap(MinHeap* Heap);// 생성한 힙의 메모리 해제함수
void InsertMinHeap(MinHeap* Heap, HeapNode element);// 힙에서의 추가 연산 함수
HeapNode* DeleteMinHeap(MinHeap* Heap);// 힙에서의 삭제 연산 함수
HeapNode* MakeNode(HeapNode* left, HeapNode* right);// 우선순위 큐에서 2개를 제거한 후 그것의 키 값을 합쳐 두 노드를 자식으로 가지는 부모 노드 생성 함수
void PrintHuffmanTree(HeapNode *p, int Depth, CompressNum* tmp, unsigned char *Code, int* k);// 데이터를 어떻게 압축할지 출력해주는 함수

#endif


