#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo os meus tipos de dados:

// Identidade do Veículo:
typedef struct {
	char modelo[25];	 // Nome do Modelo + Linha (Exemplo: Corolla XEI)
	char fabricante[20]; // Nome da Fabricante
	char codigo[5];		 // Código Único
} Identidade;

// Detalhes do Veículo:
typedef struct {
	int ano;			  // Ano de Fabricação
	char cor[20];		  // Cor do Carro
	int classe;			  // Sedã:1 Hatch:0
	int abs;			  // Com:1 Sem:0
	float potencia;		  // Potência do Motor
	int tracao;			  // Com:1 Sem:0
	int ocupantes;		  // Ocupantes
	char combustivel[15]; //Álcool, Gasolina, Diesel ou Híbrido
	float consumo;		  // Km/L
} Detalhes;

// Preço e Detalhes Financeiros:
typedef struct {
	float preco;
	float entrada;
	int qntd_parcelas;
	float desconto; // Esse atributo é dado em porcentagem
	float preco_final;
	float parcelas;
} Financeiro;

// Resultado final do tipo de dado Veículo:
typedef struct {
	Identidade identidade;
	Detalhes detalhes;
	Financeiro financeiro;
} Veiculo;

//"Instanciando" novo veículo
Veiculo novo_Veiculo() {
	Veiculo veiculo;

	fflush(stdin);   // Ambiente Windows
	__fpurge(stdin); // Ambiente Linux

	// Identidade
	printf("\nModelo e a linha: ");
	scanf("%[^\n]s", &veiculo.identidade.modelo);
	fflush(stdin);   // Ambiente Windows
	__fpurge(stdin); // Ambiente Linux

	printf("Fabricante: ");
	scanf("%[^\n]s", &veiculo.identidade.fabricante);
	fflush(stdin);   // Ambiente Windows
	__fpurge(stdin); // Ambiente Linux

	printf("Código do Veículo: ");
	scanf(" %s", &veiculo.identidade.codigo);

	// Detalhes

	printf("\nAno: ");
	scanf("%d", &veiculo.detalhes.ano);

	printf("Cor: ");
	scanf(" %[^\n]s", &veiculo.detalhes.cor);
	fflush(stdin);   // Ambiente Windows
	__fpurge(stdin); // Ambiente Linux

	printf("Classe (Sedan[1] Hatch[0]): ");
	scanf("%d", &veiculo.detalhes.classe);

	printf("Freios ABS (Possui[1] Não_Possui[0]): ");
	scanf("%d", &veiculo.detalhes.abs);

	printf("Potência do motor: ");
	scanf("%f", &veiculo.detalhes.potencia);

	printf("Tração (Possui[1] Não_Possui[0]): ");
	scanf("%d", &veiculo.detalhes.tracao);

	printf("Número de ocupantes: ");
	scanf("%d", &veiculo.detalhes.ocupantes);

	printf("Combustível: ");
	scanf(" %[^\n]s", &veiculo.detalhes.combustivel);
	fflush(stdin);   // Ambiente Windows
	__fpurge(stdin); // Ambiente Linux

	printf("Consumo (Km/L): ");
	scanf("%f", &veiculo.detalhes.consumo);

	// Financeiro

	printf("\nPreço: ");
	scanf("%f", &veiculo.financeiro.preco);

	printf("Entrada: ");
	scanf("%f", &veiculo.financeiro.entrada);

	printf("Quantidade Parcelas: ");
	scanf("%d", &veiculo.financeiro.qntd_parcelas);

	printf("Desconto: ");
	scanf("%f", &veiculo.financeiro.desconto);

	veiculo.financeiro.preco_final =
		(veiculo.financeiro.preco - veiculo.financeiro.entrada) -
		(veiculo.financeiro.preco * (veiculo.financeiro.desconto / 100));
	veiculo.financeiro.parcelas =
		(veiculo.financeiro.preco_final / veiculo.financeiro.qntd_parcelas);

	return veiculo;
}

// Imprimindo Veículos

