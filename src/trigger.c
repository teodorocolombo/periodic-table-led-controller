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

// Tabela de valores (linha << 4 | coluna)
// Iremos usar a GPIOA como saida, onde utilizaremos 8bits para escolher qual
// Tabela de valores (linha << 3 | coluna)
const uint8_t element_values[] = {
    (ROW_1 << 3) | COL_1,  // H
    (ROW_1 << 3) | COL_18, // He
    (ROW_2 << 3) | COL_1,  // Li
    (ROW_2 << 3) | COL_2,  // Be
    (ROW_2 << 3) | COL_13, // B
    (ROW_2 << 3) | COL_14, // C
    (ROW_2 << 3) | COL_15, // N
    (ROW_2 << 3) | COL_16, // O
    (ROW_2 << 3) | COL_17, // F
    (ROW_2 << 3) | COL_18, // Ne
    (ROW_3 << 3) | COL_1,  // Na
    (ROW_3 << 3) | COL_2,  // Mg
    (ROW_3 << 3) | COL_13, // Al
    (ROW_3 << 3) | COL_14, // Si
    (ROW_3 << 3) | COL_15, // P
    (ROW_3 << 3) | COL_16, // S
    (ROW_3 << 3) | COL_17, // Cl
    (ROW_3 << 3) | COL_18, // Ar
    (ROW_4 << 3) | COL_1,  // K
    (ROW_4 << 3) | COL_2,  // Ca
    (ROW_4 << 3) | COL_3,  // Sc
    (ROW_4 << 3) | COL_4,  // Ti
    (ROW_4 << 3) | COL_5,  // V
    (ROW_4 << 3) | COL_6,  // Cr
    (ROW_4 << 3) | COL_7,  // Mn
    (ROW_4 << 3) | COL_8,  // Fe
    (ROW_4 << 3) | COL_9,  // Co
    (ROW_4 << 3) | COL_10, // Ni
    (ROW_4 << 3) | COL_11, // Cu
    (ROW_4 << 3) | COL_12, // Zn
    (ROW_4 << 3) | COL_13, // Ga
    (ROW_4 << 3) | COL_14, // Ge
    (ROW_4 << 3) | COL_15, // As
    (ROW_4 << 3) | COL_16, // Se
    (ROW_4 << 3) | COL_17, // Br
    (ROW_4 << 3) | COL_18, // Kr
    (ROW_5 << 3) | COL_1,  // Rb
    (ROW_5 << 3) | COL_2,  // Sr
    (ROW_5 << 3) | COL_3,  // Y
    (ROW_5 << 3) | COL_4,  // Zr
    (ROW_5 << 3) | COL_5,  // Nb
    (ROW_5 << 3) | COL_6,  // Mo
    (ROW_5 << 3) | COL_7,  // Tc
    (ROW_5 << 3) | COL_8,  // Ru
    (ROW_5 << 3) | COL_9,  // Rh
    (ROW_5 << 3) | COL_10, // Pd
    (ROW_5 << 3) | COL_11, // Ag
    (ROW_5 << 3) | COL_12, // Cd
    (ROW_5 << 3) | COL_13, // In
    (ROW_5 << 3) | COL_14, // Sn
    (ROW_5 << 3) | COL_15, // Sb
    (ROW_5 << 3) | COL_16, // Te
    (ROW_5 << 3) | COL_17, // I
    (ROW_5 << 3) | COL_18, // Xe
    (ROW_6 << 3) | COL_1,  // Cs
    (ROW_6 << 3) | COL_2,  // Ba
    (ROW_6 << 3) | COL_3,  // La
    (ROW_6 << 3) | COL_4,  // Ce
    (ROW_6 << 3) | COL_5,  // Pr
    (ROW_6 << 3) | COL_6,  // Nd
    (ROW_6 << 3) | COL_7,  // Pm
    (ROW_6 << 3) | COL_8,  // Sm
    (ROW_6 << 3) | COL_9,  // Eu
    (ROW_6 << 3) | COL_10, // Gd
    (ROW_6 << 3) | COL_11, // Tb
    (ROW_6 << 3) | COL_12, // Dy
    (ROW_6 << 3) | COL_13, // Ho
    (ROW_6 << 3) | COL_14, // Er
    (ROW_6 << 3) | COL_15, // Tm
    (ROW_6 << 3) | COL_16, // Yb
    (ROW_6 << 3) | COL_17, // Lu
    (ROW_7 << 3) | COL_3,  // Ac
    (ROW_7 << 3) | COL_4,  // Th
    (ROW_7 << 3) | COL_5,  // Pa
    (ROW_7 << 3) | COL_6,  // U
    (ROW_7 << 3) | COL_7,  // Np
    (ROW_7 << 3) | COL_8,  // Pu
    (ROW_7 << 3) | COL_9,  // Am
    (ROW_7 << 3) | COL_10, // Cm
    (ROW_7 << 3) | COL_11, // Bk
    (ROW_7 << 3) | COL_12, // Cf
    (ROW_7 << 3) | COL_13, // Es
    (ROW_7 << 3) | COL_14, // Fm
    (ROW_7 << 3) | COL_15, // Md
    (ROW_7 << 3) | COL_16, // No
    (ROW_7 << 3) | COL_17, // Lr
    (ROW_7 << 3) | COL_4,  // Rf
    (ROW_7 << 3) | COL_5,  // Db
    (ROW_7 << 3) | COL_6,  // Sg
    (ROW_7 << 3) | COL_7,  // Bh
    (ROW_7 << 3) | COL_8,  // Hs
    (ROW_7 << 3) | COL_9,  // Mt
    (ROW_7 << 3) | COL_10, // Ds
    (ROW_7 << 3) | COL_11, // Rg
    (ROW_7 << 3) | COL_12, // Cn
    (ROW_7 << 3) | COL_13, // Nh
    (ROW_7 << 3) | COL_14, // Fl
    (ROW_7 << 3) | COL_15, // Mc
    (ROW_7 << 3) | COL_16, // Lv
    (ROW_7 << 3) | COL_17, // Ts
    (ROW_7 << 3) | COL_18  // Og
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