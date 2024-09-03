#include "trigger.h"

#include <stdint.h>
#include "stm32f1xx_hal.h"

// Estrutura para armazenar os pinos de ativação
typedef struct {
    uint16_t colunaPin;
    uint16_t linhaPin;
} Pins;

enum Column
{
    COL_1 = 1,
    COL_2,
    COL_3,
    COL_4,
    COL_5,
    COL_6,
    COL_7,
    COL_8,
    COL_9,
    COL_10,
    COL_11,
    COL_12,
    COL_13,
    COL_14,
    COL_15,
    COL_16,
    COL_17,
    COL_18
};

enum Row
{
    ROW_1 = 1,
    ROW_2,
    ROW_3,
    ROW_4,
    ROW_5,
    ROW_6,
    ROW_7
};

// Tabela de símbolos
const char* elements[] = {
    "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", 
    "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti",
    "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", 
    "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", 
    "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te",
    "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", 
    "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf",
    "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb",
    "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U",
    "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", 
    "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", 
    "Nh", "Fl", "Mc", "Lv", "Ts", "Og"
};

// Vetores de elementos por família
const char* alkali_metals[] = {"Li", "Na", "K", "Rb", "Cs", "Fr"};
const char* alkaline_earth_metals[] = {"Be", "Mg", "Ca", "Sr", "Ba", "Ra"};
const char* transition_metals[] = {"Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", 
                                   "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", 
                                   "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", 
                                   "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn"};
const char* post_transition_metals[] = {"Al", "Ga", "In", "Sn", "Tl", "Pb", "Bi", "Nh", "Fl", "Mc", "Lv"};
const char* metalloids[] = {"B", "Si", "Ge", "As", "Sb", "Te", "Po"};
const char* nonmetals[] = {"H", "C", "N", "O", "P", "S", "Se"};
const char* halogens[] = {"F", "Cl", "Br", "I", "At", "Ts"};
const char* noble_gases[] = {"He", "Ne", "Ar", "Kr", "Xe", "Rn", "Og"};
const char* lanthanides[] = {"La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", 
                             "Ho", "Er", "Tm", "Yb", "Lu"};
const char* actinides[] = {"Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", 
                           "Es", "Fm", "Md", "No", "Lr"};

// Vetor de famílias
const char** families[] = {
    alkali_metals, alkaline_earth_metals, transition_metals, post_transition_metals,
    metalloids, nonmetals, halogens, noble_gases, lanthanides, actinides
};

// Nomes das famílias para retorno
const char* family_names[] = {
    "Alkali Metals", "Alkaline Earth Metals", "Transition Metals", "Post-Transition Metals",
    "Metalloids", "Nonmetals", "Halogens", "Noble Gases", "Lanthanides", "Actinides"
};

// Vetor necessário para conseguir realizar a validação de retorno das famílias
const int family_sizes[] = {
    sizeof(alkali_metals) / sizeof(alkali_metals[0]),
    sizeof(alkaline_earth_metals) / sizeof(alkaline_earth_metals[0]),
    sizeof(transition_metals) / sizeof(transition_metals[0]),
    sizeof(post_transition_metals) / sizeof(post_transition_metals[0]),
    sizeof(metalloids) / sizeof(metalloids[0]),
    sizeof(nonmetals) / sizeof(nonmetals[0]),
    sizeof(halogens) / sizeof(halogens[0]),
    sizeof(noble_gases) / sizeof(noble_gases[0]),
    sizeof(lanthanides) / sizeof(lanthanides[0]),
    sizeof(actinides) / sizeof(actinides[0])
};


