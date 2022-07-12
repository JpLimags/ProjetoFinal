#include "inc.h"
#include "pgm.h"
#include "prop.h"
#include "lib.h"


int main(){


    clock_t begin, end;
	double time_per_img, time_total=0;
	long long int a = 999999999;

    filterImg = malloc(sizeof(struct pgm));

    dir = opendir("./oncotex_pgm/datasets/");

    int tam, count = 0;
    if (dir)
    {

        while ((pImgArq = readdir(dir)) != NULL)
        {

            strcpy(nomeArquivo[iArquivo], "./oncotex_pgm/datasets/");
            identificador[iArquivo] = pImgArq->d_name[0];
            strcat(nomeArquivo[iArquivo], pImgArq->d_name);
            iArquivo++;
        }
    }

    for (int i = 2; i < iArquivo; i++)
    {

        begin = clock();
        readPGMImage(&img, nomeArquivo[i]);
        filtrolbp(&img, filterImg);
        end = clock();
        time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;
		time_total += time_per_img;
        hist = malloc(TAMCHAR * sizeof(unsigned int));
        histograma(filterImg->pData, filterImg->r, filterImg->c, hist);
        histogramaCSV(hist, nomeArquivo[i], identificador[i]);
    }

    if (count == 0) {
        printf("Nenhum arquivo encontrado\n");
    }

    printf("Tempo médio: %lf\n",time_total/count+1);
    printf("Tempo Total: %lf\n",time_total);

    closedir(dir);

    return 0;
}