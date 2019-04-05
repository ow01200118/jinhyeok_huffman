#include "huffman.h"

MinHeap* MaekHeap(int MaxElementCount) 
{
	MinHeap *Return = NULL;
	int i = 0;

	if (MaxElementCount > 0)  // 생성할 크기 값이 1 이상이어야 힙을 생성할 수 있다
	{
		Return = (MinHeap *)malloc(sizeof(MinHeap)); // 힙을 생성 후 저장할 변수 선언
		if (Return != NULL)
		{
			Return->MaxElementCount = MaxElementCount;
			Return->currentElementCount = 0;
			Return->Node = (HeapNode *)malloc(sizeof(HeapNode) * (MaxElementCount + 1)); // 만들고자 하는 개수에 + 1 을 하여 힙의 크기를 만들어준다.
			if (Return->Node == NULL)
			{
				printf("메모리 할당 오류 ( MakeHeap)\n");
				free(Return);
				return NULL;
			}

			memset(Return->Node, 0, sizeof(HeapNode) * (MaxElementCount + 1)); // 메모리 초기화를 해준다.
		}
		else
		{
			printf("메모리 할당 오류 ( MakeHeap)\n");
		}
	}
	else
	{
		printf("최대 원소 개수는 0보다 커야 합니다\n");
	}

	return Return; // 생성한 힙을 반환한다.
}

void InsertMinHeap(MinHeap* Heap, HeapNode element) 
{
	int i = 0;


	if (Heap != NULL)
	{
		if (Heap->currentElementCount == Heap->MaxElementCount) // 힙이 가득차서 더이상 추가할 수 없을 경우
		{
			printf("힙이 가득찼습니다.\n", Heap->MaxElementCount);
			return;
		}

		Heap->currentElementCount++; // 힙에 노드를 추가 해주기 때문에 현재 노드의 개수 + 1을 해준다.
		i = Heap->currentElementCount; // 추가된 노드는 우선 힙에 제일 마지막 노드에 추가가 된다.



		while ((i != 1) && (element.key < Heap->Node[i / 2].key)) // 노드의 키 값이 부모 노드의 키 값보다 작을 경우 실행한다.
		{
			Heap->Node[i] = Heap->Node[i / 2]; // 자식 노드와 부모 노드 swap
			i /= 2;
		} // 추가된 노드가 더이상 올라갈 수 없을때까지 실행한다.
		Heap->Node[i] = element;
	}
}

HeapNode* DeleteMinHeap(MinHeap* Heap) 
{
	HeapNode* Return = NULL; // 반환될 노드가 저장될 변수
	HeapNode* Tmp = NULL;

	int i = 0;
	int parent = 0, child = 0;

	if (Heap != NULL && Heap->currentElementCount >  0)
	{
		Return = (HeapNode*)malloc(sizeof(HeapNode)); // Return 변수 메모리 할당
		if (Return == NULL)
		{
			printf("메모리 할당 오류 (DeleteMinHeap)\n");
			return NULL;
		}
		*Return = Heap->Node[1]; // 힙으로 구현을 하였기에 루트 노드 반환! ( 최소힙으로 구현을 했기 때문에 루트 노드의 키 값이 제일 작다.)

		i = Heap->currentElementCount; // 힙에 마지막 노드를 가리킨다.
		Tmp = &(Heap->Node[i]); // 힙에 마지막 노드를 Tmp 변수에 저장
		Heap->currentElementCount--; // 루트 노드가 반환될 것이기 때문에 힙의 현재 노드 개수 감소

		parent = 1;
		child = 2;
		while (child <= Heap->currentElementCount) // 루트 노드를 새로 갱신하고 노드의 키 값을 비교하여 빈 부분을 채워준다.
		{

			if ((child < Heap->currentElementCount) && Heap->Node[child].key > Heap->Node[child + 1].key) // 루트 노드 밑에 두 자식 노드간의 크기를 비교한다. 더 작은 값이 루트 노드로 올라가야 하기 때문에 chile++실행.
			{
				child++;
			}
			if (Tmp->key <= Heap->Node[child].key) // 힙에서 delete를 하면 제일 마지막에 있는 노드가 루트 노드로 올라가게 된다. 그래서 그 밑에 더 작은 노드가 있다면 swap 해줘야 한다. 
			{
				break;
			}

			Heap->Node[parent] = Heap->Node[child];
			parent = child;
			child *= 2;
		}// while문이 첫번쨰 실행될 때는 루트 노드가 될 만한 값들을 있는지 찾고 루트 노드를 갱신하는 과정이고, 그 다음 부터는 루트 노드로 갱신된 노드의 빈 자리를 채워주기 위한 과정이다.
		Heap->Node[parent] = *Tmp; // 마지막에 있는 노드가 루트 노드로 올라간 후 밑의 자식 노드들과 키 값을 비교한 후 제자리를 찾아가는 과정이다.
	}

	return Return;
}

void RemoveHeap(MinHeap* Heap) 
{
	if (Heap != NULL)
	{
		if (Heap->Node != NULL)
		{
			free(Heap->Node);
		}
		free(Heap);
	}
}


HeapNode* MakeNode(HeapNode* left, HeapNode* right) 
{
	HeapNode *node = (HeapNode*)malloc(sizeof(HeapNode)); // 새로 만들 부모 노드 변수 선언

	if (node == NULL)
	{
		printf("메모리 할당 에러\n (MakeNode)");
		return 1;
	}

	node->L_child = left; // 왼쪽 자식의 주소를 가지고 있는다.
	node->R_child = right; // 오른쪽 자식의 주소를 가지고 있는다.
	node->data = 0x00; // 새로 만들어진 노드이기 때문에 data 값을 0x00으로 초기화 시켜줬다.
	node->key = (left->key + right->key); // 작은것 두 값을 빼고 그 두 노드의 키 값을 합쳐서 부모 노드를 생성한다.

	return node;
}

void PrintHuffmanTree(HeapNode *p, int Depth, CompressNum* tmp, unsigned char *Code, int* Index) 
{

	int cnt = 0;


	if (p != NULL)
	{

		Depth++; // Depth + 1을 한다. 이유는 밑에 재귀호출에서 Code = ' 0 ' 이 들어가고 p->L_child 값이 들어가기 때문에 Depth가 증가한다.

		Code[Depth] = '0'; 
		PrintHuffmanTree(p->L_child, Depth, tmp, Code, Index);  // 왼쪽 자식은 0을 부여 받는다.
		Code[Depth] = '1';
		PrintHuffmanTree(p->R_child, Depth, tmp, Code, Index); // 오른쪽 자식은 1을 부여 받는다.
		
		// 재귀호출을 이용하여 허프만 트리를 탐색하고 data에 문자가 들어있는 노드는 자식 노드들이 없기 때문에 data가 있는 노드들만 출력이 된다.
		Code[Depth] = '\0'; // 출력에서의 쓰레기값을 제거하기 위해 넣어준다.
		if (p->L_child == NULL && p->R_child == NULL)
		{
			printf("알파벳 : %3c\t 빈도수 : %3d\t 압축된 bit : %s\n", p->data, p->key, Code);
			tmp->data[*Index] = p->data; //  압축률을 구하기 위해 data값을 넣어준다.
			tmp->Length[*Index] = Depth; // Depth = bit length 이기 때문에 압축률 구하는데 사용한다.
			*Index += 1;
		}

	}


}