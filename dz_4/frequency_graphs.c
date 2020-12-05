#include <stdio.h>
#include <stdlib.h>

typedef struct title
{
	char name;
	int frequency;	
} title_t;

int menu(void);
int* add(int* graph, title_t** tops, int* count);// добавляет ветви в граф
void show(int* graph, title_t* tops, int count);// визуализирует граф в формате png
int is_relate(int* graph, int count);// проверяет граф на связность
void sort_graph(int* graph, title_t*, int count);
void list_frequency(title_t* tops, int count);

int main(void)
{
	int flag = menu();
	int count = 0;
	int* graph = NULL;
	title_t* tops = NULL;
	int res = 0;
	while (flag)
	{
		switch(flag)
		{
			case 1: graph = add(graph, &tops, &count); break;
			case 2: show(graph, tops, count); break;
			case 3: 
			res = is_relate(graph, count);
			if (res == 1)
				printf("relateed graph\n");
			else 
				printf("unreleated graph\n");
			break;
			case 4: sort_graph(graph, tops, count); break;
			default: printf("Don't know such command\n"); 
		}
		flag = menu();
	}
	free(graph);
	free(tops);
	return 0;
}


void buble_sort(title_t* tops, int* graph, int size);
void list(int* arr, int i); // выводит двумерный массив
void swap_line(int* graph, int line_sort, int line_basis, int size);
void swap_column(int* graph, int column_sort, int column_basis, int size);


void sort_graph(int* graph, title_t* tops, int count)
{
	buble_sort(tops, graph, count);
	list_frequency(tops, count);
}

void swap_column(int* graph, int A, int B, int size)
{
	int* swap_arr = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; ++i)
	{
		swap_arr[i] = *(graph + i * size + A);
		*(graph + i * size + A) = *(graph + i * size + B);
		*(graph + i * size + B) = swap_arr[i];
	}
	free(swap_arr);	
}

void swap_line(int* graph, int A, int B, int size)
{
	int* swap_arr = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; ++i)
	{
		swap_arr[i] = *(graph + A * size + i);
		*(graph + A * size + i) = *(graph + B * size + i);
		*(graph + B * size + i) = swap_arr[i];
	}
	free(swap_arr);	
}

void buble_sort(title_t* tops, int* graph, int size)
{
	for(int i = 0; i < size - 1; ++i)
	{
		int f = 0;
		for(int j = 0; j < size - i - 1; ++j)
		{
			if ((tops + j)->frequency > (tops + j + 1)->frequency)
			{
				f = 1;
				title_t tmp = tops[j];
				tops[j] = tops[j + 1];
				tops[j + 1] = tmp;
				swap_line(graph, j, j + 1, size);
				swap_column(graph, j, j + 1, size);
			}
		} 
		if (f == 0) break;
	}
}



void list_frequency(title_t* tops, int count)
{
	for (int i = 0; i < count; ++i)
		printf("%c: %d\n", (tops + i)->name, (tops + i)->frequency);
}

int titles_from_input(char* c1, char* c2);// возвращает две введённые пользователем буквы
int search(title_t* p_str, int i, char c);// ищет индекс буквы в массиве titels
int* copy(int size_new, int* old, int size_old);// создаёт двумерный массив size_new * size_new копирует значения из старого массива


