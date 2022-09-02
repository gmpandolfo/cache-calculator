// Eduardo e Gabriel Pandolfo

#include <iostream> //standard lib
#include <string>   //string type
#include <cmath>    //log2
#include <vector>

using namespace std;

//Mostra o resultado final com o endereço preenchido 
template <typename T1, typename T2>
void showFormatedAddress(T1 bitArray, T2 tag, T2 index)
{
    int counter = 1;

    for (auto i : bitArray)
    {
        cout << i << (char)32;
        if (counter == tag || counter == tag + index)
            cout << '|' << (char)32;
        counter++;
    }
    cout << endl;
}

// Mostra o formato do endereço
template <typename T>
void showAddressDivisions(T tag, T index, T offset)
{
    cout << endl
         << "Quantidade de bits para rótulo: " << tag << endl
         << "Quantidade de bits para índice: " << index << endl
         << "Quantidade de bits para deslocamento: " << offset << endl
         << endl;

    cout << "Formato do endereço: \n";

    for (size_t i = 1; i < (tag + index + offset) + 1; i++)
    {
        cout << '_' << (char)32;
        if (i == tag || i == tag + index)
            cout << '|' << (char)32;
    }

    cout << endl;
}

int main(int argc, char const *argv[])
{

    uint64_t n, C, L, m;

    // vetor sequencial para armazenar o endereço em binário
    vector<int> bit_array;

    // Preenchimento das informações para a cache
    cout << "Tamanho do endereço de memória em bits: ";
    cin >> n;
    cout << "Número de linhas de cache: ";
    cin >> C;
    cout << "Tamanho da linha em bytes: ";
    cin >> L;
    cout << "Associatividade: ";
    cin >> m;

    cout << endl;

    // Cálculo do tamanho da cache
    auto memSize = [](uint64_t &C, uint64_t &L)
    { return C * L; };

    cout << "Tamanho da memória Cache: " << memSize(C, L) << " B" << endl;

    // Cálculos para definir deslocamento, índice e rótulo
    //  Diretamente associativa - tags e indices
    //  m == 1
    double offset = log2(L);
    double index = log2(C);
    double tag = n - (index + offset);

    if (m == C) // Completamente associativa - qualquer bloco da mem pode ser armazenado em qualquer linha da $
    {

        tag += index;
        index = 0;
    }
    else if (m > 1) // Associativa por conjunto
    {

        // quantidade de linhas * associatividade = 32
        // 8 * 4 = 32

        // index = log2 (quantidade de conjuntos) // NÃO da quantidade de linhas
        index -= log2(m);
        tag += m - 1;

        // RACIOCÍNIO LÓGICO
        // 64 bits
        // 8 bits de deslocamento
        // 10 bits de indice
        // 46 bits de tag

        // associatividade++

        // 8 bits de deslocamento
        // 9 bits de indice
        // 47 bits de tag
    }

    // Mostra a divisão do endereço em tag, índice e deslocamento
    showAddressDivisions((uint32_t)tag, (uint32_t)index, (uint32_t)offset);

    string memAddr;
    cout << "\nDigite um endereco de memória: 0x";
    cin >> memAddr;

    // Conversão da string hexadecimal inserida para seu valor em decimal
    string hex(memAddr);
    uint64_t decimalValue;
    sscanf(hex.c_str(), "%lx", &decimalValue);

    // printf("\nstring=%s, decimalValue=%ld\n", hex.c_str(), decimalValue);

    // Transformação do valor decimal para binário
    // Inclusão dos bits de endereço no vetor
    for (int i = n - 1; i >= 0; i--)
        bit_array.push_back((decimalValue >> i) & 1);

    showFormatedAddress(bit_array, tag, index);

    return 0;
}