// Vetor de estruturas PinosAtivacao correspondente aos elementos
Pins element_values[] = {
    {GPIO_PIN_9,  GPIO_PIN_7},  // H - PB9, PA7
    {GPIO_PIN_15, GPIO_PIN_7},  // He - PC15, PA7
    {GPIO_PIN_8,  GPIO_PIN_6},  // Li - PB8, PA6
    {GPIO_PIN_8,  GPIO_PIN_5},  // Be - PB8, PA5
    {GPIO_PIN_7,  GPIO_PIN_5},  // B - PB7, PA5
    {GPIO_PIN_6,  GPIO_PIN_5},  // C - PB6, PA5
    {GPIO_PIN_5,  GPIO_PIN_5},  // N - PB5, PA5
    {GPIO_PIN_4,  GPIO_PIN_5},  // O - PB4, PA5
    {GPIO_PIN_3,  GPIO_PIN_5},  // F - PB3, PA5
    {GPIO_PIN_2,  GPIO_PIN_5},  // Ne - PB2, PA5
    {GPIO_PIN_1,  GPIO_PIN_5},  // Na - PB1, PA5
    {GPIO_PIN_0,  GPIO_PIN_5},  // Mg - PB0, PA5
    {GPIO_PIN_15, GPIO_PIN_6},  // Al - PC15, PA6
    {GPIO_PIN_14, GPIO_PIN_6},  // Si - PC14, PA6
    {GPIO_PIN_13, GPIO_PIN_6},  // P - PC13, PA6
    {GPIO_PIN_12, GPIO_PIN_6},  // S - PC12, PA6
    {GPIO_PIN_11, GPIO_PIN_6},  // Cl - PC11, PA6
    {GPIO_PIN_10, GPIO_PIN_6},  // Ar - PC10, PA6
    {GPIO_PIN_9,  GPIO_PIN_6},  // K - PC9, PA6
    {GPIO_PIN_8,  GPIO_PIN_6},  // Ca - PC8, PA6
    {GPIO_PIN_7,  GPIO_PIN_6},  // Sc - PC7, PA6
    {GPIO_PIN_6,  GPIO_PIN_6},  // Ti - PC6, PA6
    {GPIO_PIN_5,  GPIO_PIN_6},  // V - PC5, PA6
    {GPIO_PIN_4,  GPIO_PIN_6},  // Cr - PC4, PA6
    {GPIO_PIN_3,  GPIO_PIN_6},  // Mn - PC3, PA6
    {GPIO_PIN_2,  GPIO_PIN_6},  // Fe - PC2, PA6
    {GPIO_PIN_1,  GPIO_PIN_6},  // Co - PC1, PA6
    {GPIO_PIN_0,  GPIO_PIN_6},  // Ni - PC0, PA6
    {GPIO_PIN_15, GPIO_PIN_7},  // Cu - PC15, PA7
    {GPIO_PIN_14, GPIO_PIN_7},  // Zn - PC14, PA7
    {GPIO_PIN_13, GPIO_PIN_7},  // Ga - PC13, PA7
    {GPIO_PIN_12, GPIO_PIN_7},  // Ge - PC12, PA7
    {GPIO_PIN_11, GPIO_PIN_7},  // As - PC11, PA7
    {GPIO_PIN_10, GPIO_PIN_7},  // Se - PC10, PA7
    {GPIO_PIN_9,  GPIO_PIN_7},  // Br - PC9, PA7
    {GPIO_PIN_8,  GPIO_PIN_7},  // Kr - PC8, PA7
    {GPIO_PIN_7,  GPIO_PIN_7},  // Rb - PC7, PA7
    {GPIO_PIN_6,  GPIO_PIN_7},  // Sr - PC6, PA7
    {GPIO_PIN_5,  GPIO_PIN_7},  // Y - PC5, PA7
    {GPIO_PIN_4,  GPIO_PIN_7},  // Zr - PC4, PA7
    {GPIO_PIN_3,  GPIO_PIN_7},  // Nb - PC3, PA7
    {GPIO_PIN_2,  GPIO_PIN_7},  // Mo - PC2, PA7
    {GPIO_PIN_1,  GPIO_PIN_7},  // Tc - PC1, PA7
    {GPIO_PIN_0,  GPIO_PIN_7},  // Ru - PC0, PA7
    {GPIO_PIN_15, GPIO_PIN_8},  // Rh - PC15, PA8
    {GPIO_PIN_14, GPIO_PIN_8},  // Pd - PC14, PA8
    {GPIO_PIN_13, GPIO_PIN_8},  // Ag - PC13, PA8
    {GPIO_PIN_12, GPIO_PIN_8},  // Cd - PC12, PA8
    {GPIO_PIN_11, GPIO_PIN_8},  // In - PC11, PA8
    {GPIO_PIN_10, GPIO_PIN_8},  // Sn - PC10, PA8
    {GPIO_PIN_9,  GPIO_PIN_8},  // Sb - PC9, PA8
    {GPIO_PIN_8,  GPIO_PIN_8},  // Te - PC8, PA8
    {GPIO_PIN_7,  GPIO_PIN_8},  // I - PC7, PA8
    {GPIO_PIN_6,  GPIO_PIN_8},  // Xe - PC6, PA8
    {GPIO_PIN_5,  GPIO_PIN_8},  // Cs - PC5, PA8
    {GPIO_PIN_4,  GPIO_PIN_8},  // Ba - PC4, PA8
    {GPIO_PIN_3,  GPIO_PIN_8},  // La - PC3, PA8
    {GPIO_PIN_2,  GPIO_PIN_8},  // Ce - PC2, PA8
    {GPIO_PIN_1,  GPIO_PIN_8},  // Pr - PC1, PA8
    {GPIO_PIN_0,  GPIO_PIN_8},  // Nd - PC0, PA8
    {GPIO_PIN_15, GPIO_PIN_9},  // Pm - PC15, PA9
    {GPIO_PIN_14, GPIO_PIN_9},  // Sm - PC14, PA9
    {GPIO_PIN_13, GPIO_PIN_9},  // Eu - PC13, PA9
    {GPIO_PIN_12, GPIO_PIN_9},  // Gd - PC12, PA9
    {GPIO_PIN_11, GPIO_PIN_9},  // Tb - PC11, PA9
    {GPIO_PIN_10, GPIO_PIN_9},  // Dy - PC10, PA9
    {GPIO_PIN_9,  GPIO_PIN_9},  // Ho - PC9, PA9
    {GPIO_PIN_8,  GPIO_PIN_9},  // Er - PC8, PA9
    {GPIO_PIN_7,  GPIO_PIN_9},  // Tm - PC7, PA9
    {GPIO_PIN_6,  GPIO_PIN_9},  // Yb - PC6, PA9
    {GPIO_PIN_5,  GPIO_PIN_9},  // Lu - PC5, PA9
    {GPIO_PIN_4,  GPIO_PIN_9},  // Hf - PC4, PA9
    {GPIO_PIN_3,  GPIO_PIN_9},  // Ta - PC3, PA9
    {GPIO_PIN_2,  GPIO_PIN_9},  // W - PC2, PA9
    {GPIO_PIN_1,  GPIO_PIN_9},  // Re - PC1, PA9
    {GPIO_PIN_0,  GPIO_PIN_9},  // Os - PC0, PA9
    {GPIO_PIN_15, GPIO_PIN_10}, // Ir - PC15, PA10
    {GPIO_PIN_14, GPIO_PIN_10}, // Pt - PC14, PA10
    {GPIO_PIN_13, GPIO_PIN_10}, // Au - PC13, PA10
    {GPIO_PIN_12, GPIO_PIN_10}, // Hg - PC12, PA10
    {GPIO_PIN_11, GPIO_PIN_10}, // Tl - PC11, PA10
    {GPIO_PIN_10, GPIO_PIN_10}, // Pb - PC10, PA10
    {GPIO_PIN_9,  GPIO_PIN_10}, // Bi - PC9, PA10
    {GPIO_PIN_8,  GPIO_PIN_10}, // Po - PC8, PA10
    {GPIO_PIN_7,  GPIO_PIN_10}, // At - PC7, PA10
    {GPIO_PIN_6,  GPIO_PIN_10}, // Rn - PC6, PA10
    {GPIO_PIN_5,  GPIO_PIN_10}, // Fr - PC5, PA10
    {GPIO_PIN_4,  GPIO_PIN_10}, // Ra - PC4, PA10
    {GPIO_PIN_3,  GPIO_PIN_10}, // Ac - PC3, PA10
    {GPIO_PIN_2,  GPIO_PIN_10}, // Th - PC2, PA10
    {GPIO_PIN_1,  GPIO_PIN_10}, // Pa - PC1, PA10
    {GPIO_PIN_0,  GPIO_PIN_10}, // U - PC0, PA10
    {GPIO_PIN_15, GPIO_PIN_11}, // Np - PC15, PA11
    {GPIO_PIN_14, GPIO_PIN_11}, // Pu - PC14, PA11
    {GPIO_PIN_13, GPIO_PIN_11}, // Am - PC13, PA11
    {GPIO_PIN_12, GPIO_PIN_11}, // Cm - PC12, PA11
    {GPIO_PIN_11, GPIO_PIN_11}, // Bk - PC11, PA11
    {GPIO_PIN_10, GPIO_PIN_11}, // Cf - PC10, PA11
    {GPIO_PIN_9,  GPIO_PIN_11}, // Es - PC9, PA11
    {GPIO_PIN_8,  GPIO_PIN_11}, // Fm - PC8, PA11
    {GPIO_PIN_7,  GPIO_PIN_11}, // Md - PC7, PA11
    {GPIO_PIN_6,  GPIO_PIN_11}, // No - PC6, PA11
    {GPIO_PIN_5,  GPIO_PIN_11}, // Lr - PC5, PA11
    {GPIO_PIN_4,  GPIO_PIN_11}, // Rf - PC4, PA11
    {GPIO_PIN_3,  GPIO_PIN_11}, // Db - PC3, PA11
    {GPIO_PIN_2,  GPIO_PIN_11}, // Sg - PC2, PA11
    {GPIO_PIN_1,  GPIO_PIN_11}, // Bh - PC1, PA11
    {GPIO_PIN_0,  GPIO_PIN_11}, // Hs - PC0, PA11
    {GPIO_PIN_15, GPIO_PIN_12}, // Mt - PC15, PA12
    {GPIO_PIN_14, GPIO_PIN_12}, // Ds - PC14, PA12
    {GPIO_PIN_13, GPIO_PIN_12}, // Rg - PC13, PA12
    {GPIO_PIN_12, GPIO_PIN_12}, // Cn - PC12, PA12
    {GPIO_PIN_11, GPIO_PIN_12}, // Nh - PC11, PA12
    {GPIO_PIN_10, GPIO_PIN_12}, // Fl - PC10, PA12
    {GPIO_PIN_9,  GPIO_PIN_12}, // Mc - PC9, PA12
    {GPIO_PIN_8,  GPIO_PIN_12}, // Lv - PC8, PA12
    {GPIO_PIN_7,  GPIO_PIN_12}, // Ts - PC7, PA12
    {GPIO_PIN_6,  GPIO_PIN_12}  // Og - PC6, PA12
};


