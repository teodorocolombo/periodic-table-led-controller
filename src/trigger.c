#include "trigger.h"

#include <stdint.h>

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

// Tabela de valores (linha << 4 | coluna)
// Iremos usar a GPIOA como saida, onde utilizaremos 8bits para escolher qual
// Tabela de valores (linha << 3 | coluna)
const uint8_t element_values[] = {
    (ROW_1) | (COL_1 << 3),  // H   = 00001001
    (ROW_1) | (COL_18 << 3), // He  = 10010001
    (ROW_2) | (COL_1 << 3),  // Li  = 00001010
    (ROW_2) | (COL_2 << 3),  // Be  = 00011010
    (ROW_2) | (COL_13 << 3), // B   = 10101010
    (ROW_2) | (COL_14 << 3), // C   = 10111010
    (ROW_2) | (COL_15 << 3), // N   = 11001010
    (ROW_2) | (COL_16 << 3), // O   = 11011010
    (ROW_2) | (COL_17 << 3), // F   = 11101010
    (ROW_2) | (COL_18 << 3), // Ne  = 11111010
    (ROW_3) | (COL_1 << 3),  // Na  = 00001011
    (ROW_3) | (COL_2 << 3),  // Mg  = 00011011
    (ROW_3) | (COL_13 << 3), // Al  = 10101011
    (ROW_3) | (COL_14 << 3), // Si  = 10111011
    (ROW_3) | (COL_15 << 3), // P   = 11001011
    (ROW_3) | (COL_16 << 3), // S   = 11011011
    (ROW_3) | (COL_17 << 3), // Cl  = 11101011
    (ROW_3) | (COL_18 << 3), // Ar  = 11111011
    (ROW_4) | (COL_1 << 3),  // K   = 00001100
    (ROW_4) | (COL_2 << 3),  // Ca  = 00011100
    (ROW_4) | (COL_3 << 3),  // Sc  = 00101100
    (ROW_4) | (COL_4 << 3),  // Ti  = 00111100
    (ROW_4) | (COL_5 << 3),  // V   = 01001100
    (ROW_4) | (COL_6 << 3),  // Cr  = 01011100
    (ROW_4) | (COL_7 << 3),  // Mn  = 01101100
    (ROW_4) | (COL_8 << 3),  // Fe  = 01111100
    (ROW_4) | (COL_9 << 3),  // Co  = 10001100
    (ROW_4) | (COL_10 << 3), // Ni  = 10011100
    (ROW_4) | (COL_11 << 3), // Cu  = 10101100
    (ROW_4) | (COL_12 << 3), // Zn  = 10111100
    (ROW_4) | (COL_13 << 3), // Ga  = 11001100
    (ROW_4) | (COL_14 << 3), // Ge  = 11011100
    (ROW_4) | (COL_15 << 3), // As  = 11101100
    (ROW_4) | (COL_16 << 3), // Se  = 11111100
    (ROW_4) | (COL_17 << 3), // Br  = 00001101
    (ROW_4) | (COL_18 << 3), // Kr  = 00011101
    (ROW_5) | (COL_1 << 3),  // Rb  = 00001101
    (ROW_5) | (COL_2 << 3),  // Sr  = 00011101
    (ROW_5) | (COL_3 << 3),  // Y   = 00101101
    (ROW_5) | (COL_4 << 3),  // Zr  = 00111101
    (ROW_5) | (COL_5 << 3),  // Nb  = 01001101
    (ROW_5) | (COL_6 << 3),  // Mo  = 01011101
    (ROW_5) | (COL_7 << 3),  // Tc  = 01101101
    (ROW_5) | (COL_8 << 3),  // Ru  = 01111101
    (ROW_5) | (COL_9 << 3),  // Rh  = 10001101
    (ROW_5) | (COL_10 << 3), // Pd  = 10011101
    (ROW_5) | (COL_11 << 3), // Ag  = 10101101
    (ROW_5) | (COL_12 << 3), // Cd  = 10111101
    (ROW_5) | (COL_13 << 3), // In  = 11001101
    (ROW_5) | (COL_14 << 3), // Sn  = 11011101
    (ROW_5) | (COL_15 << 3), // Sb  = 11101101
    (ROW_5) | (COL_16 << 3), // Te  = 11111101
    (ROW_5) | (COL_17 << 3), // I   = 00001110
    (ROW_5) | (COL_18 << 3), // Xe  = 00011110
    (ROW_6) | (COL_1 << 3),  // Cs  = 00001110
    (ROW_6) | (COL_2 << 3),  // Ba  = 00011110
    (ROW_6) | (COL_3 << 3),  // La  = 00101110
    (ROW_6) | (COL_4 << 3),  // Ce  = 00111110
    (ROW_6) | (COL_5 << 3),  // Pr  = 01001110
    (ROW_6) | (COL_6 << 3),  // Nd  = 01011110
    (ROW_6) | (COL_7 << 3),  // Pm  = 01101110
    (ROW_6) | (COL_8 << 3),  // Sm  = 01111110
    (ROW_6) | (COL_9 << 3),  // Eu  = 10001110
    (ROW_6) | (COL_10 << 3), // Gd  = 10011110
    (ROW_6) | (COL_11 << 3), // Tb  = 10101110
    (ROW_6) | (COL_12 << 3), // Dy  = 10111110
    (ROW_6) | (COL_13 << 3), // Ho  = 11001110
    (ROW_6) | (COL_14 << 3), // Er  = 11011110
    (ROW_6) | (COL_15 << 3), // Tm  = 11101110
    (ROW_6) | (COL_16 << 3), // Yb  = 11111110
    (ROW_6) | (COL_17 << 3), // Lu  = 00001111
    (ROW_7) | (COL_3 << 3),  // Ac  = 00101111
    (ROW_7) | (COL_4 << 3),  // Th  = 00111111
    (ROW_7) | (COL_5 << 3),  // Pa  = 01001111
    (ROW_7) | (COL_6 << 3),  // U   = 01011111
    (ROW_7) | (COL_7 << 3),  // Np  = 01101111
    (ROW_7) | (COL_8 << 3),  // Pu  = 01111111
    (ROW_7) | (COL_9 << 3),  // Am  = 10001111
    (ROW_7) | (COL_10 << 3), // Cm  = 10011111
    (ROW_7) | (COL_11 << 3), // Bk  = 10101111
    (ROW_7) | (COL_12 << 3), // Cf  = 10111111
    (ROW_7) | (COL_13 << 3), // Es  = 11001111
    (ROW_7) | (COL_14 << 3), // Fm  = 11011111
    (ROW_7) | (COL_15 << 3), // Md  = 11101111
    (ROW_7) | (COL_16 << 3), // No  = 11111111
    (ROW_7) | (COL_17 << 3), // Lr  = 00010000
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