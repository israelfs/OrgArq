arvore* criaArvore(char nomeArquivoIndice[]) {
    arvore* novaArvore = (arvore*)malloc(sizeof(arvore));

    novaArvore->header.status = '1';
    novaArvore->header.noRaiz = -1;
    novaArvore->header.RRNproxNo = 0;
    novaArvore->driver = 1;

    for (int i = 0; i < 68; i++) novaArvore->header.lixo[i] = '@';

    novaArvore->arquivoIndice = fopen(nomeArquivoIndice, "w+");
    if (novaArvore->arquivoIndice == NULL) printf("Arquivo nulo \n");
    salvaHeaderArvore(novaArvore);

    return novaArvore;
}

void finalizaArvore(arvore* currArvore) {
    currArvore->header.status = '1';
    salvaHeaderArvore(currArvore);

    fclose(currArvore->arquivoIndice);
    free(currArvore);
}

void salvaHeaderArvore(arvore* currArvore) {
    if (currArvore->arquivoIndice == NULL) printf("null");
    fseek(currArvore->arquivoIndice, 0, 0);

    fwrite(&currArvore->header.status, sizeof(char), 1, currArvore->arquivoIndice);
    fwrite(&currArvore->header.noRaiz, sizeof(int), 1, currArvore->arquivoIndice);
    fwrite(&currArvore->header.RRNproxNo, sizeof(int), 1, currArvore->arquivoIndice);
    fwrite(&currArvore->header.lixo, sizeof(char), 68, currArvore->arquivoIndice);
}

void leHeaderArvore(FILE* arquivoIndice, arvoreHeader* header) {
    fseek(arquivoIndice, 0, 0);

    fread(&header->status, sizeof(char), 1, arquivoIndice);
    fread(&header->noRaiz, sizeof(int), 1, arquivoIndice);
    fread(&header->RRNproxNo, sizeof(int), 1, arquivoIndice);
    fread(&header->lixo, sizeof(char), 68, arquivoIndice);
}

void lerNoArvore(arvore* currArvore, arvoreNo* novoNo, int RRN) {
    fseek(currArvore->arquivoIndice, (RRN + 1) * 77, 0);

    fread(&novoNo->folha, sizeof(char), 1, currArvore->arquivoIndice);
    fread(&novoNo->RRNdoNo, sizeof(int), 1, currArvore->arquivoIndice);
    fread(&novoNo->nroChavesIndexadas, sizeof(int), 1, currArvore->arquivoIndice);

    fread(&novoNo->registros[0].P_ant, sizeof(int), 1, currArvore->arquivoIndice);

    for (int i = 0; i < ORDEM_ARVORE - 1; i++) {
        fread(&novoNo->registros[i].C, sizeof(int), 1, currArvore->arquivoIndice);
        fread(&novoNo->registros[i].Pr, sizeof(long int), 1, currArvore->arquivoIndice);
        fread(&novoNo->registros[i].P_prox, sizeof(int), 1, currArvore->arquivoIndice);
    }

    for (int i = 0; i < ORDEM_ARVORE - 2; i++) {
        novoNo->registros[i + 1].P_ant = novoNo->registros[i].P_prox;
    }
}

void salvaNoArvore(arvore* currArvore, arvoreNo* novoNo, int RRN) {
    fseek(currArvore->arquivoIndice, (RRN + 1) * 77, 0);

    fwrite(&novoNo->folha, sizeof(char), 1, currArvore->arquivoIndice);
    fwrite(&novoNo->RRNdoNo, sizeof(int), 1, currArvore->arquivoIndice);
    fwrite(&novoNo->nroChavesIndexadas, sizeof(int), 1, currArvore->arquivoIndice);

    fwrite(&novoNo->registros[0].P_ant, sizeof(int), 1, currArvore->arquivoIndice);

    for (int i = 0; i < ORDEM_ARVORE - 1; i++) {
        fwrite(&novoNo->registros[i].C, sizeof(int), 1, currArvore->arquivoIndice);
        fwrite(&novoNo->registros[i].Pr, sizeof(long int), 1, currArvore->arquivoIndice);
        fwrite(&novoNo->registros[i].P_prox, sizeof(int), 1, currArvore->arquivoIndice);
    }
}