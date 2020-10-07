#include <stdio.h>
#include <stdlib.h>

int menu(void);
int* add(int* graph, char** titles, int* count);// добавляет ветви в граф
void show(int* graph, char* titles, int count);// визуализирует граф в формате png
int is_relate(int* graph, char* titles, int count);// проверяет граф на связность

int main(void)
{
	int flag = menu();
	int count = 0;
	int* graph = NULL;
	char* titles = NULL;
	int res;
	while (flag)
	{
		switch(flag)
		{
			case 1: graph = add(graph, &titles, &count); flag = menu(); break;
			case 2: show(graph, titles, count); flag = menu(); break;
			case 3: 
			res = is_relate(graph, titles, count);
			if (res == 1)
				printf("relateed graph\n");
			else 
				printf("unreleated graph\n");
			flag = menu();
			break;
			default: printf("Don't know such command\n"); flag = menu();
		}
	}
	free(graph);
	free(titles);
	return 0;
}

int titles_from_input(char* c1, char* c2);// возвращает две введённые пользователем буквы
int search(char* arr, int i, char c);// ищет индекс буквы в массиве titels
int* copy(int size_new, int* old, int size_old);// создаёт двумерный массив size_new * size_new копирует значения из старого массива
// void list(int* arr, int i); // выводит двумерный массив


int* add(int* graph, char** titles, int* count)
{
	printf("Use such format \"a--c\"\n");
	char c1, c2;
	int num_c1, num_c2;
	int size = *count, flag = titles_from_input(&c1, &c2);
	while(flag)
	{
		if (flag == -1)
		{
			flag = titles_from_input(&c1, &c2);
			continue;
		}
		if (flag == -2)
		{
			num_c1 = search(*titles, size, c1);
			if (num_c1 == 0)
			{
				size += 1;
				*titles = (char*) realloc(*titles, size * sizeof(int));
				if (titles == NULL)
					exit(200);
				*(*titles + size - 1) = c1;
				graph = copy(size, graph, size - 1);				
			} else
			{
				flag = titles_from_input(&c1, &c2);
				continue;
			}
		} else
		{
			num_c1 = search(*titles, size, c1);
			num_c2 = search(*titles, size, c2);
			if (num_c1 != 0)
			{
				if (num_c2 != 0)
				{
					*(graph + (num_c1 - 1) * size + num_c2 - 1) = 1;// для с1
					*(graph + (num_c2 - 1) * size + num_c1 - 1) = 1;
				}else
				{
					
					size += 1;
					*titles = (char*) realloc(*titles, size * sizeof(int));
					if (titles == NULL)
						exit(200);
					*(*titles + size - 1) = c2;
					graph = copy(size, graph, size - 1);
					*(graph + (num_c1 - 1) * size + size - 1) = 1;// для с1
					*(graph + (size - 1) * size + num_c1 - 1) = 1;
				}

			} else if (num_c2 != 0)
			{
				size += 1;
				*titles = (char*) realloc(*titles, size * sizeof(int));
				if (titles == NULL)
					exit(200);
				*(*titles + size - 1) = c1;
				graph = copy(size, graph, size - 1);
				*(graph + (num_c2 - 1) * size + size - 1) = 1;// для с1
				*(graph + (size - 1) * size + num_c2 - 1) = 1;
			} else
			{
				size += 2;
				*titles = (char*) realloc(*titles, size * sizeof(int));
				if (titles == NULL)
					exit(200);
				*(*titles + size - 2) = c1;
				*(*titles + size - 1) = c2;
				if ((size - 2) == 0)
				{
					graph = (int*) realloc(graph, size * size * sizeof(int));
					if (graph == NULL)
						exit(200);
					*(graph + (size - 2) * size + size - 1) = 1;// для с1
					*(graph + (size - 1) * size + size - 2) = 1;
				}else
				{
					graph = copy(size, graph, size - 2);
					*(graph + (size - 2) * size + size - 1) = 1;// для с1
					*(graph + (size - 1) * size + size - 2) = 1;
				}
			}
		}
		// list(graph, size);
		flag = titles_from_input(&c1, &c2);
	}
	*count = size;
	return graph;
}


