#include "AiksaurusC.h"
#include "Aiksaurus.h"
#include <new>

static Aiksaurus *instance = 0;

int Aiksaurus_init()
{
    if (!instance)
        instance = new(nothrow) Aiksaurus;
    
    return (instance != 0); 
}

void Aiksaurus_destroy()
{
    delete instance;
    instance = 0;
}

const char* Aiksaurus_error()
{
    if (instance)
        return instance->error();
    else
        return "Error: Aiksaurus_error() called before Aiksaurus_init()";
}

const char* Aiksaurus_word()
{
    return((instance) ? (instance->word()) : (""));
}

int Aiksaurus_find(const char* word)
{
    return((instance) ? (instance->find(word)) : (0));
}

const char* Aiksaurus_next(int* meaning)
{
    return((instance) ? (instance->next(*meaning)) : (""));
}

const char* Aiksaurus_similar()
{
    return((instance) ? (instance->similar()) : (""));
}