int* add(int* graph, title_t** tops, int* count)
{
	printf("Use such format \"a--c\"\n");
	printf("Tap '*' to fifnsh input\n");
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
			num_c1 = search(*tops, size, c1);
			if (num_c1 == 0)
			{
				size += 1;
				*tops = (title_t*) realloc(*tops, size * sizeof(title_t));
				if (*tops == NULL)
					exit(200);
				(*tops + size - 1)->name = c1;
				// (*tops + size - 1)->frequency += 1;
				// *(*titles + size - 1) = c1;
				graph = copy(size, graph, size - 1);				
			} else
			{
				flag = titles_from_input(&c1, &c2);
				continue;
			}
			// 
			// 
			// 
		} else
		{
			num_c1 = search(*tops, size, c1);
			num_c2 = search(*tops, size, c2);
			if (num_c1 != 0)
			{
				if (num_c2 != 0)
				{
					if (num_c1 != num_c2)// a--c a and c already exist
					{
						*(graph + (num_c1 - 1) * size + num_c2 - 1) += 1;// для с1
						*(graph + (num_c2 - 1) * size + num_c1 - 1) += 1;
						(*tops + num_c2 - 1)->frequency += 1;
						(*tops + num_c1 - 1)->frequency += 1;
					} else // a--a a already exist
					{
						*(graph + (num_c2 - 1) * size + num_c1 - 1) += 1;
						(*tops + num_c1 - 1)->frequency += 2;
					}
				}else
				{
					
					size += 1;
					*tops = (title_t*) realloc(*tops, size * sizeof(title_t));
					if (*tops == NULL)
						exit(200);
					(*tops + size - 1)->name = c2;

					graph = copy(size, graph, size - 1);
					*(graph + (num_c1 - 1) * size + size - 1) += 1;// для с1
					*(graph + (size - 1) * size + num_c1 - 1) += 1;

					(*tops + num_c1 - 1)->frequency += 1;
					(*tops + size - 1)->frequency += 1;
				}

			} else if (num_c2 != 0)
			{
				size += 1;
				*tops = (title_t*) realloc(*tops, size * sizeof(title_t));
				if (*tops == NULL)
					exit(200);
				(*tops + size - 1)->name = c1;

				graph = copy(size, graph, size - 1);
				*(graph + (num_c2 - 1) * size + size - 1) += 1;// для с1
				*(graph + (size - 1) * size + num_c2 - 1) += 1;
				(*tops + size - 1)->frequency += 1;
				(*tops + num_c2 - 1)->frequency += 1;
			} else
			{
				size += 2;
				*tops = (title_t*) realloc(*tops, size * sizeof(title_t));
				if (*tops == NULL)
					exit(200);
				// *(*titles + size - 2) = c1;
				(*tops + size - 2)->name = c1;
				// *(*titles + size - 1) = c2;
				(*tops + size - 1)->name = c2;
				(*tops + size - 2)->frequency += 1;
				(*tops + size - 1)->frequency += 1;
				if ((size - 2) == 0)
				{
					graph = (int*) realloc(graph, size * size * sizeof(int));
					if (graph == NULL)
						exit(200);
					*(graph + (size - 2) * size + size - 1) += 1;// для с1
					*(graph + (size - 1) * size + size - 2) += 1;
				}else
				{
					graph = copy(size, graph, size - 2);
					*(graph + (size - 2) * size + size - 1) += 1;// для с1
					*(graph + (size - 1) * size + size - 2) += 1;
				}
			}
		}
		// list(graph, size);
		flag = titles_from_input(&c1, &c2);
	}
	// while ((c = getchar()) != '\n'); 
	*count = size;
	return graph;
}


int titles_from_input(char* c1, char* c2)// вовращает две ведёные буквы - названия ячеек
{
	char str[5];
	int i = 0;
	for (i; i < 5 && ((str[i] = getchar()) != '\n') && (str[i] != '*'); ++i)
		;
	if (str[i] == '*')
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


int search(title_t* p_str, int count, char c)
{
	for (int i = 0; i < count; ++i)
		if ((p_str + i)->name == c)
			return i + 1;
	return 0;
}


void search_in_deep(int* graph, int* node, int num, int n);
// совершает поиск в глубину если пройдёт все элементы граф связный иначе не связный
// nodes > (ribs - 1) (ribs - 2) * 0.5

int is_relate(int* graph, int count)
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


void show(int* graph, title_t* tops, int count)
{
	FILE* visualisation = fopen("new_new.dot", "w");
	if (visualisation == 0)
	{
		printf("Can not create file\n");
		return;
	}
	int sum = 0;
	fprintf(visualisation, "graph first {\n");
	// list(graph, count);
	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count; ++j)
		{
			sum += *(graph + i * count + j);
			if (*(graph + i * count + j) > 0 && i <= j)
			{
				int circle = *(graph + i * count + j);
				do
				{
					fprintf(visualisation, "%c--%c;\n", (tops + i)->name, (tops + j)->name);
					circle -= 1;
				} while (circle > 0);

			}
		}
		if (sum == 0)
			fprintf(visualisation, "%c;\n", (tops + i)->name);
		sum = 0;
	}

	fprintf(visualisation, "}\n");
	fclose(visualisation);
	system("dot -Tpng new_new.dot -o graph.png");
	system("xdg-open graph.png");
	system("rm new_new.dot");
}

// list
void list(int* arr, int count)
{
	for (int i = 0; i < count; ++i)
	{
		for (int j = 0; j < count; ++j)
			printf("%d ", *(arr + i * count + j));
		printf("\n");
	}
}

int menu(void)
{
	printf("-c to create or add graph's nodes\n");
	printf("-s to vizuate graph in png file\n");
	printf("-v to verify relate of graph\n");
	printf("-l to list frequency and sort graph\n");
	printf("-0 to quite\n");
	int	c = getchar();
	if (c != '-' && c != -1)
	{
		while(c != '\n') 
			c = getchar();
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
		case 'l': return 4; break;
		case '0': return 0; break;
		default: return 10;
	}
}