int titles_from_input(char* c1, char* c2)// вовращает две ведёные буквы - названия ячеек
{
	char str[5];
	int i = 0;
	for (i; i < 5 && ((str[i] = getchar()) != '\n') && (str[i] != EOF); ++i)
		;
	if (str[i] == EOF)
		return 0;// 0 чтобы выйти из цикла и закончить заполнение
	if ((str[0] <= 'z') && (str[0] >= 'a') && str[1] == '\n')
	{
		printf("nice\n");
		*c1 = str[0];
		return -2;
	}
	if (str[4] == '\n' && str[1] == '-' && str[2] == '-')
	{
		if ((str[0] <= 'z') && (str[0] >= 'a') && (str[3] <= 'z') && (str[3] >= 'a'))
		{
			*c1 = str[0];
			*c2 = str[3];
			return 1;// ввод волиден
		} else
		{
			printf("Fallse input\n");
			return -1;
		}
	} else 
	{
		while((str[0] = getchar()) != '\n')
			;
		printf("Fallse input\n");
		return -1;
	}
}


int* copy(int size_new, int* old, int size_old)
{
	int* new = (int*) calloc(size_new * size_new, sizeof(int));
	if (new == NULL)
		exit(200);
	for (int i = 0, j = 0; i < size_old * size_old; ++i, ++j)
	{
		new[j] = old[i];
		if ((i % (size_old)) == (size_old - 1))
			j += size_new - size_old;
	}
	free(old);
	return new;
}


int search(char* arr, int count, char c)
{
	for (int i = 0; i < count; ++i)
		if (arr[i] == c)
			return i + 1;
	return 0;
}


void search_in_deep(int* graph, int* node, int num, int n);
// совершает поиск в глубину если пройдёт все элементы граф связный иначе не связный
// nodes > (ribs - 1) (ribs - 2) * 0.5

int is_relate(int* graph, char* titles, int count)
{
	int flag = 1;
	int* node = (int*) malloc(count * sizeof(int));
	if (node == NULL)
		exit(200);
	for (int i = 0; i < count; ++i)
		node[i] = 0;
	search_in_deep(graph, node, 0, count);
	for (int i = 0; i < count; ++i)
	{
		if (node[i] == 0)
		{
			flag = 0;
			break;
		}
	}
	free(node);
	return flag;
}


void search_in_deep(int* graph, int* node, int num, int n)
{
	int i = 0;
	node[num] = 1;
	for (i; i < n; ++i)
		if (*(graph + num * n + i) != 0 && (node[i] == 0))
			search_in_deep(graph, node, i, n);
}


void show(int* graph, char* titles, int count)
{
	FILE* visualisation = fopen("new.dot", "w");
	if (visualisation == 0)
	{
		printf("Can not create file\n");
		return;
	}
	int schet = 0;
	fprintf(visualisation, "graph first {\n");
	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count; ++j)
		{
			if (*(graph + i * count + j) == 1 && i <= j)
			{
				schet += 1;
				fprintf(visualisation, "%c--%c;\n", titles[i], titles[j]);
			}
		}
	}
	if (schet < count)
	{
		int sum = 0;
		for (int i = 0; i < count; ++i)
		{
			for (int j = 0; j < count; ++j)
				sum += *(graph + i * count + j);// если сумма значений всео ряда равна 0 то создаём пустую ноду
			if (sum == 0)
				fprintf(visualisation, "%c;\n", titles[i]);
			sum = 0;
		}
	}
	fprintf(visualisation, "}\n");
	fclose(visualisation);
	system("dot -Tpng new.dot -o graph.png");
	system("xdg-open graph.png");
	system("rm new.dot");
}

// list
// void list(int* arr, int count)
// {
// 	for (int i = 0; i < count; ++i)
// 	{
// 		for (int j = 0; j < count; ++j)
// 			printf("%d ", *(arr + i * count + j));
// 		printf("\n");
// 	}
// }

int menu(void)
{
	printf("-c to create or add graph's nodes\n");
	printf("-s to vizuate graph in png file\n");
	printf("-v to verify relate of graph\n");
	printf("-0 to quite\n");
	int	c = getchar();
	if (c != '-')
	{
		while((c = getchar()) != '\n') 
		;
		return 10;
	}
	c = getchar();
	int n = getchar();
	if (n != '\n')
		return 10;
	switch(c)
	{
		case 'c': return 1; break;
		case 's': return 2; break;
		case 'v': return 3; break;
		case '0': return 0; break;
		default: return 10;
	}
}
