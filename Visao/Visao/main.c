#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include "vc.h"
int main()
{
	IVC *image[5];
	int i, numero;
	OVC *nobjetos;

	image[0] = vc_read_image("Imagens/Imagem01.ppm");
	if (image[0] == NULL)
	{
		printf("Error -> vc_read_image():\tFile not found.\n");
		getchar();
		return 0;
	}

	image[1] = vc_image_new(image[0]->width, image[0]->height,1, image[0]->levels);
	if (image[1] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	image[2] = vc_image_new(image[0]->width, image[0]->height, 1, image[0]->levels);
	if (image[2] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	image[3] = vc_image_new(image[0]->width, image[0]->height, 1, image[0]->levels);
	if (image[3] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	image[4] = vc_image_new(image[0]->width, image[0]->height, 1, image[0]->levels);
	if (image[4] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	vc_rgb_to_hsv(image[0]);
	vc_hsv_segmentation(image[0], 10, 45, 10, 38, 55, 90);
	vc_rgb_to_gray(image[0], image[1]);
	vc_gray_negative(image[1]);

	vc_binary_open(image[1], image[2], 5, 5);
	vc_binary_close(image[2], image[3], 3, 3);

	nobjetos = vc_binary_blob_labelling(image[3], image[4], &numero);
	vc_binary_blob_info(image[4], nobjetos, numero);
	vc_write_image("vc0001.ppm", image[4]);
	vc_draw_image(nobjetos,image[4],numero);

	for (i = 0; i < numero; i++)
	{
		printf("X = %d Y = %d\n", nobjetos[i].x, nobjetos[i].y);
	}
	printf("\n\n Numero de objetos = %d", numero);



	vc_write_image("vc00023.ppm", image[3]);
	vc_write_image("vc0002.ppm", image[4]); 
	free(nobjetos);
	vc_image_free(image[0]);
	vc_image_free(image[1]);
	vc_image_free(image[2]);
	vc_image_free(image[3]);
	vc_image_free(image[4]);

	system("cmd /c start FilterGear Imagens/Imagem01.ppm"); // Input
	system("FilterGear vc00023.ppm"); // Output
	system("FilterGear vc0001.ppm"); // Output
	system("FilterGear vc0002.ppm"); // Output

	printf("\nPress any key to exit.\n");
	getchar();
	return 0;

}