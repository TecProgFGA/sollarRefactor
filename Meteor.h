/*
* Solar 3D Técnicas de Programação
* Esse programa carrega o meteoro, sua textura e
* envia para a área do jogo, configurando a área ocupada e
* desenhando o meteoro na área configurando também sua
* aceleração
*/

#ifndef METEORO_H
#define METEORO_H
#include <GL/glut.h>
#include "Collision.h"

/* loads the meteor model */
void carregaModeloMeteoro(GLMmodel **meteoro)
{
	if (*meteoro == NULL) {
		*meteoro = glmReadOBJ("data/meteoro/meteoro.obj");
		if (*meteoro == NULL){
			printf("\n\nErro carregando meteoro.obj");
			exit(0);
		}
		else {
		  /* nothing to do */
		}
		glmUnitize(*meteoro); /* redimensions to unity matrix */
		glmFacetNormals(*meteoro);
		glmVertexNormals(*meteoro, 90.0);
	}
	else {
		printf("Meteoro nao carregado! \n");
	}
}

/* creates an empty meteor position */
int posicaoVaziaMeteoros(game_item *meteoros)
{
	int i = 0;
	for (i = 0; i < MAX_NUMBER_OF_METEORS_THAT_WILL_APPEAR; i++) {
		if (!meteoros[i].visible) {
			return i;
		}
		else {
			/* nothing to do */
		}
	}
	return -1;
}

/* send meteor to the screen */
void enviaMeteoro(game_item *meteoros,
				  int meteorosEnviar,
				  collision_box colisaoMeteoroDefault)
{
	int i = 0;

	for (i = 0; i < meteorosEnviar; i++) {
		int pos = posicaoVaziaMeteoros(meteoros);

		if (pos >= 0) {
			meteoros[pos].visible = TRUE;
			meteoros[pos].position.z = (INICIAL_POSITION_OF_METEOR_IN_THE_AXIS_Z-10) -
									   rand()%(INICIAL_POSITION_OF_METEOR_IN_THE_AXIS_Z -
									   -20);
			meteoros[pos].position.x = MINIMUN_X + rand() % (MAXIMUM_X-MINIMUN_X);
			meteoros[pos].position.y = MINIMUM_Y + rand() % (MAXIMUM_Y-MINIMUM_Y);
			/*
			 * Keep the last position to calculate the collision box
			 * to the meteor in a different position of <0, 0, 0>
			 */
			meteoros[pos].last_position.z = meteoros[pos].position.z;
			meteoros[pos].last_position.x = meteoros[pos].position.x;
			meteoros[pos].last_position.y = meteoros[pos].position.y;

			int c = 0;
			/* fix me. I am out of the bounds*/
			for (c = 0; c < 8; c++){
				meteoros[pos].collision.points[c].x = colisaoMeteoroDefault.points[c].x;
				meteoros[pos].collision.points[c].y = colisaoMeteoroDefault.points[c].y;
				meteoros[pos].collision.points[c].z = colisaoMeteoroDefault.points[c].z;
			}
			setaCaixaColisao(&meteoros[pos].collision, meteoros[pos].position);
		}
		else {
			/* nothing to do */
		}
	}
}

/* loads the meteor texture */
void carregaTexturaMeteoro(Texture *texturaMetoro, char *filePath)
{
	if (LoadTGA(texturaMetoro, filePath)) {
		glGenTextures(1, &texturaMetoro->texID);
		glBindTexture(GL_TEXTURE_2D, texturaMetoro->texID);
		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 texturaMetoro->bpp / 8,
					 texturaMetoro->width,
					 texturaMetoro->height,
					 0,
					 texturaMetoro->type,
					 GL_UNSIGNED_BYTE,
					 texturaMetoro->imageData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
	}
	else {
		printf("\nErro carregando a textura do meteoro");
	}
}

/* configur the meteor collision box */
void configuraCaixaColisaoMeteoro(collision_box *colisaoMeteoroDefault)
{
	int c;

	for (c = 0; c < 8; c++){
		colisaoMeteoroDefault->points[c].x*=METEOR_SCALE;
		colisaoMeteoroDefault->points[c].y*=METEOR_SCALE;
		colisaoMeteoroDefault->points[c].z*=METEOR_SCALE;
	}
}

/* configur the meteors' aceleration */
void configuraAceleracaoMeteoros(game_item *meteoros)
{
	int i = 0;

	for (i = 0; i < MAX_NUMBER_OF_METEORS_THAT_WILL_APPEAR; i++) {
		meteoros[i].acceleration = 0.02;
	}
}

/* draws meteors */
void desenhaMeteoros(game_item *meteoros,
					 Texture texturaMetoro,
					 GLMmodel *meteoro)
{
	int i = 0;

	for (i = 0; i < MAX_NUMBER_OF_METEORS_THAT_WILL_APPEAR; i++) {
		if (meteoros[i].visible) {
			glPushMatrix();
			glTranslatef(meteoros[i].position.x,
						 meteoros[i].position.y,
						 meteoros[i].position.z);
			desenhaModelo(METEOR_MODEL, texturaMetoro, meteoro);
			glPopMatrix();
		}
		else {
			/* nothing to do */
		}
	}
}

#endif