// Função para buscar o índice de um elemento
int find_element_index(const char *symbol)
{
    int num_elements = sizeof(elements) / sizeof(elements[0]);
    for (int i = 0; i < num_elements; i++)
    {
        if (strcmp(elements[i], symbol) == 0)
        {
            return i;
        }
    }
    return -1; // Retorna -1 se não encontrado
}

// Função para converter símbolo em valor de 8 bits
uint8_t get_element_value(const char *symbol)
{
    int index = find_element_index(symbol);
    if (index != -1)
    {
        return element_values[index];
    }
    return 0; // Retorna 0 se o símbolo não for encontrado
}

// Função para buscar a família pelo nome
const char** find_family(const char *name, int *family_size)
{
    int num_families = sizeof(family_names) / sizeof(family_names[0]);
    
    for (int i = 0; i < num_families; i++)
    {
        if (strcmp(family_names[i], name) == 0)
        {
            *family_size = family_sizes[i];
            return families[i];
        }
    }
    return NULL; // Retorna NULL se a família não for encontrada
}

void activate_pins(const char *symbol) {
    int index = find_element_index(symbol);
    
    if (index == -1) {
        // Elemento não encontrado
        return;
    }
    
    // Obtenha os pinos para o elemento encontrado
    Pins pinos = element_values[index];
    
    // Ative os pinos correspondentes
    if (pinos.colunaPin != 0) {
        HAL_GPIO_WritePin(GPIOB, pinos.colunaPin, GPIO_PIN_SET);
    }
    if (pinos.linhaPin != 0) {
        HAL_GPIO_WritePin(GPIOA, pinos.linhaPin, GPIO_PIN_SET);
    }
}

void deactivate_pins(const char *symbol) {
    int index = find_element_index(symbol);
    
    if (index == -1) {
        // Elemento não encontrado
        return;
    }
    
    // Obtenha os pinos para o elemento encontrado
    Pins pinos = element_values[index];
    
    // Desative os pinos correspondentes
    if (pinos.colunaPin != 0) {
        HAL_GPIO_WritePin(GPIOB, pinos.colunaPin, GPIO_PIN_RESET);
    }
    if (pinos.linhaPin != 0) {
        HAL_GPIO_WritePin(GPIOA, pinos.linhaPin, GPIO_PIN_RESET);
    }
}