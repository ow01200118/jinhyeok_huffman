#include "huffman.h"

MinHeap* MaekHeap(int MaxElementCount) 
{
	MinHeap *Return = NULL;
	int i = 0;

	if (MaxElementCount > 0)  // ������ ũ�� ���� 1 �̻��̾�� ���� ������ �� �ִ�
	{
		Return = (MinHeap *)malloc(sizeof(MinHeap)); // ���� ���� �� ������ ���� ����
		if (Return != NULL)
		{
			Return->MaxElementCount = MaxElementCount;
			Return->currentElementCount = 0;
			Return->Node = (HeapNode *)malloc(sizeof(HeapNode) * (MaxElementCount + 1)); // ������� �ϴ� ������ + 1 �� �Ͽ� ���� ũ�⸦ ������ش�.
			if (Return->Node == NULL)
			{
				printf("�޸� �Ҵ� ���� ( MakeHeap)\n");
				free(Return);
				return NULL;
			}

			memset(Return->Node, 0, sizeof(HeapNode) * (MaxElementCount + 1)); // �޸� �ʱ�ȭ�� ���ش�.
		}
		else
		{
			printf("�޸� �Ҵ� ���� ( MakeHeap)\n");
		}
	}
	else
	{
		printf("�ִ� ���� ������ 0���� Ŀ�� �մϴ�\n");
	}

	return Return; // ������ ���� ��ȯ�Ѵ�.
}

void InsertMinHeap(MinHeap* Heap, HeapNode element) 
{
	int i = 0;


	if (Heap != NULL)
	{
		if (Heap->currentElementCount == Heap->MaxElementCount) // ���� �������� ���̻� �߰��� �� ���� ���
		{
			printf("���� ����á���ϴ�.\n", Heap->MaxElementCount);
			return;
		}

		Heap->currentElementCount++; // ���� ��带 �߰� ���ֱ� ������ ���� ����� ���� + 1�� ���ش�.
		i = Heap->currentElementCount; // �߰��� ���� �켱 ���� ���� ������ ��忡 �߰��� �ȴ�.



		while ((i != 1) && (element.key < Heap->Node[i / 2].key)) // ����� Ű ���� �θ� ����� Ű ������ ���� ��� �����Ѵ�.
		{
			Heap->Node[i] = Heap->Node[i / 2]; // �ڽ� ���� �θ� ��� swap
			i /= 2;
		} // �߰��� ��尡 ���̻� �ö� �� ���������� �����Ѵ�.
		Heap->Node[i] = element;
	}
}

HeapNode* DeleteMinHeap(MinHeap* Heap) 
{
	HeapNode* Return = NULL; // ��ȯ�� ��尡 ����� ����
	HeapNode* Tmp = NULL;

	int i = 0;
	int parent = 0, child = 0;

	if (Heap != NULL && Heap->currentElementCount >  0)
	{
		Return = (HeapNode*)malloc(sizeof(HeapNode)); // Return ���� �޸� �Ҵ�
		if (Return == NULL)
		{
			printf("�޸� �Ҵ� ���� (DeleteMinHeap)\n");
			return NULL;
		}
		*Return = Heap->Node[1]; // ������ ������ �Ͽ��⿡ ��Ʈ ��� ��ȯ! ( �ּ������� ������ �߱� ������ ��Ʈ ����� Ű ���� ���� �۴�.)

		i = Heap->currentElementCount; // ���� ������ ��带 ����Ų��.
		Tmp = &(Heap->Node[i]); // ���� ������ ��带 Tmp ������ ����
		Heap->currentElementCount--; // ��Ʈ ��尡 ��ȯ�� ���̱� ������ ���� ���� ��� ���� ����

		parent = 1;
		child = 2;
		while (child <= Heap->currentElementCount) // ��Ʈ ��带 ���� �����ϰ� ����� Ű ���� ���Ͽ� �� �κ��� ä���ش�.
		{

			if ((child < Heap->currentElementCount) && Heap->Node[child].key > Heap->Node[child + 1].key) // ��Ʈ ��� �ؿ� �� �ڽ� ��尣�� ũ�⸦ ���Ѵ�. �� ���� ���� ��Ʈ ���� �ö󰡾� �ϱ� ������ chile++����.
			{
				child++;
			}
			if (Tmp->key <= Heap->Node[child].key) // ������ delete�� �ϸ� ���� �������� �ִ� ��尡 ��Ʈ ���� �ö󰡰� �ȴ�. �׷��� �� �ؿ� �� ���� ��尡 �ִٸ� swap ����� �Ѵ�. 
			{
				break;
			}

			Heap->Node[parent] = Heap->Node[child];
			parent = child;
			child *= 2;
		}// while���� ù���� ����� ���� ��Ʈ ��尡 �� ���� ������ �ִ��� ã�� ��Ʈ ��带 �����ϴ� �����̰�, �� ���� ���ʹ� ��Ʈ ���� ���ŵ� ����� �� �ڸ��� ä���ֱ� ���� �����̴�.
		Heap->Node[parent] = *Tmp; // �������� �ִ� ��尡 ��Ʈ ���� �ö� �� ���� �ڽ� ����� Ű ���� ���� �� ���ڸ��� ã�ư��� �����̴�.
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
	HeapNode *node = (HeapNode*)malloc(sizeof(HeapNode)); // ���� ���� �θ� ��� ���� ����

	if (node == NULL)
	{
		printf("�޸� �Ҵ� ����\n (MakeNode)");
		return 1;
	}

	node->L_child = left; // ���� �ڽ��� �ּҸ� ������ �ִ´�.
	node->R_child = right; // ������ �ڽ��� �ּҸ� ������ �ִ´�.
	node->data = 0x00; // ���� ������� ����̱� ������ data ���� 0x00���� �ʱ�ȭ �������.
	node->key = (left->key + right->key); // ������ �� ���� ���� �� �� ����� Ű ���� ���ļ� �θ� ��带 �����Ѵ�.

	return node;
}

void PrintHuffmanTree(HeapNode *p, int Depth, CompressNum* tmp, unsigned char *Code, int* Index) 
{

	int cnt = 0;


	if (p != NULL)
	{

		Depth++; // Depth + 1�� �Ѵ�. ������ �ؿ� ���ȣ�⿡�� Code = ' 0 ' �� ���� p->L_child ���� ���� ������ Depth�� �����Ѵ�.

		Code[Depth] = '0'; 
		PrintHuffmanTree(p->L_child, Depth, tmp, Code, Index);  // ���� �ڽ��� 0�� �ο� �޴´�.
		Code[Depth] = '1';
		PrintHuffmanTree(p->R_child, Depth, tmp, Code, Index); // ������ �ڽ��� 1�� �ο� �޴´�.
		
		// ���ȣ���� �̿��Ͽ� ������ Ʈ���� Ž���ϰ� data�� ���ڰ� ����ִ� ���� �ڽ� ������ ���� ������ data�� �ִ� ���鸸 ����� �ȴ�.
		Code[Depth] = '\0'; // ��¿����� �����Ⱚ�� �����ϱ� ���� �־��ش�.
		if (p->L_child == NULL && p->R_child == NULL)
		{
			printf("���ĺ� : %3c\t �󵵼� : %3d\t ����� bit : %s\n", p->data, p->key, Code);
			tmp->data[*Index] = p->data; //  ������� ���ϱ� ���� data���� �־��ش�.
			tmp->Length[*Index] = Depth; // Depth = bit length �̱� ������ ����� ���ϴµ� ����Ѵ�.
			*Index += 1;
		}

	}


}