void imprime_Veiculo(Veiculo veiculo) {
	printf(
		"\n\nModelo e a linha: %s\nFabricante: %s\nCódigo do Veículo: %s",
		veiculo.identidade.modelo,
		veiculo.identidade.fabricante,
		veiculo.identidade.codigo);

	printf("\n\nAno: %d", veiculo.detalhes.ano);

	printf(" - Cor: %s", veiculo.detalhes.cor);

	if (veiculo.detalhes.classe)
		printf(" - Sedan");
	else
		printf(" - Hatch");

	if (veiculo.detalhes.abs)
		printf(" - Com ABS");
	else
		printf(" - Sem ABS");

	printf(" - Potência do motor: %.1f", veiculo.detalhes.potencia);

	if (veiculo.detalhes.tracao)
		printf(" - Possui Tração");
	else
		printf(" - Não Possui Tração");

	printf(" - Número de ocupantes: %d", veiculo.detalhes.ocupantes);

	printf(" - Combustível: %s", veiculo.detalhes.combustivel);

	printf(" - Consumo: %.1f Km/L", veiculo.detalhes.consumo);

	printf(
		"\n\nPreço na Tabela: R$ %.2f\nEntrada: R$ %.2f\nQuantidade Parcelas: "
		"%d",
		veiculo.financeiro.preco,
		veiculo.financeiro.entrada,
		veiculo.financeiro.qntd_parcelas);

	if (veiculo.financeiro.desconto) {
		printf(
			" - Preço com Desconto: R$ %.2f", veiculo.financeiro.preco_final);
	} else {
		printf(" - Não possui desconto");
	}
	printf(" - Valor das Parcelas: R$ %.2f", veiculo.financeiro.parcelas);
}

// Procurando Veículo

void search_Veiculo(Veiculo veiculos[], int tamanho, char codigo[]) {
	int find = 1;
	for (int i = 0; i < tamanho; i++) {
		if (strcmp(veiculos[i].identidade.codigo, codigo) == 0) {
			imprime_Veiculo(veiculos[i]);
			find = 0;
		}
	}
	if (find)
		printf("\n\nVeículo não encontrado!");
}

int main(void) {
	setlocale(LC_ALL, "Portuguese"); // Em caso de compilações fora do Repl.it

	int option,
		start = 1,
		tamanho = 1; // Variável para opções do switch e para startar o programa
	Veiculo *veiculos;
	char codigo[5]; // Variável global, dentro do escopo da main, para pesquisa
					// de veículos

	while (start) {
		printf("\n\n::> Gestão de Estoque para Concessionárias de Veículos "
			   "<::\n\n1.Iniciar Cadastro de "
			   "Veículos.\n2.Adicionar Veículo.\n3.Pesquisar Veículo.\n4.Ver "
			   "catálogo completo.\n5.Sair do Programa\n\nOpção:");
		scanf("%d", &option);

		switch (option) {
		case 1: // Inicia o vetor de Veículos

			veiculos = malloc(sizeof(Veiculo));

			if (veiculos == NULL) {
				printf("\nERRO: Ops! Algo deu errado, tente novamente!\n\n");
			} else {
				printf("\n::> Preencha os dados do veículo <::\n");
				*veiculos = novo_Veiculo();
			}
			tamanho++;

			break;

		case 2: // Adiciona novos veículos, realocando memória

			veiculos = realloc(veiculos, (tamanho) * sizeof(Veiculo));
			if (veiculos == NULL) {
				printf("\nERRO: Ops! Algo deu errado, tente novamente!\n\n");
			} else {
				printf("\n::> Preencha os dados do veículo <::\n");
				veiculos[tamanho - 1] = novo_Veiculo();
			}
			tamanho++;

			break;

		case 3: // Pesquisando veículos

			fflush(stdin);
			__fpurge(stdin);
			printf("Insira o número do código do veículo: ");
			scanf("%[^\n]s", &codigo);
			search_Veiculo(veiculos, tamanho - 1, codigo);

			break;

		case 4: // Imprime todos os veículos

			for (int j = 0; j < tamanho - 1; j++) {
				printf(
					"\n\n::> Veículo %s <::\n", veiculos[j].identidade.codigo);
				imprime_Veiculo(veiculos[j]);
			}

			break;

		case 5: // Sair do programa

			start = 0;
			break;

		default:
			printf("\nOpção inválida, escolha a operação correta.");
		}
	}
}
