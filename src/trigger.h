#ifndef TRIGGER_H
#define TRIGGER_H

int find_element_index(const char *symbol);
unsigned char get_element_value(const char *symbol);
const char** find_family(const char *name, int *family_size);

#endif //TRIGGER_H