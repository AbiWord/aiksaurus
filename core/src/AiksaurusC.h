#ifndef INCLUDED_AIKSAURUSC_H
#define INCLUDED_AIKSAURUSC_H

#if defined (__cplusplus)
extern "C" {
#endif
    int  Aiksaurus_init();
    void Aiksaurus_destroy();

    const char* Aiksaurus_error();
    const char* Aiksaurus_word();

    int Aiksaurus_find(const char* meaning);

    const char* Aiksaurus_next(int* meaning);
    const char* Aiksaurus_similar();
#if defined (__cplusplus)
}
#endif 

#endif
