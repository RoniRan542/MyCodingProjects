#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "d_vector.h"

enum status 
{
	SUCCESS = 0,
	FAILURE
};

struct vector
{
	void *data;
	size_t size;
	size_t element_size;
	size_t capacity;
};

d_vector_t *DVectorCreate(size_t element_size, size_t capacity)
{
	d_vector_t *d_vector = malloc(sizeof(d_vector_t));
	if (NULL == d_vector)
	{
		return NULL;
	}
	
	if(capacity <= 0)
	{
		capacity = DEFAULT_SIZE;
	}	
	
	d_vector->data = malloc(element_size * capacity);
	if (NULL == d_vector->data)
	{
		DVectorDestroy(d_vector);
		return NULL;
	}
	
	d_vector->size = 0;
	d_vector->element_size = element_size;
	d_vector->capacity = capacity;
	
	return d_vector;
}

size_t DVectorSize(const d_vector_t *vector)
{
	return vector->size;
}

size_t DVectorCapacity(const d_vector_t *vector)
{
	return vector->capacity;
}

int DVectorPushBack(d_vector_t *vector,const void *data)
{
	size_t offset = vector->size * vector->element_size;
	memcpy((char *)vector->data + offset , data , vector->element_size);
	++vector->size;
	if(vector->capacity == vector->size)
	{
		return DVectorReserve(vector, vector->capacity * 2);
	}
	
	return SUCCESS;
}

void *DVectorGetElement(const d_vector_t *vector, size_t index)
{
	void *ptr = 0;
	size_t offset = 0;
	
	assert(NULL != vector);
	/*assert(index < DVectorSize(vector));*/
	
	offset = vector->element_size * index;
	ptr = (char *)vector->data + offset;
	
	return ptr;
}

int DVectorIsEmpty(const d_vector_t *vector)
{
	return !vector->size;
}

void DVectorDestroy(d_vector_t *vector)
{
	free(vector->data);
	vector->data = NULL;
	free(vector);
	vector = NULL;
}

int DVectorReserve(d_vector_t *vector, size_t new_capacity)
{
	void *backup = vector->data;
	
	if(vector->size < new_capacity)
	{
		vector->data = realloc(vector->data, new_capacity * vector->element_size);
		if(NULL == vector->data)
		{
			vector->data = backup;
			return FAILURE;
		}
		vector->capacity = new_capacity;
	}
	else
	{
		return DVectorShrinkToFit(vector);
	}
	
	
	return SUCCESS;
}

int DVectorShrinkToFit(d_vector_t *vector)
{
	void *backup = vector->data;
	vector->data = realloc(vector->data, (vector->size + 1) * vector->element_size);
	if(NULL == vector->data)
	{
		vector->data = backup;
		return FAILURE;
	}
	vector->capacity = vector->size + 1;
	
	return SUCCESS;
}

int DVectorPopBack(d_vector_t  *vector)
{
	--vector->size;
	if(vector->size <= vector->capacity / 4)
	{	
		return DVectorReserve(vector, vector->capacity / 2);
	}

	return SUCCESS;
}
